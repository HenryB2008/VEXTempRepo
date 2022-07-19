#include "flywheel.h"

Flywheel::Flywheel(int port1, int port2, int port3): m1(port1), m2(port2), m3(port3), previousPower(0) {

}

void Flywheel::runVoltage(double power) {
    m1.moveVoltage(power);
    m2.moveVoltage(power);
    m3.moveVoltage(power);
}

void Flywheel::toggle(double power) {
    if (previousPower != power) {
        runVoltage(power);
    } else {
        runVoltage(0);
    }

    previousPower = power;
}

Flywheel fly = Flywheel(FLYWHEEL_1, FLYWHEEL_2, FLYWHEEL_3);