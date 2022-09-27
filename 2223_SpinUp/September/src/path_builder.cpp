#include "path_builder.h"

void Movement::execute(std::vector<Callback>& callbacks) {

  PIDController headingController  = PIDController(headingGains, headingSlew, headingMax);
  PIDController distanceController = PIDController(distanceGains, distanceSlew, distanceMax);

  std::cout << "Start movement" << std::endl;


  // Arbitrary values
  double distanceError = 999999999;
  double headError     = 999999999;

  double distancePower;
  double headPower;

  double distanceTol = tol.convert(okapi::inch);

  double endTime = pros::millis() + time.convert(okapi::millisecond);

  auto targetTheta = Odometry::pointingTo(target);

  double headingCorrectionTolInches = headingCorrectionTol.convert(okapi::inch);

  while (distanceError > distanceTol && pros::millis() < endTime) {
      distanceError = Odometry::magError(target).convert(okapi::inch);

      // if we are outside a certain distance, recalculate theta
      if (distanceError > headingCorrectionTolInches)
        targetTheta = Odometry::pointingTo(target);

      if(dir == REVERSE){
          targetTheta += 180_deg;
      }

      headError = Drive::thetaError(targetTheta).convert(okapi::degree);

      Odometry::printPos();

      //auto curPos = Drive::getPos();
      //std::cout << "O: " << curPos.theta.convert(okapi::degree);

      // Used to make sure robot moves in the right direction to reach the target point
      distancePower = dir * distanceController.step(distanceError);
      headPower     = headingController.step(headError);

      Drive::arcade(distancePower, headPower);

      // if there is at least one callback to handle
      if (!callbacks.empty()) {
          Callback current = callbacks.at(0);

          if(Drive::magError(current.target) < current.tol) {
              current.func();
              callbacks.erase(callbacks.begin());

              std::cout << "Callback called" << std::endl;
          }
      }

      pros::delay(10);

    }

}

void Turn::execute(const Direction& dir){

  PIDController Turn = PIDController(turnGains, turnSlew, turnMax);

  double turnError = 999999999;

  double turnPower;

  double turnTol = tol.convert(okapi::degree);

  double endTime = pros::millis() + time.convert(okapi::millisecond);

  if(dir == REVERSE){
      target += 180_deg;
  }

  while(abs(turnError) > turnTol && pros::millis() < endTime) {

      Odometry::printPos();

      turnError = Drive::thetaError(target).convert(okapi::degree);

      turnPower = Turn.step(turnError);

      Drive::arcade(0, turnPower);

      pros::delay(10);

  }

  Drive::arcade(0,0);

}

void Turn::inPlace(const Direction &dir) {
    PIDController Turn = PIDController(turnGains, turnSlew, 0.5);
    PIDController distanceController = PIDController({0.035, 0, 0}, 0.1, 0.6);

    double distanceError = 999999999;
    double turnError = 999999999;

    double distancePower;
    double turnPower;

    double turnTol = tol.convert(okapi::degree);

    double endTime = pros::millis() + time.convert(okapi::millisecond);

    if (dir == REVERSE) {
        target += 180_deg;
    }

    okapi::Point ogPos = {Odometry::getPos().x, Odometry::getPos().y};

    while(abs(turnError) > turnTol && pros::millis() < endTime) {

        Odometry::printPos();

        distanceError = Drive::magError(ogPos).convert(okapi::inch);
        turnError     = Drive::thetaError(target).convert(okapi::degree);

        distancePower = distanceController.step(distanceError);
        turnPower     = Turn.step(turnError);

        Drive::arcade(distancePower, turnPower);

        pros::delay(10);

    }

    Drive::arcade(0,0);
}

void PathBuilder::execute() {

    // Loop through each path

    for (Movement& path : paths) {

        path.execute(callbacks);

        std::cout << "End movement" << std::endl;
    }

    std::cout << "Completed all movements" << std::endl;

    Drive::arcade(0, 0);
}