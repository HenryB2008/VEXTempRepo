#ifndef ODOMETRY_H
#define ODOMETRY_H

#include "main.h"
#include "drive.h"
#include "ports.h"

using QAngle = okapi::QAngle;

namespace Odometry {
    void run();
    
    void init();

    void calibrateInertial();

    void resetHeading();

    QAngle getHeading();
    okapi::OdomState getPos();

    void setPos(const okapi::OdomState& os);

    okapi::QLength magError(const okapi::Point& target);
    okapi::QAngle thetaError(const okapi::QAngle& target);

    okapi::QAngle pointingTo(const okapi::Point& p);

    void printPos();
};

#endif