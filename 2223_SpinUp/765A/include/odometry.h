#ifndef ODOMETRY_H
#define ODOMETRY_H

#include "main.h"
#include "drive.h"
#include "ports.h"

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