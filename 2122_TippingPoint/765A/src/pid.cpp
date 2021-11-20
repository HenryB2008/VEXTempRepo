#include "pid.h"

PID::PID(PIDConst constants) {
  this->kp = constants.kp;
  this->ki = constants.ki;
  this->kd = constants.kd;
}

double PID::step(double err) {
  totalerr+=err;
  double val = kp*err + totalerr*ki;
  return val;
}
