#include "pid.h"

PIDController::PIDController(const PIDGAINS& gains, const double& slew,const double& maxOutput) {
    // Copy PID Gains into PIDController
    this->kp = gains.kp;
    this->ki = gains.ki;
    this->kd = gains.kd;
    this->slew = slew;
    this->maxOutput = maxOutput;
    prevError = 0;
    prevOutput = 0;
    errorSum = 0;
}

PIDGAINS copyGains(const PIDGAINS& other){
  return {other.kp, other.ki, other.kd};
}

double PIDController::step(const double& error) {

    errorSum += error; // sum of the error for ki

    double rawOutput = error * kp + errorSum * ki + (error - prevError) * kd; // raw output from PIDGAINS

    double finalOutput; // value which is returned

    if(rawOutput > 0){ // positive rawOutput case

        finalOutput = std::clamp(rawOutput, prevOutput - slew, std::min(maxOutput, prevOutput + slew)); // clamped for slew and so finalOutput does not exceed maxOutput

    } else if (rawOutput < 0){ // negative rawOutput case

        finalOutput = std::clamp(rawOutput, std::max(-maxOutput, prevOutput - slew), prevOutput + slew); // clamped for slew and so finalOutput does not exceed -maxOutput

    } else { // rawOutput is 0

        finalOutput = 0; // step will return 0
    }

    prevError = error; // current error is now prevError : used for kd

    prevOutput = finalOutput; // the output to be returned will be set to prevOutput for the slew limiter

    return finalOutput;
}