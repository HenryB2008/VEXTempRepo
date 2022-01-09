#ifndef _INTAKE_
#define _INTAKE_

#include "main.h"

class Intake {
private:
  okapi::Motor m;
  bool dir;
  bool moving;
  std::vector<int> encPositions;
  int prevCount = 0;
  int upper;
  int lower;
  bool limits = false;
public:
  Intake(double port);
  void run(bool left, bool right, double speed);
  void moveTarget(double enc);
  void setTarget(double enc);
  void stepAbsolute(int count, double speed);
  void addPosition(int pos);
  void step();
  void setLimits(int upper, int lower);
};



#endif
