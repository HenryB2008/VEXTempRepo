#ifndef _EFFECTORS_
#define _EFFECTORS_

#include "main.h"

//class for two-bar actuation
class Effectors {
private:
  //two bar port
  okapi::Motor motors[1] = {okapi::Motor(9)};
  int encPositions[3][3];
  int prevCounts[3];
  bool goalFinal = false;
  bool spikeUp = false;
public:
  Effectors();
  void run(bool left, bool right, double speed);
  void step(int buttons[3], double speeds[3]);
  void addPosition();
  void runOne(int lift, int pos);
  void runOneToPosition(int lift, int pos);
};

#endif
