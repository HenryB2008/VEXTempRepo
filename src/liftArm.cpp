#include "liftArm.h"


double liftkP = 3; 
double liftkI = 0.0; 
double liftkD = 0.05; 


int liftError; 
int liftPrevError = 0; 
int liftDerivative; 
int liftTotalError = 0; 

int desiredLiftValue = 0; // Shared desired value for the lift
bool liftPIDRunning = false; // Flag to indicate if the liftPID is active

void liftPIDTask(void* param) {
    while (true) {
        if (liftPIDRunning) {
            int LiftMotorPosition = rotation_sensor.get_angle();
            liftError = LiftMotorPosition - desiredLiftValue;
            liftDerivative = liftError - liftPrevError;
            liftTotalError += liftError;

            double liftMotorPower = liftError * liftkP + liftDerivative * liftkD + liftTotalError * liftkI;
            liftMotor.move(liftMotorPower);

            // Stop condition
            if (abs(liftError) < 500) {
                liftPIDRunning = false;
                liftMotor.brake();
            }

            liftPrevError = liftError;
        }

        pros::delay(20); // Save resources
    }
}