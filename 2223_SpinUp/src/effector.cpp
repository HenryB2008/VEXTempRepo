#include "effector.h"
#include "controller.h"
#include "okapi/impl/device/controllerUtil.hpp"

Effector::Effector
    (const MotorGroup& motors, const std::vector<double>& powers): 
    motors(motors), powers(powers) {

}

void Effector::runVoltage(double power) {
    motors.moveVoltage(power);
}

void Effector::toggle(const Direction& dir) {
    // Run the power at the current index
    runVoltage(powers.at(currPower) * dir);

    // Increment by 1
    currPower += 1;

    // Cycle back to the beginning of the vector
    if (currPower == powers.size())
        currPower = 0;
}

void Effector::runWhenPressed(const okapi::ControllerDigital& b, double power) {
    if (Controller::getDigital(b))
        runVoltage(power);
    else
        runVoltage(0);
}

Effector intake    = Effector(MotorGroup({ INTAKE_MOTOR }), { 12000, 0 });
Effector flywheel  = Effector(MotorGroup({ FLYWHEEL_1, FLYWHEEL_2 }), { 10000, 12000, 0 });
Effector indexer   = Effector(MotorGroup({ INDEXER_MOTOR }), { 12000, 0 });