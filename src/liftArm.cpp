#include "liftArm.h"


double liftkP = 2.2; 
double liftkI = 0; 
double liftkD = 0.5; 
double antiWindUp = 8; 


int liftError; 
int liftPrevError = 0; 
int liftDerivative; 
int liftTotalError = 0; 

int desiredLiftValue = 0; // Shared desired value for the lift
bool liftPIDRunning = false; // Flag to indicate if the liftPID is active

int iterations = 0; 



void liftPIDTask(void* param) {
    double liftMotorPower; 
    while (true) {

       
        if (liftPIDRunning) {
            iterations++; 
            int LiftMotorPosition = rotation_sensor.get_angle()/ 100;
            liftError = desiredLiftValue - LiftMotorPosition;
            liftDerivative = liftError - liftPrevError;
            liftTotalError += liftError;

        

            if (abs(liftError) < antiWindUp) {
                liftMotorPower = liftError * liftkP + liftDerivative * liftkD + liftTotalError * liftkI;
            } else {
                liftMotorPower = liftError * liftkP + liftDerivative * liftkD;
            }
            lbMotor1.move(liftMotorPower);
            lbMotor2.move(liftMotorPower);
            // Stop 350
            if (abs(liftError) < 1 || iterations > 75) {
                lbMotor1.brake();
                lbMotor2.brake(); 
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