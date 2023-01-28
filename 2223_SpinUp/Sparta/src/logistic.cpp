#include "logistic.h"
#include "okapi/api/units/QAngle.hpp"

Logistic::Logistic(double startTime, double numberOfIntervals, double thetaDifference, okapi::QAngle startTheta) {
    TIME_INCREMENT = abs(startTime) * 2 / numberOfIntervals;
    MAX_VAL = thetaDifference; // asymptotic to target theta, fastest at theta / 2

    currTime = startTime;
    idealTheta = 0_deg;
    this->startTheta = startTheta;
}

double Logistic::val(double max, double t) {
    return max / (1 + pow(M_E, -t));
}

double Logistic::derivative(double max, double t) {
    return max * (1 - val(1, t)) * val(1, t);
}

okapi::QAngle Logistic::step() {
    currTime += TIME_INCREMENT;

    idealTheta = val(MAX_VAL, currTime) * 1_deg;

    std::cout << idealTheta.convert(okapi::degree) << "\n";

    return startTheta + idealTheta;


    /*
    double targetTheta = 5;

    const double START_TIME = -5;
    const double TIME_INCREMENT = 0.1;

    double currMotorVel = val(targetTheta, START_TIME);

    for (double i = START_TIME; i <= -START_TIME; i += TIME_INCREMENT) {
        // std::cout << "(" << i << ", " << currMotorVel * TIME_INCREMENT << ")" << "\n";
        
        if (i < 0)
            currMotorVel += derivative(targetTheta, i - (TIME_INCREMENT / 2));
        else if (i >= 0)
            currMotorVel -= derivative(targetTheta, i - (TIME_INCREMENT / 2));
    }
    */
}