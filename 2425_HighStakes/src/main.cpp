#include "lemlib/api.hpp" // IWYU pragma: keep
#include "main.h"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/util.hpp"
#include "pros/misc.h"
#include <stdio.h>
using namespace pros; 




       

//Odometry 

pros::Imu imu(16); //imu.
pros::Rotation horizontal_encoder(5); 
pros::Rotation vertical_encoder(7);   
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, 2, -2.5);  
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, 2, 5); 
lemlib::OdomSensors sensors(&vertical_tracking_wheel, // Vertical tracking wheel 1, set to null
                            nullptr, // Vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horizontal_tracking_wheel, // Horizontal tracking wheel 1
                            nullptr, // Horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // Inertial sensor
);


//PID-
// latetral PID controller
lemlib::ControllerSettings lateral_controller(6.2 , // proportional gain (kP)6.2
                                              0, // integral gain (kI)
                                              1.9, // derivative gain (kD) 1.9
                                              0, // anti windup
                                              0, // small error range, in inches
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in inches
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (s5lew)
);

// angular PID controller (8, 44 FOR SKILLS) 1.9, 9SET TO 3, 14 FOR THE OTHER AUTON 
lemlib::ControllerSettings angular_controller(8,  // proportional gain (kP) 12.5
                                              0, // integral gain (kI)
                                                44                   , // derivative gain (kD) 30
                                              0, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              2, // large error range, in degrees
                                              500       , // large error range timeout, in milliseconds
                                                0 // maximum acceleration (slew)
);


//Drivetrain & Chassis

MotorGroup left_motors({-17, -18, 19}, MotorGearset::blue);
MotorGroup right_motors({-12, 13, 14}, MotorGearset::blue);
// Initialize the drivetrain with the specified settings
lemlib::Drivetrain drivetrain (
   &left_motors,
   &right_motors,
   11.75,       // track width          // this might be wrong
   2.75,              // wheel diameter      
   450,            // wheel rpm            
   8             // horizontal drift
);

lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);





//other
pros::Optical colorSensor(5);
pros::Motor IntakeMotor1 (15);
pros::Motor LiftMotor(20);
pros::adi::Pneumatics mogo('B', false); 
pros::adi::Pneumatics intakeSolenoid('H', false);
pros::adi::Pneumatics doinker('D', false);
pros::ADIDigitalIn limit('E');
pros::Rotation rotation_sensor(9);
pros::Optical intakeDistance (4);






double liftkP = 3; 
double liftkI = 0.0; 
double liftkD = 0.05; 


int liftError; 
int liftPrevError = 0; 
int liftDerivative; 
int liftTotalError = 0; 






int desiredLiftValue = 0; // Shared desired value for the lift
bool liftPIDRunning = false; // Flag to indicate if the liftPID is active

void liftPIDTask(void* param) {
    while (true) {
        if (liftPIDRunning) {
            int LiftMotorPosition = rotation_sensor.get_angle();
            liftError = LiftMotorPosition - desiredLiftValue;
            liftDerivative = liftError - liftPrevError;
            liftTotalError += liftError;

            double liftMotorPower = liftError * liftkP + liftDerivative * liftkD + liftTotalError * liftkI;
            LiftMotor.move(liftMotorPower);

            // Stop condition
            if (abs(liftError) < 500) {
                liftPIDRunning = false;
                LiftMotor.brake();
            }

            liftPrevError = liftError;
        }

        pros::delay(20); // Save resources
    }
}

bool intakeRunning = false; 
bool reverse = false; 

void intakeTask(void* param) {
    while (true) {
        if(intakeRunning && reverse) {
            IntakeMotor1.move(127);
        } else if (intakeRunning && reverse==false) {
            IntakeMotor1.move(-127); 
        }
        pros::delay(20);
    }
}




 









