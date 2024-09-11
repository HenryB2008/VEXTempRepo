#include "lemlib/api.hpp" // IWYU pragma: keep
#include "main.h"
#include "pros/misc.h"

using namespace pros; 

ASSET(moveToWallStake_txt);
ASSET(firstReverse_txt);
ASSET(collectFirstRing_txt);

pros::Controller controller(pros::E_CONTROLLER_MASTER);


pros::Motor IntakeMotor1 (1);
pros::Motor LiftMotor(3);

// Initialize IMU
pros::Imu imu(9);

pros::Optical colorSensor(5);

// Horizontal tracking wheel encoder
pros::Rotation horizontal_encoder(19);  // Change port to finalized one
// Vertical tracking wheel encoder
pros::Rotation vertical_encoder(16);    // Change port to finalized one

// Horizontal tracking wheel
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_275, -5.75);    // Change distance in future
// Vertical tracking wheel
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_275, -2.5); // Change distance in future
    

// OdomSensors setup
lemlib::OdomSensors sensors(&vertical_tracking_wheel, // Vertical tracking wheel 1, set to null
                            nullptr, // Vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horizontal_tracking_wheel, // Horizontal tracking wheel 1
                            nullptr, // Horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // Inertial sensor
);

pros::adi::Pneumatics mogo('B', false);
pros::adi::Pneumatics doinker('C', false);

MotorGroup left_motors({-8, -2, -10}, MotorGearset::blue);
MotorGroup right_motors({11, 14, 17}, MotorGearset::blue);


lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);


// angular PID controller
lemlib::ControllerSettings angular_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// Initialize the drivetrain with the specified settings
lemlib::Drivetrain drivetrain (
   &left_motors,
   &right_motors,
   12,       // track width          // this might be wrong
   2.75,              // wheel diameter      
   600,            // wheel rpm            
   2               // horizontal drift
);


lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);



void autonomous()
{   
    
    chassis.setPose(52.339, -13.475, 315);
    doinker.extend();
    pros::delay(1500);
    chassis.follow(firstReverse_txt, 15, 2000, false);
    chassis.waitUntilDone();
    pros::delay(1500);
    chassis.setPose(58.271, -19.203, 315);
    pros::delay(1500);
    chassis.follow(collectFirstRing_txt, 15, 2000, true);
    chassis.waitUntilDone();
    pros::delay(1500);
    chassis.setPose(48.862, -10.816, 315);
    pros::delay(1500);
    chassis.turnToHeading(0, 2000);
    chassis.waitUntilDone();
    pros::delay(1500);
    chassis.follow(moveToWallStake_txt, 15, 2000); 
    
    
   
    


    //mogo.toggle();
    // LiftMotor.move(127);
    // pros::delay(500);
    // chassis.moveToPose(-32.343, -18.589, 140, 2000, {.forwards=false});
    // chassis.moveToPose(-46.047, -1.407, 140, 2000, {.forwards =true} );
    // IntakeMotor1.move(127);
    // pros::delay(1000);

    // chassis.follow(furthestdonut_txt, 10, 1500, true);
    // pros::delay(500);
    // chassis.follow(seconddonut_txt, 10, 2500, false);
    // pros::delay(500);
    // chassis.follow(thirddonut_txt, 10, 2500, false);
    // doinker.toggle();
    // pros::delay(500);
    // LiftMotor.brake();
    // doinker.toggle();
    // chassis.follow(finaltouchdown_txt, 10, 2500, false);
    // IntakeMotor1.brake(); 


    

}






void initialize() {
    mogo.retract();
    pros::lcd::initialize(); // initialize brain screen
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);    
    chassis.calibrate(); // calibrate sensors
    // print position to brain screen


    /*sole1.set_value(false);*/


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





void opcontrol() {
    bool intake_forward = false;
    bool intake_reverse = false;
    //Loop
    while (true) {
        //Controller buttons
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        int R2Button = controller.get_digital(E_CONTROLLER_DIGITAL_R2);
        int R1Button = controller.get_digital(E_CONTROLLER_DIGITAL_R1);
        int L1Button = controller.get_digital(E_CONTROLLER_DIGITAL_L1);
        int L2Button = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
        int xButton = controller.get_digital(pros::E_CONTROLLER_DIGITAL_X);
        int yButton = controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y);
       
       


        //move drivetrain
        chassis.tank(leftY, rightY);


        //intake code
        /*if(R2Button)
        {
            IntakeMotor1.move(127);
        } else if (R1Button)
        {
            IntakeMotor1.move(-127);
        } else
        {
            IntakeMotor1.brake();
        }*/

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

        if(L1Button)
        {
            LiftMotor.move(127);
        } else if (L2Button)
        {
            LiftMotor.move(-127);
        } else
        {
            LiftMotor.brake();
        }

        
        
        if(controller.get_digital_new_press(E_CONTROLLER_DIGITAL_Y)){
            mogo.toggle();
        }

        if(controller.get_digital_new_press(E_CONTROLLER_DIGITAL_B)){
            doinker.toggle();
        }
       
        // stops brain from using too much resources
        pros::delay(25);
    }
}
