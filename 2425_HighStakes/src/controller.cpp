#include "controller.h"

using namespace pros; 

pros::Controller controller(pros::E_CONTROLLER_MASTER);


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