void opcontrol() {
// Controller Buttons
    pros::Controller controller(pros::E_CONTROLLER_MASTER);
    


    bool intake_forward = false;
    bool intake_reverse = false;


   


    //Loop
    while (true) {  

        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        int LiftMotorPosition = rotation_sensor.get_angle();


        //move drivetrain
        chassis.tank(leftY, rightY);
        
        if(controller.get_digital_new_press(E_CONTROLLER_DIGITAL_R1)){
            intake_reverse = false;
            intake_forward = !intake_forward;
        }

        if(controller.get_digital_new_press(E_CONTROLLER_DIGITAL_R2)){
            intake_forward = false;
            intake_reverse = !intake_reverse;
        }

        if(intake_forward){
            IntakeMotor1.move(-127);
        }
        else if(intake_reverse){
            IntakeMotor1.move(127);
        }
        else{
            IntakeMotor1.brake();
        }
        

        
        if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_L2)) {
            desiredLiftValue = 21200;
            liftPIDRunning = true;
        } else if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_RIGHT)) {
            desiredLiftValue = 22800;
            liftPIDRunning = true;
        } else if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_L1)) {
            desiredLiftValue = 32000;
            liftPIDRunning = true;
            IntakeMotor1.move(-127);
            pros::delay(250);
            IntakeMotor1.brake();
        }
        
    
        

        if(controller.get_digital_new_press(E_CONTROLLER_DIGITAL_Y)) {
            mogo.toggle(); 
        }
        if(controller.get_digital_new_press(E_CONTROLLER_DIGITAL_B)) { 
            doinker.toggle();
        } 
        if(controller.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN)){
            intakeSolenoid.toggle(); 
        }


        // stops brain from using too much resources    
        pros::delay(20);
    }
}






void test() {
    chassis.setPose(0,0,180);
    chassis.turnToHeading(270, 1200);  
}



void skills() {
    
    chassis.setPose(0,0,0);     //INITIAL POSITION. this is where the imu is located 
    
    
    liftPIDRunning = true; 
    desiredLiftValue = 32000; 
    pros::delay(1000);
    
    liftPIDRunning = true; 
    desiredLiftValue = 23500; 
    
    chassis.moveToPoint(0, -11, 800, {.forwards = false}, false);
    chassis.turnToHeading(90, 1300, {}, false);
    
    chassis.moveToPoint(-5, chassis.getPose().y, 750, {.forwards = false});
    chassis.waitUntil( 10);
    mogo.extend();
    chassis.waitUntilDone(); 
    pros::delay(400);   
    
    chassis.turnToHeading(180, 1300, {}, false);
    IntakeMotor1.move(-127);
    chassis.moveToPoint(chassis.getPose().x, -44, 1200, {}, false);
    pros::delay(500);
    chassis.turnToHeading(270, 1800, {}, false);
    chassis.moveToPoint(-38,  chassis.getPose().y, 1300, {.maxSpeed = 80}, false);
    pros::delay(700);
    chassis.turnToPoint(-40, -5, 1400, {}, false);
    
    chassis.moveToPoint(-40, -3, 1400, {.maxSpeed = 90}, false);
    pros::delay(1500);
    chassis.moveToPoint(-40, -11, 900, {.forwards = false}, false);
    chassis.turnToHeading(122.5, 1200, {}, false);
    chassis.moveToPoint(-35.5, -2.25, 900, {.forwards = false}, false);
    mogo.retract(); 
    pros::delay(300);
    
    chassis.moveToPose(20, -4, 86.5 , 2800,  {}, false);
    chassis.turnToHeading(chassis.getPose().theta - 180, 1600, {}, false);
    chassis.setPose(chassis.getPose().x, chassis.getPose().y, 270);
    pros::delay(10);
    chassis.moveToPoint(36, chassis.getPose().y, 1400, {.forwards = false, .maxSpeed = 60});
    chassis.waitUntil(13.5);
    mogo.toggle();
    chassis.waitUntilDone();  
    chassis.turnToHeading(chassis.getPose().theta + 178, 1500, {}, false);
    chassis.moveToPoint(76, chassis.getPose().y, 2000, {.maxSpeed = 60}, false); 
    pros::delay(500);
    chassis.moveToPoint(72, chassis.getPose().y, 1000, {.forwards = false}, false);
    chassis.turnToHeading(213, 1500, {}, false);
    chassis.moveToPoint(76.5, -14, 1000, {.forwards = false}, false);
    mogo.retract();
    pros::delay(350);
    //chassis.moveToPose(63, -70.5, 198.5, 2000, {.minSpeed = 70, .earlyExitRange = 10});
    chassis.moveToPose(31, -120,  230, 5000, {}, false);
    chassis.turnToHeading(122, 1400, {}, false);
    IntakeMotor1.brake();   
    chassis.moveToPose(75, -113, 91, 3500, {.minSpeed = 30}, false);
    chassis.moveToPose(-37, -113, 87, 4000, {.forwards = false, .minSpeed = 50}, false);


    
}

