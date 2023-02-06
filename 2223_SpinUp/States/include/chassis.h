#ifndef CHASSIS_H
#define CHASSIS_H

#include "okapi/api/chassis/controller/chassisScales.hpp"
#include "okapi/api/units/QAngle.hpp"

#include <cmath>

#include "main.h"
#include "ports.h"

constexpr okapi::QLength RIGHT_TRACKING_WHEEL_DIM = 2.855865_in;
constexpr okapi::QLength MID_TRACKING_WHEEL_DIM = 2.80061_in;
constexpr okapi::QLength RIGHT_TRACKING_WHEEL_TRACK = 3.61346_in;
constexpr okapi::QLength MID_TRACKING_WHEEL_TRACK = 4.95163_in;

constexpr okapi::QLength WHEEL_DIM  = 4_in;
constexpr okapi::QLength WHEEL_TRACK = 14_in;

using QAngle = okapi::QAngle;

namespace Chassis {

    // Controls forward and turn movements
    void arcade(const double forward, const double yaw);

    // Sets how the robot will brake during movements
    void setBrakeMode(const okapi::AbstractMotor::brakeMode bm);

    // Moves forward at a set power for a set time
    void timedForward(const double power, const double time);

    // Turns at a set power for a set time
    void timedTurn(const double power, const double time);

    /*

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

    */

};

#endif