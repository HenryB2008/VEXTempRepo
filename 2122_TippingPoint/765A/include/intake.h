#ifndef _INTAKE_
#define _INTAKE_

#include "main.h"


//Class for intake and four bar actuation
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
