#include "main.h"
#include "okapi/api/units/QAngle.hpp"
#include <iostream>
#include <cmath>

#ifndef LOGISTIC_H
#define LOGISTIC_H

// Class representing a logistic (sigmoid) curve, returning an angle for each time increment
class Logistic {

    private:

        // represnted in milliseconds, usually 10 milliseconds
        double TIME_INCREMENT;

        // difference between start and target heading, in degrees
        double MAX_VAL;

        double currTime;
        okapi::QAngle idealTheta;
        okapi::QAngle startTheta;

    public:
        Logistic(double startTime, double numberOfIntervals, double thetaDifference, okapi::QAngle startTheta);

        double val(double max, double t);
        double derivative(double max, double t);

        okapi::QAngle step();
};

#endif