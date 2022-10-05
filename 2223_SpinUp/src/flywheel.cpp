#include "flywheel.h"

Flywheel::Flywheel(int port1, int port2): m1(port1), m2(port2), previousPower(0) {

}

void Flywheel::runVoltage(double power) {
    m1.moveVoltage(power);
    m2.moveVoltage(power);
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

Flywheel fly = Flywheel(FLYWHEEL_1, FLYWHEEL_2);