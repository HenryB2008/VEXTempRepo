#include "main.h"
#include "pid.h"
#include "odom.h"
#include "drivetrain.h"
#include "controller.h"
#include "intake.h"


void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors
    // print position to brain screen
    pros::Task screen_task([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // delay to save resources
            pros::delay(20);
        }
    });
}

void opcontrol() {
    // loop forever
    while (true) {
        // get left y and right y positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        int R1Button = controller.get_digital(E_CONTROLLER_DIGITAL_R1); 
        int R2Button = controller.get_digital(E_CONTROLLER_DIGITAL_R2); 
        
        

        // move the robot
        chassis.tank(leftY, rightY);


        //intake code
        if(R2Button)
        {
            IntakeMotor1.move(128);
            IntakeMotor2.move(-128);
        } else if (R1Button)
        {
            IntakeMotor1.move(-128);
            IntakeMotor2.move(128);
        } else
        {
            IntakeMotor1.brake();
            IntakeMotor2.brake(); 
        }
        
        // delay to save resources
        pros::delay(25);
    }
}