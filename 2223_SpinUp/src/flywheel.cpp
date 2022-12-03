#include "flywheel.h"

Flywheel::Flywheel(int port1, int port2): m1(port1), m2(port2) {

}

void Flywheel::runVoltage(double power) {
    m1.moveVoltage(power);
    m2.moveVoltage(power);
}

void Flywheel::toggle() {
    runVoltage(powers.at(currPower));

    currPower += 1;

    // Cycle back to the beginning of the vector
    if (currPower == powers.size())
        currPower = 0;
}

Flywheel fly = Flywheel(FLYWHEEL_1, FLYWHEEL_2);