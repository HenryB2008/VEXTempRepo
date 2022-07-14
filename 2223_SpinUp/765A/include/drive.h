#ifndef DRIVE_H
#define DRIVE_H

#include "main.h"
#include "ports.h"
#include "odometry.h"
#include "pid.h"
#include "okapi/api/chassis/controller/chassisScales.hpp"

#define WHEEL_DIM 4_in
#define WHEEL_TRACK 14_in

namespace Drive {

    void arcade(const double& forward, const double& yaw);

    void setBrakeMode(const okapi::AbstractMotor::brakeMode& bm);

    okapi::QLength magError(const okapi::Point& target);
    okapi::QAngle thetaError(const okapi::QAngle& target);

    void turnInPlace(okapi::QAngle target);

    void pointToGoal();
};

#endif