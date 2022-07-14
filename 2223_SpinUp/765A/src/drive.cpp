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

    okapi::QLength magError(const okapi::Point& target) {
        okapi::OdomState pos = Odometry::getPos();
        okapi::QLength xError = target.x - pos.x;
        okapi::QLength yError = target.y - pos.y;

        return sqrt(xError * xError + yError * yError); // Hypotenuse
    }

    okapi::QAngle thetaError(const okapi::QAngle& target) {
        return okapi::OdomMath::constrainAngle180(target - Odometry::getPos().theta);
    }

    void turnInPlace(okapi::QAngle target) {
        // TODO: define these elsewhere
        PIDGAINS turnGains = {0.015, 0, 0.0};
        double turnSlew = 0.1;
        double turnMax = 1.0;
        okapi::QAngle tol = 2_deg;

        PIDController Turn = PIDController(turnGains, turnSlew, 0.5);
        PIDController distanceController = PIDController({0.035, 0, 0}, 0.1, 0.6);

        double distanceError = 999999999;
        double turnError = 999999999;

        double distancePower;
        double turnPower;

        double turnTol = tol.convert(okapi::degree);

        okapi::Point ogPos = {Odometry::getPos().x, Odometry::getPos().y};

        while(abs(turnError) > turnTol) {

            distanceError = magError(ogPos).convert(okapi::inch);
            turnError     = thetaError(target).convert(okapi::degree);

            distancePower = distanceController.step(distanceError);
            turnPower     = Turn.step(turnError);

            arcade(distancePower, turnPower);

            pros::delay(DELAY);

        }

        arcade(0, 0);
    }

    void pointToGoal() {
        // Testing point for pointing to the goal
        // TOOD: get this dynamically based on start position
        okapi::Point p = { 115_in, -4.5_in };

        okapi::OdomState curPos = Odometry::getPos();
        okapi::QAngle degrees   = (atan2((p.x - curPos.x).convert(okapi::meter), (p.y -  curPos.y).convert(okapi::meter)) * 1_rad); // Some tricky unit circle math

        okapi::QAngle res = okapi::OdomMath::constrainAngle180(90_deg - degrees); // 90_deg - degrees converts the angle from unit circle heading to airplane heading

        turnInPlace(res);
    }
};