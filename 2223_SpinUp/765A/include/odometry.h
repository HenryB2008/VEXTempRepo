#ifndef ODOMETRY_H
#define ODOMETRY_H

#include "main.h"
#include "drive.h"
#include "ports.h"

#define RIGHT_TRACKING_WHEEL_DIM 2.5_in
#define MID_TRACKING_WHEEL_DIM 2.5_in

#define RIGHT_TRACKING_WHEEL_TRACK -2.1227567_in
#define MID_TRACKING_WHEEL_TRACK 4.56944444_in

using QAngle = okapi::QAngle;

namespace Odometry {
    void run();
    
    void init(const okapi::OdomState& os);

    void calibrateInertial();

    void resetOdometry();

    QAngle getHeading();

    void printPos();
};

#endif