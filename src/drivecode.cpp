#include "drivecode.h"

bool intake_forward = false;
bool intake_reverse = false;
bool driveState = true; 

int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

int LiftMotorPosition = rotation_sensor.get_angle();


void driver()
{
    // Controller Buttons

    // Loop

    while (true)
    {
        controller.print(0,0, "Intake: %d", liftMotor.get_temperature());

        leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        LiftMotorPosition = rotation_sensor.get_angle();

        // move drivetrain

        if(driveState){

            
            chassis.tank(leftY, rightY);
            
           /*
            chassis.arcade(rightY, // throttle
                rightX, // steer
                false, // enable drive curves
                0.75 // slightly prioritize steering
            );
            */
            
        } else {
            
            
            chassis.tank(leftY * 0.5, rightY * 0.5);
            
           /*
           chassis.arcade(leftY * 0.5, // throttle
            rightX * 0.5, // steer
            false, // enable drive curves
            0.75 // slightly prioritize steering
            
        );
        */
        
        }


        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
            intakeMotor1.move(-127);
        } else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            intakeMotor1.move(127);
        } else {
            intakeMotor1.move(0);
        }


        //86, 320 
        const int LIFT_MIN_ANGLE = 8600;
        const int LIFT_MAX_ANGLE = 32000;
        
        // Get current lift angle
        
        // L2 raises the lift, but only if it's below the max limit
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            // Only move up if above the minimum limit
            if (rotation_sensor.get_angle() > LIFT_MIN_ANGLE) {
                liftMotor.move(127);
            } else {
                liftMotor.move(0); // Prevent movement if at the limit
            }
        } 
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            // Only move down if below the maximum limit
            if (rotation_sensor.get_angle()< LIFT_MAX_ANGLE) {
                liftMotor.move(-127);
            } else {
                liftMotor.move(0); // Prevent movement if at the limit
            }
        } 
        // Move to preset position when RIGHT button is pressed
        else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
            desiredLiftValue = 101; 
            liftPIDRunning = true; 
            iterations = 0; 
        } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)){
            desiredLiftValue = 234;
            liftPIDRunning = true;
            iterations = 0; 
        }
        else {
            liftMotor.brake(); // Stop motor if no valid input
        }
       
        
/*
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
            mogo.retract();
        } else {
            mogo.extend(); 
        }
        */



        if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)){
            mogo.toggle();
        } 
            


        if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
            rightDoinker.toggle();
        }

        if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)){
            leftDoinker.toggle();
        }

        if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)){
            driveState = !driveState; 
        }

        if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)){
            gRushClamp.toggle(); 
        }
        


        pros::delay(20);
    }
}