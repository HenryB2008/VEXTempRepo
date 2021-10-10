#ifndef _PID_
#define _PID_


struct PIDConst {
  double kp, ki, kd;
};


class PID {
private:
  double kp;
  double ki;
  double kd;
  double totalerr;
public:
  PID(double kp, double ki, double kd);
  double step(double err);
};

#endif
