#include "pid.h"

PID::PID(double kp, double ki, double kd) {
  this->kp = kp;
  this->ki = ki;
  this->kd = kd;
}

double PID::step(double err) {
  totalerr+=err;
  double val = kp*err + totalerr*ki;
  return val;
}
