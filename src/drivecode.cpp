#include "drivecode.h"

bool intake_forward = false;
bool intake_reverse = false;
bool driveState = true; 

int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
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
        LiftMotorPosition = rotation_sensor.get_angle();

        // move drivetrain

        if(driveState){
            chassis.tank(leftY, rightY);
        } else {
            chassis.tank(leftY * 0.5, rightY * 0.5);
        }


        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
            intakeMotor1.move(-127);
        } else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            intakeMotor1.move(127);
        } else {
            intakeMotor1.move(0);
        }

        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) ) {
           liftMotor.move(127);
        } else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
            liftMotor.move(-127);
        } else if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
            desiredLiftValue = 9000; 
            liftPIDRunning = true; 
        }

         else {
            liftMotor.brake(); 
        }
       

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