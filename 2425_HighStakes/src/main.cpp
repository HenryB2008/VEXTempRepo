#include "lemlib/api.hpp" // IWYU pragma: keep
#include "main.h"
#include "pros/misc.h"
using namespace pros; 





       

//Odometry 

pros::Imu imu(16); //imu.
pros::Rotation horizontal_encoder(5); 
pros::Rotation vertical_encoder(7);   
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, 2, -2);  
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, 2, 5); 
lemlib::OdomSensors sensors(&vertical_tracking_wheel, // Vertical tracking wheel 1, set to null
                            nullptr, // Vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horizontal_tracking_wheel, // Horizontal tracking wheel 1
                            nullptr, // Horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // Inertial sensor
);


//PID-
// latetral PID controller
lemlib::ControllerSettings lateral_controller(6.2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              1.9, // derivative gain (kD)
                                              0, // anti windup
                                              0, // small error range, in inches
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in inches
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (s5lew)
);

// angular PID controller (1.9, 9)
lemlib::ControllerSettings angular_controller(3, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              14, // derivative gain (kD)
                                              0, // anti windup
                                              0, // small error range, in degrees
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in degrees
                                              0       , // large error range timeout, in milliseconds
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
   600,            // wheel rpm            
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
        } else {
            IntakeMotor1.brake(); 
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
        } else if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN)) {
            desiredLiftValue = 22800;
            liftPIDRunning = true;
        } else if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_L1)) {
            desiredLiftValue = 32000;
            liftPIDRunning = true;
            IntakeMotor1.move(-127);
            pros::delay(1000);
            IntakeMotor1.brake();  
        }
        
    
        

        if(controller.get_digital_new_press(E_CONTROLLER_DIGITAL_Y)) {
            mogo.toggle(); 
        }
        if(controller.get_digital_new_press(E_CONTROLLER_DIGITAL_RIGHT)) { 
            doinker.toggle();
        } 
        if(controller.get_digital_new_press(E_CONTROLLER_DIGITAL_B)){
            intakeSolenoid.toggle(); 
        }


        // stops brain from using too much resources    
        pros::delay(20);
    }
}



void red(){
    
    chassis.setPose(0,0,0);     //calibrate position  
    liftPIDRunning = true;  
    desiredLiftValue = 22800;       //lift arm for intakex   
    pros::delay(10);             
    chassis.moveToPoint(0,-8, 1200, {.forwards = false, .minSpeed = 72}, false); //move up to edge the other bot
    pros::delay(100);
    chassis.moveToPoint(0,4,1200, {}, false);           //move back to the original position
    pros::delay(200);
    chassis.turnToHeading(304, 1200, {}, false);         //turn to face the mogo
    pros::delay(200);
    chassis.setPose(0,0,0);
    pros::delay(20);
    chassis.moveToPoint(0, -30, 1400, {.forwards = false, .maxSpeed=90, .minSpeed = 1,  .earlyExitRange = 1});          
    chassis.waitUntil(16);
    intakeRunning = true; 
    chassis.waitUntilDone(); 
    pros::delay(50);
    mogo.toggle(); 
    pros::delay(300); 
    chassis.turnToHeading(243, 1200, {}, false);         //-28.365, -20.951, 180
    pros::delay(10);            
    chassis.setPose(0,0,0); 
    pros::delay(150);
    chassis.moveToPoint(0, 26, 900, {}, false);     //y: -44.951 
    pros::delay(1000);
    chassis.turnToHeading(159, 800, {}, false);
    pros::delay(10);
    chassis.setPose(0,0,0);  //theta 337 
    mogo.toggle(); 
    pros::delay(500);
    reverse = true; 
    chassis.moveToPoint(0, 55, 1200, {.maxSpeed = 110}, false);    //-38.274, 0.434, 329 
    pros::delay(10);
    chassis.setPose(0,0,0);
    pros::delay(300);
    chassis.turnToHeading(257, 800, {}, false);
    pros::delay(10);
    chassis.setPose(0,0,0);     
    pros::delay(200);
    chassis.moveToPoint(0,-16, 800, {.forwards = false}, false);     //gets the second mogo 
    mogo.toggle(); 
    pros::delay(250);
    chassis.turnToHeading(125, 800, {}, false); 
    chassis.setPose(0,0,0);
    pros::delay(300); 
    reverse = false; 
    chassis.moveToPoint(0, 28, 900);



    pros::delay(2000);
    

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
            pros::lcd::print(3, "distance:  %d", intakeDistance.get_proximity());
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());

            // delay to save resources  
            pros::delay(20);

        }
    });    
    opcontrol(); 
}





void skills()
{

}


