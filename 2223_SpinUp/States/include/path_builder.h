#ifndef PATH_BUILDER_H
#define PATH_BUILDER_H

#include "chassis.h"
#include "logistic.h"
#include "main.h"
#include "pid.h

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


class Turn {

   private:

       okapi::QAngle target;
       okapi::QTime time;

       PIDGAINS turnGains = {0.014, 0, 0};
       double turnSlew = 0.1;
       double turnMax = 1.0;
       okapi::QAngle tol = 1_deg;

   public:

       Turn(const okapi::QAngle& _target, const okapi::QTime& _time)
       : target(_target), time(_time) {}

       Turn(const okapi::Point& _target, const okapi::QTime& _time)
       : target(Odometry::pointingTo(_target)), time(_time) {}

       void execute(const Direction& dir);
       void executeLogistic(const Direction& dir, const PIDGAINS& logisticGains = {0.02, 0.00065, 0.0135});
       void inPlace(const Direction& dir);
       void executeToPoint(const okapi::Point& _target, const Direction& dir);

       /*

       --------- CONTROLLER CHAINING PATTERN ---------

       */

       Turn& withTurnGains(const PIDGAINS& turn) {turnGains = turn; return *this;}
       Turn& withTurnMax(const double& max) {turnMax = max; return *this;}
       Turn& withTurnSlew(const double& slew) {turnSlew = slew; return *this;}
       Turn& withTolerance(const okapi::QAngle& _tol) {this->tol = _tol; return *this;}

};


class PathBuilder {
    private:
        /* Stored values that will later be executed */
        std::queue<Movement> paths;
        std::queue<Callback> callbacks;

    public:

        PathBuilder& addPath(const Movement& data){
            paths.push(data);
            return *this;
        }

        PathBuilder& addCallback(const okapi::Point& target,const std::function<void()>& func,const okapi::QLength& tol = 4_in){
            Callback c = { target, func, tol };
            callbacks.push(c);
            return *this;
        }

        void execute();
};

#endif