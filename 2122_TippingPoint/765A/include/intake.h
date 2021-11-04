#ifndef _INTAKE_
#define _INTAKE_

#include "main.h"

class Intake {
private:
  okapi::Motor m;
  okapi::IntegratedEncoder e;
  bool dir;
  bool moving;
  std::vector<int> encPositions;
  int prevCount = 0;
public:
  Intake(double port);
  void run(bool left, bool right, double speed);
  void setTarget(double enc);
  void stepAbsolute(int count, double speed);
  void addPosition(int pos);
  void step();
};

class Effectors {
private:
  okapi::Motor motors[4];
  okapi::IntegratedEncoder Encs[4];
  std::vector<int> encPositions[4];
public:
  void run(bool left, bool right, double speed);
}

#endif
