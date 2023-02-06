#include "chassis.h"

namespace Chassis {
    // We define the chassis and IMU only in the source file so that it is essentially "private"
    auto chassis = okapi::ChassisControllerBuilder()
        .withMotors(
            okapi::MotorGroup({ TOP_LEFT_MOTOR, MID_LEFT_MOTOR, BOTTOM_LEFT_MOTOR }),
            okapi::MotorGroup({ TOP_RIGHT_MOTOR, MID_RIGHT_MOTOR, BOTTOM_RIGHT_MOTOR })
        )
        .withDimensions(
            okapi::AbstractMotor::gearset::green,
            okapi::ChassisScales({ WHEEL_DIM, WHEEL_TRACK }, okapi::imev5GreenTPR)
        )
        .build();


    void arcade(const double forward, const double yaw) {
        chassis->getModel()->arcade(forward, yaw);
    }

    void setBrakeMode(const okapi::AbstractMotor::brakeMode bm) {
        chassis->getModel()->setBrakeMode(bm);
    }

    void timedForward(const double power, const double time) {
        arcade(power, 0);
        pros::delay(time);
        arcade(0, 0);
    }

    void timedTurn(const double power, const double time) {
        arcade(0, power);
        pros::delay(time);
        arcade(0, 0);
    }

    /*

    namespace Odometry {

        okapi::OdomState curPos;

        pros::Imu inertial(IMU_PORT);

        okapi::ADIEncoder rightEnc(RIGHT_TRACKING_WHEEL_TOP, RIGHT_TRACKING_WHEEL_BOTTOM, true);
        okapi::ADIEncoder midEnc(MID_TRACKING_WHEEL_TOP, MID_TRACKING_WHEEL_BOTTOM, false);

        pros::Mutex inertialMutex;

        pros::Mutex positionMutex;

        pros::Mutex encs;

        double rightEncVal;

        double midEncVal;

        void run() {

            // Tick diffs

            encs.take();
            double right_tick = (rightEnc.get());
            double mid_tick   = (midEnc.get());
            encs.give();

            // Movements in inches

            okapi::QLength delta_right = (right_tick - rightEncVal) / 360 * M_PI * RIGHT_TRACKING_WHEEL_DIM;
            okapi::QLength delta_mid   = (mid_tick - midEncVal)     / 360 * M_PI * MID_TRACKING_WHEEL_DIM;

            // Reset previous values

            rightEncVal = right_tick;
            midEncVal   = mid_tick;

            // Get heading

            positionMutex.take();
            QAngle curHeading   = getHeading();
            QAngle deltaHeading = okapi::OdomMath::constrainAngle180(curHeading - curPos.theta);
            positionMutex.give();

            okapi::QLength localXChange, localYChange;

            if (deltaHeading == 0_deg){
                localXChange = delta_right;
                localYChange = delta_mid;
            } else {
                auto factor = 2 * sin(deltaHeading / 2);
                
                localXChange = factor * (delta_right / deltaHeading.convert(okapi::radian) + RIGHT_TRACKING_WHEEL_TRACK);
                localYChange = factor * (delta_mid   / deltaHeading.convert(okapi::radian) + MID_TRACKING_WHEEL_TRACK);
            }

            okapi::QAngle avgTheta = curPos.theta + (deltaHeading / 2);
            
            okapi::QLength globalXChange = (localXChange * cos(avgTheta)) - (localYChange * sin(avgTheta));
            okapi::QLength globalYChange = (localXChange * sin(avgTheta)) + (localYChange * cos(avgTheta));

            positionMutex.take();
            curPos.x += globalXChange;
            curPos.y += globalYChange;
            curPos.theta = okapi::OdomMath::constrainAngle180(curPos.theta + deltaHeading);
            positionMutex.give();

            pros::lcd::print(5, "Delta theta: %f", deltaHeading.convert(okapi::degree));
            pros::lcd::print(6, "Delta right: %f", delta_right.convert(okapi::inch));

        }

        void init() {
            setPos({ 0_in, 0_in, 0_deg });

            encs.take();
            rightEnc.reset();
            midEnc.reset();
            encs.give();

            rightEncVal = 0;
            midEncVal   = 0;

            calibrateInertial();

            pros::Task task{[] {
                while (true) {
                    run();
                    Odometry::printPos();
                    pros::delay(1);
                }
            }};
        }

        void calibrateInertial() {
            inertialMutex.take();
            inertial.reset();

            // Loop until the inertial is done calibrating
            // TODO: maybe try just doing while (interial.is_calibrating()) ?
            while (inertial.get_status() & pros::c::E_IMU_STATUS_CALIBRATING) {
                pros::lcd::print(1, "inertial calibrating...");
                pros::delay(10);
            }

            inertial.set_data_rate(DELAY);
            inertialMutex.give();
        }

        void resetHeading() {
            inertialMutex.take();
            // Round the current heading to the nearest 90 degrees (0, 90, 180, 270, or 360)
            int nearest90 = round(inertial.get_heading() / 90) * 90;
            inertial.set_heading(nearest90);
            inertialMutex.give();
        }

        QAngle getHeading() {
            inertialMutex.take();
            QAngle heading = okapi::OdomMath::constrainAngle180(inertial.get_heading() * 1_deg);
            inertialMutex.give();
            return heading;
        }

        okapi::OdomState getPos() {
            positionMutex.take();
            okapi::OdomState returnOs(curPos);
            positionMutex.give();
            return returnOs;
        }

        void setPos(const okapi::OdomState& os) {
            positionMutex.take();
            curPos = os;
            positionMutex.give();

            inertialMutex.take();
            inertial.set_heading(okapi::OdomMath::constrainAngle360(os.theta).convert(okapi::degree));
            inertialMutex.give();
        }

        void printPos() {
            auto curPos = getPos();
            pros::lcd::print(0, "X: %f in", curPos.x.convert(okapi::inch));
            pros::lcd::print(1, "Y: %f in", curPos.y.convert(okapi::inch));
            pros::lcd::print(2, "Theta: %f deg", curPos.theta.convert(okapi::degree));
            encs.take();
            pros::lcd::print(3, "Right enc: %f", rightEnc.get());
            pros::lcd::print(4, "Mid enc: %f", midEnc.get());
            encs.give();

        }

        okapi::QLength magError(const okapi::Point& target) {
            okapi::OdomState pos = getPos();
            okapi::QLength xError = target.x - pos.x;
            okapi::QLength yError = target.y - pos.y;

            return sqrt(xError * xError + yError * yError); // Hypotenuse
        }

        okapi::QAngle thetaError(const okapi::QAngle& target) {
            return okapi::OdomMath::constrainAngle180(target - getPos().theta);
        }

        okapi::QAngle pointingTo(const okapi::Point& p) {
            okapi::OdomState curPos = getPos();
            okapi::QAngle degrees   = (atan2((p.x - curPos.x).convert(okapi::meter), (p.y -  curPos.y).convert(okapi::meter)) * 1_rad); // Some tricky unit circle math

            return okapi::OdomMath::constrainAngle180(90_deg - degrees); // 90_deg - degrees converts the angle from unit circle heading to airplane heading
        }

    };

    */

};