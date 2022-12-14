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

void Effector::runTimed(double power, double time) {
    motors.moveVoltage(power);
    pros::delay(time);
    motors.moveVoltage(0);
}

void Effector::toggle(const Direction& dir) {
    /*
        If the direction swapped, we assume we want to run the previous power in the opposite direction instead of going to the next
        Check if: 
        -- the direction DIDN'T swap
        -- the current index is less than 0 (starts at -1)
        -- the current power is 0 (we don't care about a change of direction in this case)
        If so, increment the current power index by 1
    */
    if (prevDir != -dir || currPowerIndex < 0 || powers.at(currPowerIndex) == 0)
        currPowerIndex += 1;

    // Cycle back to the beginning of the vector
    if (currPowerIndex == powers.size())
        currPowerIndex = 0;

    // Run the power at the current index
    runVoltage(powers.at(currPowerIndex) * dir);

    // Store the previous direction
    prevDir = dir;
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