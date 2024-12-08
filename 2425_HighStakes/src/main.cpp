#include "lemlib/api.hpp" // IWYU pragma: keep
#include "main.h"
#include "pros/misc.h"
using namespace pros; 

ASSET(firstRing_txt);
ASSET(followRoute_txt);




       

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
lemlib::ControllerSettings lateral_controller(5.9, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              2.2, // derivative gain (kD)
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

bool enableLiftPID = true; 




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


int distance; 
bool monitorDistanceRunning = false; 
void monitorDistance(void* param) {
    
  while (true) {
    
    if(monitorDistanceRunning) {
        distance = intakeDistance.get_proximity(); 
        
        if(distance == 255) {
            monitorDistanceRunning = false;
            pros::delay(625);
            IntakeMotor1.brake(); 
            
        } else {
            IntakeMotor1.move(-127);    
        }
        
    }
    pros::delay(5);
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



void test() {
    
    chassis.setPose(-11, 50, 235);
    pros::delay(10); 
    chassis.follow(followRoute_txt, 8, 2500);
    
    
    
}


void blueRight() {
    chassis.setPose(0,0,0); //set initial position
    liftPIDRunning = true; 
    desiredLiftValue = 22800; 
    doinker.extend();       
    chassis.moveToPoint(0,39.5,  2000);   //move up to knock the pair of blue rings off
    chassis.waitUntil(38.7);            
    chassis.cancelMotion();
    pros::delay(175);
    chassis.moveToPoint(0,29,800, {.forwards = false});
    chassis.waitUntil(10.3); 
    chassis.cancelMotion(); 
    doinker.retract();
    pros::delay(300);
    chassis.turnToHeading(62.5, 700); 
    chassis.waitUntil(61.5);
    chassis.cancelMotion();
    pros::delay(20);    
    chassis.setPose(24, 30, 0);
    pros::delay(250);
    chassis.moveToPoint(24, 19, 800, {.forwards = false, .minSpeed = 10, .earlyExitRange = 0.8, }, false);
    mogo.toggle();  
    pros::delay(20);
    IntakeMotor1.move(-127);
    pros::delay(200);
    chassis.turnToHeading(-55, 800, {.minSpeed=15, .earlyExitRange = 0.9}, false);
    chassis.setPose(0,0,0);
    pros::delay(100);
    chassis.moveToPoint(0, 14   , 1500, {.minSpeed = 10, .earlyExitRange = 0.8}, false);
    pros::delay(100);
    chassis.turnToHeading(52.5, 1000, {.minSpeed=15, .earlyExitRange = 0.9}, false);
    pros::delay(100);
    chassis.setPose(0,0,0);
    pros::delay(10);
    chassis.moveToPoint(0,8,1000, {.maxSpeed = 40, .minSpeed = 10, .earlyExitRange = 0.8}, false);
    pros::delay(500);
    chassis.turnToHeading(-165, 800, {}, false); 
    chassis.waitUntilDone();
    chassis.setPose(0,0,0);
    pros::delay(50);
    chassis.moveToPoint(0,32, 1500, {.maxSpeed = 80}, false);

}


void redLeft()
{   
    chassis.setPose(0,0,0); //set initial position
    liftPIDRunning = true; 
    desiredLiftValue = 22800; 
    doinker.extend();       
    chassis.moveToPoint(0,39.5,  2000);   //move up to knock the pair of blue rings off
    chassis.waitUntil(38.7);            
    chassis.cancelMotion();
    pros::delay(175);
    chassis.moveToPoint(0,29,800, {.forwards = false});
    chassis.waitUntil(10.3); 
    chassis.cancelMotion(); 
    doinker.retract();
    pros::delay(300);
    chassis.turnToHeading(-62.5, 700); 
    chassis.waitUntil(61.5);
    chassis.cancelMotion();
    pros::delay(20);    
    chassis.setPose(-24, 30, 0);
    pros::delay(250);
    chassis.moveToPoint(-24, 19, 800, {.forwards = false, .minSpeed = 10, .earlyExitRange = 0.8, }, false);
    mogo.toggle();  
    pros::delay(20);
    IntakeMotor1.move(-127);
    pros::delay(200);
    chassis.turnToHeading(55, 800, {.minSpeed=15, .earlyExitRange = 0.9}, false);
    chassis.setPose(0,0,0);
    pros::delay(100);
    chassis.moveToPoint(0, 14   , 1500, {.minSpeed = 10, .earlyExitRange = 0.8}, false);
    pros::delay(100);
    chassis.turnToHeading(-52.5, 1000, {.minSpeed=15, .earlyExitRange = 0.9}, false);
    pros::delay(100);
    chassis.setPose(0,0,0);
    pros::delay(10);
    chassis.moveToPoint(0,8,1000, {.maxSpeed = 40, .minSpeed = 10, .earlyExitRange = 0.8}, false);
    pros::delay(500);
    chassis.turnToHeading(-165, 800, {}, false); 
    chassis.waitUntilDone();
    chassis.setPose(0,0,0);
    pros::delay(50);
    chassis.moveToPoint(0,32, 1500, {.maxSpeed = 80}, false);
    
    /*
    chassis.turnToHeading(-115, 800, {.minSpeed=15, .earlyExitRange = 0.9}, false);
    pros::delay(20);
    liftPIDRunning = true; 
    desiredLiftValue = 21200; 
    pros::delay(250);
    chassis.setPose(0,0,0);
    pros::delay(10);
    chassis.moveToPoint(0, 20, 1500, {.minSpeed=72, .earlyExitRange = 1}, false);
    mogo.toggle();
    monitorDistanceRunning = true; 
    chassis.moveToPoint(0, 57, 1500, {.minSpeed=10, .earlyExitRange = 1});
    if(!chassis.isInMotion())
    {
        pros::delay(200);   
    }
    */



    //chassis.turnToHeading(28, 800, {.minSpeed=15, .earlyExitRange = 0.9}, false);
    
    



    
    

}

void autonomous() {
    redLeft(); 

}





void initialize() {
    mogo.retract(); 
    doinker.retract();
    pros::lcd::initialize(); // initialize brain screen
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);    
    chassis.calibrate(); // calibrate sensors
    rotation_sensor.set_data_rate(5);
    LiftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    



   
    pros::Task liftPIDController(liftPIDTask, nullptr, "Lift PID Task");
    pros::Task distanceTask(monitorDistance, nullptr, "Intake Distance Task"); 
    

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
    autonomous(); 
}





void skills()
{

}


