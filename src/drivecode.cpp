#include "drivecode.h"

bool intake_forward = false;
bool intake_reverse = false;

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
        chassis.tank(leftY, rightY);

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1))
        {
            intake_reverse = false;
            intake_forward = !intake_forward;
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2))
        {
            intake_forward = false;
            intake_reverse = !intake_reverse;
        }

        if (intake_forward)
        {
            intakeMotor1.move(-127);
        }
        else if (intake_reverse)
        {
            intakeMotor1.move(127);
        }
        else
        {
            intakeMotor1.brake();
        }


        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2))
        {
            desiredLiftValue = 21200;
            liftPIDRunning = true;
        }
        else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT))
        {
            desiredLiftValue = 22800;
            liftPIDRunning = true;
        }
        else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1))
        {
            desiredLiftValue = 32000;
            liftPIDRunning = true;
            intakeMotor1.move(-127);
            pros::delay(250);
            intakeMotor1.brake();
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y))
        {
            mogo.toggle();
        }
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B))
        {
            doinker.toggle();
        }
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
        {
            intakeSolenoid.toggle();
        }
        if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
        {
            raiseSolenoid.toggle(); 
        }

        // stops brain from using too much resources
        pros::delay(20);
    }
}