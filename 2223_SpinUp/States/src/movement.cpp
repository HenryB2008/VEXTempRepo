#include "movement.h"

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

  auto targetTheta = Chassis::Odometry::pointingTo(target);

  while (distanceError > distanceTol && pros::millis() < endTime) {
      distanceError = Chassis::Odometry::magError(target).convert(okapi::inch);
      // std::cout << distanceError << std::endl;
      pros::c::lcd_print(4, "distanceError: %f inches", distanceError);

      // if we are outside 12_in distance, recalculate theta
      if (distanceError > 12)
        targetTheta = Chassis::Odometry::pointingTo(target);

      if(dir == REVERSE){
          targetTheta += 180_deg;
      }

      headError = Chassis::Odometry::thetaError(targetTheta).convert(okapi::degree);

      Chassis::Odometry::printPos();

      //auto curPos = Drive::getPos();
      //std::cout << "O: " << curPos.theta.convert(okapi::degree);

      // Used to make sure robot moves in the right direction to reach the target point
      distancePower = dir * distanceController.step(distanceError);
      headPower     = headingController.step(headError);

      Chassis::arcade(distancePower, headPower);

      // if there is at least one callback to handle
      if (!callbacks.empty()) {
          Callback current = callbacks.front();

          if(Chassis::Odometry::magError(current.target) < current.tol) {
              current.func();
              callbacks.pop();

              std::cout << "Callback called" << std::endl;
          }
      }

      pros::delay(10);

    }

}