#ifndef _EFFECTORS_
#define _EFFECTORS_

#include "main.h"

class Effectors {
private:
  okapi::Motor motors[3] = {okapi::Motor(1), okapi::Motor(10), okapi::Motor(9)};
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
};

#endif
