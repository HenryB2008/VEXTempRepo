#include "drive.h"
#include "pid.h"

namespace Drive {
    // We define the chassis and IMU only in the source file so that it is essentially "private"
    auto chassis = okapi::ChassisControllerBuilder()
        .withMotors(
            okapi::MotorGroup({ TOP_LEFT_MOTOR, BOTTOM_LEFT_MOTOR }),
            okapi::MotorGroup({ TOP_RIGHT_MOTOR, BOTTOM_RIGHT_MOTOR })
        )
        .withDimensions(
            okapi::AbstractMotor::gearset::green,
            okapi::ChassisScales({ WHEEL_DIM, WHEEL_TRACK }, okapi::imev5GreenTPR)
        )
        .build();


    void arcade(const double& forward, const double& yaw) {
        chassis->getModel()->arcade(forward, yaw);
    }

    void setBrakeMode(const okapi::AbstractMotor::brakeMode& bm) {
        chassis->getModel()->setBrakeMode(bm);
    }

    void timedForward(const double &power, const double &time) {
        arcade(power, 0);
        pros::delay(time);
        arcade(0, 0);
    }

    void timedTurn(const double &power, const double& time) {
        arcade(0, power);
        pros::delay(time);
        arcade(0, 0);
    }

    okapi::QLength magError(const okapi::Point& target) {
        okapi::OdomState pos = Odometry::getPos();
        okapi::QLength xError = target.x - pos.x;
        okapi::QLength yError = target.y - pos.y;

        return sqrt(xError * xError + yError * yError); // Hypotenuse
    }

    okapi::QAngle thetaError(const okapi::QAngle& target) {
        return okapi::OdomMath::constrainAngle180(target - Odometry::getPos().theta);
    }
};