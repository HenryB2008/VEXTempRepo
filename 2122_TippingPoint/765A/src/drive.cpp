#include "drive.h"

Drive::Drive() {
  chassis = ChassisControllerBuilder()
            .withMotors(TOP_LEFT_MOTOR, -TOP_RIGHT_MOTOR, -BOTTOM_RIGHT_MOTOR, BOTTOM_LEFT_MOTOR)
            .withDimensions(
              AbstractMotor::gearset::green,
			        ChassisScales({WHEELDIM, WHEELTRACK}, imev5GreenTPR))
            .withSensors(
              ADIEncoder( // left encoder
                  LEFT_TRACKING_WHEEL_TOP,
                  LEFT_TRACKING_WHEEL_BOTTOM,
                  true
              ),
              ADIEncoder( // right encoder
                  RIGHT_TRACKING_WHEEL_TOP,
                  RIGHT_TRACKING_WHEEL_BOTTOM,
                  true
              ),
               ADIEncoder( // back encoder
                   BACK_TRACKING_WHEEL_TOP,
                   BACK_TRACKING_WHEEL_BOTTOM,
                   true
               )
          )
          .withOdometry(
            ChassisScales({ODOMWHEELDIM, ODOMTRACK, ODOMBACKDISTANCE, ODOMWHEELDIM}, quadEncoderTPR)
          )

        .buildOdometry();
        chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);
}





double Drive::getX() {
  return chassis->getState().x.convert(inch);
}

double Drive::getY() {
  return chassis->getState().y.convert(inch);
}

double Drive::getHeading() {
  return chassis->getState().theta.convert(degree);
}

void Drive::run(double forward, double strafe, double heading) {
  std::shared_ptr<okapi::XDriveModel> xDrive = std::static_pointer_cast<okapi::XDriveModel>(chassis->getModel());
  if(forward+strafe+heading>1) {
    forward/=(forward+strafe+heading);
    strafe/=(forward+strafe+heading);
    heading/=(forward+strafe+heading);
  }
  printf("%f %f %f\n", strafe, forward, heading);
  xDrive->xArcade(strafe, forward, heading);
}

void Drive::runTankArcade(double forward, double turn) {
  chassis->getModel()->arcade(forward, turn);
}

void Drive::runTank(double left, double right) {
  chassis->getModel()->tank(left, right);
}



okapi::OdomState Drive::getState() {
  return chassis->getState();
}
