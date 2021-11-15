#ifndef _EFFECTORS_
#define _EFFECTORS_

#include "main.h"

class Effectors {
private:
  okapi::Motor motors[3] = {okapi::Motor(17), okapi::Motor(16), okapi::Motor(7)};
  std::vector<int> encPositions[3];
  int prevCounts[3] = {0, 0, 0};
  bool goalFinal = false;
  bool spikeUp = false;
public:
  Effectors();
  void run(bool left, bool right, double speed);
  void step(int buttons[3], double speeds[3]);
  void addPosition(int lift, int pos);
  void runOne(int lift, double pos);
};

#endif
