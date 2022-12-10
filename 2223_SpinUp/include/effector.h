#ifndef EFFECTOR_H
#define EFFECTOR_H

#include "main.h"
#include "okapi/api/device/motor/abstractMotor.hpp"
#include "okapi/impl/device/motor/motorGroup.hpp"
#include "ports.h"

using okapi::MotorGroup;

class Effector {
    private:
        MotorGroup motors;

        const std::vector<double> powers;

        int currPower = 0;

    public:
        Effector(const MotorGroup& motors, const std::vector<double>& powers);
        void runVoltage(double power);
        void toggle(const Direction& dir = FORWARD);
        void runWhenPressed(const okapi::ControllerDigital& b, double power);
};

extern Effector intake;
extern Effector flywheel;
extern Effector indexer;

#endif