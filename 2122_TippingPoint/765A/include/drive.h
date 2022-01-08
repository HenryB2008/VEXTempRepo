#ifndef _DRIVE_
#define _DRIVE_

#define WHEELDIM 4_in
#define WHEELTRACK 10_in

#include "main.h"
#include "ports.h"

class Drive {
private:
  std::shared_ptr<okapi::OdomChassisController> chassis;
  int speedfactor;
public:
  Drive();
  double getX();
  double getY();
  double getHeading();
  void run(double forward, double strafe, double turn);
  okapi::OdomState getState();
  void runWithController();
  void runTankArcade(double forward, double turn);
  void runTank(double left, double right);
  void reverseOrientation(int ori);
  void setMode(okapi::AbstractMotor::brakeMode brakeMode);
};

#endif
