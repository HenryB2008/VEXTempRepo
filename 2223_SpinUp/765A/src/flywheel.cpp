#include "../include/flywheel.h"

Flywheel::Flywheel(int port1, int port2, int port3): m1(port1), m2(port2), m3(port3) {

}

void Flywheel::runVoltage(double power = 12000){
    m1.moveVoltage(power);
    m2.moveVoltage(power);
    m3.moveVoltage(power);
}