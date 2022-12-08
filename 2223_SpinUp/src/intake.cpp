#include "intake.h"

Intake::Intake(int port1): m1(port1) {

}

void Intake::runVoltage(double power) {
    m1.moveVoltage(power);
}

void Intake::toggle() {
    runVoltage(powers.at(currPower));

    currPower += 1;

    // Cycle back to the beginning of the vector
    if (currPower == powers.size())
        currPower = 0;
}

Intake intake = Intake(INTAKE_MOTOR);