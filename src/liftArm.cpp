#include "liftArm.h"


double liftkP = 1; 
double liftkI = 0; 
double liftkD = 0; 
double antiWindUp = 4; 


int liftError; 
int liftPrevError = 0; 
int liftDerivative; 
int liftTotalError = 0; 


int desiredLiftValue = 0; // Shared desired value for the lift
bool liftPIDRunning = false; // Flag to indicate if the liftPID is active



void liftPIDTask(void* param) {
    double liftMotorPower; 
    while (true) {
       
        if (liftPIDRunning) {

            int LiftMotorPosition = rotation_sensor.get_angle()/ 100;
            liftError = LiftMotorPosition - desiredLiftValue;
            liftDerivative = liftError - liftPrevError;
            liftTotalError += liftError;

        

            if (abs(liftError) < antiWindUp) {
                liftMotorPower = liftError * liftkP + liftDerivative * liftkD + liftTotalError * liftkI;
            } else {
                liftMotorPower = liftError * liftkP + liftDerivative * liftkD;
            }
            liftMotor.move(liftMotorPower);
            // Stop 350
            if (abs(liftError) < 1    ) {
                liftMotor.brake();
                liftPIDRunning = false; 
            }
            
            liftPrevError = liftError;
            if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1) || controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)){
                liftPIDRunning = false;
            }

        }

        pros::delay(20); // Save resources
    }
}