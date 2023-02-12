#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "chassis.h"
#include "logistic.h"
#include "main.h"
#include "pid.h"

#include <functional>
#include <queue>
#include <vector>

// Structure representing a callback
struct Callback {

    // Execute when near this point
    okapi::Point target;

    // Execute this function
    std::function<void()> func;

    // Execute when within {tol} distance from targets
    okapi::QLength tol;

};

// Represents a singular movement
class Movement {

    // Allows the PathBuilder class to access the private members of Movement
    friend class PathBuilder;

    private:

        // The target point to be reached
        okapi::Point target;

        // If the time elapsed is greater than time the movement will end
        okapi::QTime time;

        // Direction of the movement (FORWARD or REVERSE)
        Direction dir;

        // Default gains for adjusting theta differences
        PIDGAINS headingGains  = {0.05, 0, 0};

        // DEfualt gains for moving forward/backward
        PIDGAINS distanceGains = {0.05, 0.00001, 0};

        // Maximum power which can be dedicated to heading correction 
        double headingMax      = 1.0;

        // Maximum power which can be dedicated to moving forward/backward
        double distanceMax     = 1.0;

        // Maximum change in heading power between individual runs of the movement loop
        double headingSlew     = 0.1;

        // Maximum change in movement power between individual runs of the movement loop
        double distanceSlew    = 0.1;

        // If the distance between a robot 
        okapi::QLength tol     = 2.5_in;

    public:
        Movement(const okapi::Point& _target, const okapi::QTime& _time, const Direction& _dir) : target(_target), time(_time), dir(_dir) {}

        void execute(std::queue<Callback> callbacks);

        Movement& withHeadingGains(const PIDGAINS& head) {headingGains = head; return *this;}
        Movement& withDistGains(const PIDGAINS& dist)  {distanceGains = dist; return *this;}

        Movement& withHeadingMax(const double& max) {headingMax = max; return *this;}
        Movement& withDistanceMax(const double& max) {distanceMax = max; return *this;}

        Movement& withHeadingSlew(const double& slew) {headingSlew = slew; return *this;}
        Movement& withDistanceSlew(const double& slew) {distanceSlew = slew; return *this;}

        Movement& withTolerance(const okapi::QLength& tol) {this->tol = tol; return *this;}

};

#endif