#ifndef _PID_
#define _PID_


//generic constants structure
struct PIDConst {
  double kp, ki, kd;
};

//generic PID class for all PID movements
class PID {
private:
  double kp;
  double ki;
  double kd;
  double totalerr;
public:
  PID(PIDConst constants);
  double step(double err);
};

#endif
