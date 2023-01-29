#include "path_builder.h"

void Movement::execute(std::queue<Callback> callbacks) {

  PIDController headingController  = PIDController(headingGains, headingSlew, 0.2, headingMax);
  PIDController distanceController = PIDController(distanceGains, distanceSlew, 0.2, distanceMax);

  std::cout << "Start movement" << std::endl;


  // Arbitrary values
  double distanceError = 999999999;
  double headError     = 999999999;

  double distancePower;
  double headPower;

  double distanceTol = tol.convert(okapi::inch);

  double endTime = pros::millis() + time.convert(okapi::millisecond);

  auto targetTheta = Odometry::pointingTo(target);

  while (distanceError > distanceTol && pros::millis() < endTime) {
      distanceError = Odometry::magError(target).convert(okapi::inch);
      std::cout << distanceError << std::endl;
      pros::c::lcd_print(4, "distanceError: %f inches", distanceError);

      // if we are outside 12_in distance, recalculate theta
      if (distanceError > 12)
        targetTheta = Odometry::pointingTo(target);

      if(dir == REVERSE){
          targetTheta += 180_deg;
      }

      headError = Odometry::thetaError(targetTheta).convert(okapi::degree);

      Odometry::printPos();

      //auto curPos = Drive::getPos();
      //std::cout << "O: " << curPos.theta.convert(okapi::degree);

      // Used to make sure robot moves in the right direction to reach the target point
      distancePower = dir * distanceController.step(distanceError);
      headPower     = headingController.step(headError);

      Drive::arcade(distancePower, headPower);

      // if there is at least one callback to handle
      if (!callbacks.empty()) {
          Callback current = callbacks.front();

          if(Odometry::magError(current.target) < current.tol) {
              current.func();
              callbacks.pop();

              std::cout << "Callback called" << std::endl;
          }
      }

      pros::delay(10);

    }

}

void Turn::execute(const Direction& dir){

  PIDController Turn = PIDController(turnGains, turnSlew, 0.2, turnMax);

  double turnError = 999999999;

  double turnPower;

  double turnTol = tol.convert(okapi::degree);

  double endTime = pros::millis() + time.convert(okapi::millisecond);

  if(dir == REVERSE){
      target += 180_deg;
  }

  while(abs(turnError) > turnTol && pros::millis() < endTime) {

      Odometry::printPos();

      turnError = Odometry::thetaError(target).convert(okapi::degree);

      turnPower = Turn.step(turnError);

      Drive::arcade(0, turnPower);

      pros::delay(10);

  }

  Drive::arcade(0,0);

}

void Turn::executeLogistic(const Direction& dir, const PIDGAINS& logisticGains) {
    PIDController Turn = PIDController(logisticGains, 0.1, 0.2, turnMax);

    double turnError = 999999999;

    double turnPower;
    Direction turnDir;

    double turnTol = tol.convert(okapi::degree);

    double endTime = pros::millis() + time.convert(okapi::millisecond);

    if(dir == REVERSE) {
        target += 180_deg;
    }

    double EXECUTE_DELAY_MS = 10;

    double thetaDiff = okapi::OdomMath::constrainAngle180(target - Odometry::getPos().theta).convert(okapi::degree);

    Logistic turnControl = Logistic(
        -time.convert(okapi::second) * 2, 
        time.convert(okapi::millisecond) / EXECUTE_DELAY_MS, 
        thetaDiff,
        Odometry::getPos().theta
    );

    std::cout << thetaDiff << std::endl;

    while(abs(thetaDiff) > 0.25 && pros::millis() < endTime) {

        thetaDiff = okapi::OdomMath::constrainAngle180(target - Odometry::getPos().theta).convert(okapi::degree);

        Odometry::printPos();

        turnError = (turnControl.step() - Odometry::getPos().theta).convert(okapi::degree);

        turnPower = Turn.step(turnError);

        Drive::arcade(0, turnPower);
    
        pros::delay(EXECUTE_DELAY_MS);

    }

    Drive::arcade(0,0);
}

void Turn::inPlace(const Direction &dir) {
    PIDController Turn = PIDController(turnGains, turnSlew,  0.2, 0.5);
    PIDController distanceController = PIDController({0.035, 0, 0}, 0.1,  0.2, 0.6);

    double distanceError = 999999999;
    double turnError = 999999999;

    double distancePower;
    double turnPower;

    double turnTol = tol.convert(okapi::degree);

    double endTime = pros::millis() + time.convert(okapi::millisecond);

    if (dir == REVERSE) {
        target += 180_deg;
    }

    target = okapi::OdomMath::constrainAngle180(target);

    okapi::Point ogPos = {Odometry::getPos().x, Odometry::getPos().y};

    while(abs(turnError) > turnTol && pros::millis() < endTime) {

        Odometry::printPos();

        distanceError = Odometry::magError(ogPos).convert(okapi::inch);
        turnError     = Odometry::thetaError(target).convert(okapi::degree);

        distancePower = distanceController.step(distanceError);
        turnPower     = Turn.step(turnError);

        Drive::arcade(distancePower, turnPower);

        pros::delay(10);

    }

    Drive::arcade(0,0);
}

void Turn::executeToPoint(const okapi::Point& _target, const Direction& dir){
    
    PIDController Turn = PIDController(turnGains, turnSlew, 0.2, turnMax);

    double turnError = 999999999;

    double turnPower;

    double turnTol = tol.convert(okapi::degree);

    double endTime = pros::millis() + time.convert(okapi::millisecond);

    while(abs(turnError) > turnTol && pros::millis() < endTime) {

        okapi::QAngle theta = Odometry::pointingTo(_target);

        if(dir == REVERSE){
            theta += 180_deg;
        }

        Odometry::printPos();

        turnError = Odometry::thetaError(theta).convert(okapi::degree);

        turnPower = Turn.step(turnError);

        Drive::arcade(0, turnPower);

        pros::delay(10);

    }

  Drive::arcade(0,0);
}

void PathBuilder::execute() {

    // Loop through each path

    while (!paths.empty()) {

        paths.front().execute(callbacks);
        paths.pop();

        std::cout << "End movement" << std::endl;
    }

    std::cout << "Completed all movements" << std::endl;

    Drive::arcade(0, 0);
}