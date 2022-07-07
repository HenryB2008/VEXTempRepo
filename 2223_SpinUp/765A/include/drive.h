#ifndef DRIVE_H
#define DRIVE_H

#include "main.h"
#include "ports.h"

#define WHEEL_DIM 4_in
#define WHEEL_TRACK 14_in

namespace Drive {

    void arcade(const double& forward, const double& yaw);

    void setBrakeMode(const okapi::AbstractMotor::brakeMode& bm);
};

#endif