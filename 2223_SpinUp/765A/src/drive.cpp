#include "drive.h"
#include "okapi/api/chassis/controller/chassisScales.hpp"

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
};