void red(){
    chassis.setPose(0,0,0);         
    liftPIDRunning = true;  
    desiredLiftValue = 23500;      //lift arm for intakex   
    pros::delay(20);
    chassis.moveToPoint(0, -30, 1400, {.forwards = false, .maxSpeed=75, .minSpeed = 1,  .earlyExitRange = 1});          //theta
    chassis.waitUntil(16);
    IntakeMotor1.move(-127);
    chassis.waitUntil(25);
    mogo.toggle();
    chassis.waitUntilDone();
    chassis.turnToHeading(250, 1500, {}, false);
    chassis.setPose(chassis.getPose().x, chassis.getPose().y, 90);
    chassis.moveToPoint(30, chassis.getPose().y, 1050, {}, false); 
    pros::delay(750);
    chassis.turnToPoint(-28, -92.5, 1400, {}, false);
    pros::delay(250);
    
    mogo.toggle();
    IntakeMotor1.move(127);
    chassis.moveToPoint(-28, -92.5, 2200,{.maxSpeed = 85},  false);

    chassis.turnToPoint(-40, -52, 1200, {.forwards = false}, false);
    chassis.moveToPoint(-37.5, -50.8, 1500, {.forwards = false});
    

    chassis.waitUntil(30);
    mogo.toggle(); 

    chassis.waitUntilDone();
    //chassis.moveToPoint(-37.5, -50.8, 800, {}, false);

    
    chassis.turnToHeading(253, 1400, {}, false);
    IntakeMotor1.move(-127);

    chassis.moveToPoint(-70.5, -71, 1200, {}, false); 
    chassis.turnToHeading(chassis.getPose().theta + 180, 1600,{}, false);
    chassis.moveToPose(-29, -41, 70, 1500, {.minSpeed = 50}, false);
    

    
    
    /*
    chassis.moveToPose(-37, -58, 144,   1200, {.forwards = false});
    
    chassis.waitUntil(25);
    mogo.toggle(); 
    chassis.waitUntilDone(); 
    
    chassis.turnToHeading(266,  1400, {}, false); 
    chassis.setPose(chassis.getPose().x, chassis.getPose().y, 270);

    chassis.moveToPoint(-75, chassis.getPose().y, 1600, {}, false);
    */  


    /*
    chassis.turnToPoint(-37, -59, 1400, {.forwards = false}, false);
    chassis.moveToPoint(-37, -59, 1800, {.forwards = false}); 
    chassis.waitUntil(24);
    mogo.toggle();
    chassis.waitUntilDone(); 
    IntakeMotor1.move(-127);
    */

    pros::delay(1000);


    

}
    
    

void autonomous() {
    red(); 
}





void initialize() {
    mogo.retract(); 
    doinker.retract();
    pros::lcd::initialize(); // initialize brain screen
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);    
    chassis.calibrate(); // calibrate sensors
    LiftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    

    pros::Task liftPIDController(liftPIDTask, nullptr, "Lift PID Task");
    pros::Task intakeStuff(intakeTask, nullptr, "intake Task");




    //pros::Task toggleDoinker(toggleDoinkerTask, nullptr, "Toggle Doinker");

     pros::Task screen_task([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());

            // delay to save resources  
            pros::delay(20);

        }
    });    
    autonomous(); 
}







