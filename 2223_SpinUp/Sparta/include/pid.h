#ifndef PID_H
#define PID_H

#include <algorithm>
#include "main.h"

struct PIDGAINS { // Gains for PID, used for auton movement and other devices which require gradual stopping
    double kp; // Proportional constant, generally 0.xx --> primary source of power
    double ki; // Integral constant, generally 0.xxxx or 0.xxxxx --> used as booster for the end of movements to ensure bot does not slow down too much
    double kd; // Derivative constant, generally 0.xxx or 0.xxxx --> used as dampener at the end
};

// kp, ki, and kd into a new PIDGAINS struct
PIDGAINS copyGains(const PIDGAINS& other);

class PIDController { // Class which takes in an error and converts it into a uable power
  private:
    double kp; // Proportional constant, generally 0.xx --> primary source of power
    double ki; // Integral constant, generally 0.xxxx or 0.xxxxx --> used as booster for the end of movements to ensure bot does not slow down too much
    double kd; // Derivative constant, generally 0.xxx or 0.xxxx --> used as dampener at the end
    double slew; // The absolute value of the difference between consecutive returns of step (unless step returns 0 due to error being less than or equal to tolerance) will never be more than slew
    double prevError; // Previous error (used for kd)
    double prevOutput; // Previous return of step (used for slew limiter)
    double errorSum; // Sum of errors from step (used for ki)
    double maxOutput; // The absolute value of the return value from step will never be more than maxOutput
  public:
    ~PIDController() = default; // Destructor
    PIDController(const PIDGAINS& gains, const double& slew, const double& maxOutput); // Constructor (gains, slew, maxOutput)
    double step(const double& error); // Converts error into a usable value, such as motor power
};

#endif