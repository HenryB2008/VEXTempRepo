#include "pid.h"

//constructor sets constants

PID::PID(PIDConst constants) {
  this->kp = constants.kp;
  this->ki = constants.ki;
  this->kd = constants.kd;
}

//steps PI algo with error passed in (no D)
double PID::step(double err) {
  totalerr+=err;
  double val = kp*err + totalerr*ki;
  return val;
}
