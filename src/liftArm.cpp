#include "liftArm.h"


double liftkP = 0.0285; 
double liftkI = 0.000275; 
double liftkD = 0.04; 
double antiWindUp = 500; 


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
            int LiftMotorPosition = rotation_sensor.get_angle();
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
            if (abs(liftError) < 400    ) {
                liftMotor.brake();
                liftPIDRunning = false; 
            }

            liftPrevError = liftError;
        }

        pros::delay(20); // Save resources
    }
}