#include "lemlib/api.hpp" // IWYU pragma: keep
#include "main.h"
#include "pros/misc.h"

using namespace pros; 


ASSET(IntakeRedRing_txt);



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


lemlib::ControllerSettings lateral_controller(13, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              35, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);


// angular PID controller
lemlib::ControllerSettings angular_controller(3.5, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              25, // derivative gain (kD)
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




    //pick up red ring and setup
    LiftMotor.move(127);
    doinker.extend();   
    pros::delay(300);
    LiftMotor.brake();
    
    chassis.setPose(-52.339, 13.475, 140);

    //deposit ring on field
    chassis.turnToHeading(75, 2000);
    chassis.waitUntilDone();

    chassis.setPose(-52.339, 13.475, 75);
    doinker.retract();
    pros::delay(500);
    


    // get ready to reverse
    chassis.turnToHeading(15, 2000);
    chassis.waitUntilDone();

    chassis.setPose(-52.339, 13.475, 15);
    pros::delay(250);

    chassis.moveToPoint(-57.911, -4.68,2000, {.forwards = false});
    chassis.waitUntilDone();
    chassis.moveToPoint(-57.092, -2.021, 2000);
    pros::delay(300);
    chassis.turnToHeading(90, 2000  );
    //chassis.moveToPoint(-55.661, -0.794, 3000);
    chassis.waitUntilDone();

    chassis.setPose(-57.092, -2.021, 90);

    pros::delay(20);
    
    chassis.moveToPoint(-62.65, -2.021, 2000, {.forwards = false});
    mogo.extend();
    chassis.waitUntilDone();
    chassis.moveToPoint(-65, -2.021, 2000, {.forwards = false});
    IntakeMotor1.move(-127);
    pros::delay(900);
    mogo.retract();
    chassis.setPose(-61.077, 0, 90);
   


    chassis.follow(IntakeRedRing_txt, 8, 3000);
    chassis.waitUntilDone();
    chassis.setPose(-44.002, 7.388, 40);
    pros::delay(1000);  
    IntakeMotor1.brake();

    chassis.turnToHeading(220, 2000);
    chassis.waitUntilDone();
    chassis.setPose(-39.911, 7.338,220);

    chassis.moveToPoint(-30.093, 22.554, 2000, {.forwards = false}); 
    chassis.waitUntil(14);
    IntakeMotor1.move(-127);
    LiftMotor.move(-127);
    mogo.extend();
    chassis.waitUntilDone();
    pros::delay(200);
    chassis.setPose(-30.093, 22.554, 220);
    pros::delay(20);
    chassis.turnToHeading(90, 2000);
    chassis.waitUntilDone();
    chassis.setPose(-30.093, 22.554, 90);
    pros::delay(20);
    chassis.moveToPoint(-10.865, 22.524, 2000, {.forwards=true});  





    

    // IntakeMotor1.brake();
    // pros::delay(1000);

    // chassis.setPose(-53.002, 8.615, 135);
    // chassis.turnToHeading(180, 2000);
    // chassis.waitUntilDone();
    // pros::delay(500);
    // chassis.setPose(-53.002, 8.615, 180);
    // chassis.moveToPose(-53.002, -0.025, 180, 2000);
    // chassis.waitUntilDone();
    // pros::delay(1000);
    // chassis.setPose(-53.002, -0.025, 180);
    // chassis.turnToHeading(95, 2000);
    // chassis.waitUntilDone();
    // pros::delay(500);
    // chassis.setPose(-53.002, -0.025, 95);
    // chassis.moveToPose(-61.077, -0.025, 95, 2000, {.forwards = false});
    // chassis.waitUntilDone();
    // chassis.setPose(-61.077, -0.025, 95); 
    // IntakeMotor1.move(-127);
    // pros::delay(2000);


    

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
