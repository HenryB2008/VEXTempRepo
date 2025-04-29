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
        lbMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        controller.print(0,0, "Intake: %d", lbMotor1.get_temperature());

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
            
        } 


/*
        if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
            descorePiston1.extend(); 
            descorePiston2.extend();
            pros::delay(150);
            intakeMotor1.move(127); //spins intake backwards
            pros::delay(150);
            intakeMotor1.brake(); 
        } else {
            descorePiston1.retract(); 
            descorePiston2.retract();
            intakeMotor1.brake(); 
        }
            */


        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
            intakeMotor1.move(-127);
        } else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            intakeMotor1.move(127);
        } else {
            intakeMotor1.move(0);
        }
    


        //86, 320 
        const int LIFT_MIN_ANGLE = 6900;
        const int LIFT_MAX_ANGLE = 31400;
        
        // Get current lift angle
        
        
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            // When raising: Check that we're below the MAX limit
            if (rotation_sensor.get_angle() < LIFT_MAX_ANGLE) {
                lbMotor1.move(127);
                lbMotor2.move(127);
            } else {
                lbMotor1.move(0);
                lbMotor2.move(0);
            }
        } 
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            if (rotation_sensor.get_angle() > LIFT_MIN_ANGLE) {
                lbMotor1.move(-127);
                lbMotor2.move(-127);
            } else {
                lbMotor1.move(0);
                lbMotor2.move(0);
            }
        }
        else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
            desiredLiftValue = 292; 
            liftPIDRunning = true; 
            iterations = 0; 
        } 


        else {
            lbMotor1.brake();
            lbMotor2.brake();
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