#include "drive.h"

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

    auto imu = pros::Imu(IMU_PORT);

    void arcade(const double& forward, const double& yaw) {
        chassis->getModel()->arcade(forward, yaw);
    }

    void setBrakeMode(const okapi::AbstractMotor::brakeMode& bm) {
        chassis->getModel()->setBrakeMode(bm);
    }

    void calibrateIMU() {
        imu.reset();

        // Loop until the IMU is done calibrating
        while (imu.get_status() & pros::c::E_IMU_STATUS_CALIBRATING) {
            pros::lcd::print(1, "IMU calibrating...");
            pros::delay(10);
        }
    }

    void resetOdometry() {
        imu.set_heading(0);
    }

    void printPos() {
        pros::lcd::print(1, "Heading: %f", imu.get_heading());
    }
};