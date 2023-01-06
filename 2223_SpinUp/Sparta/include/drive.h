#ifndef DRIVE_H
#define DRIVE_H

#include "main.h"
#include "ports.h"
#include "odometry.h"
#include "pid.h"
#include "okapi/api/chassis/controller/chassisScales.hpp"

// Values required for ChassisController instantiation

constexpr okapi::QLength WHEEL_DIM  = 4_in;
constexpr okapi::QLength WHEEL_TRACK = 14_in;

namespace Drive {

    // Controls forward and turn movements

    void arcade(const double forward, const double yaw);

    // Sets how the robot will brake during movements

    void setBrakeMode(const okapi::AbstractMotor::brakeMode bm);

    void timedForward(const double power, const double time);
    void timedTurn(const double power, const double time);

};

#endif