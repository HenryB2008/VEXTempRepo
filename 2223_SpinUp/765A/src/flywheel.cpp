#include "flywheel.h"

Flywheel::Flywheel(int port): m(port), previousPower(0) {

}

void Flywheel::runVoltage(double power) {
    m.moveVoltage(power);
}

void Flywheel::toggle(double power) {
    if (previousPower != power) {
        runVoltage(power);
        previousPower = power;
    } else {
        runVoltage(0);
        previousPower = 0;
    }
}

Flywheel fly = Flywheel(FLYWHEEL);