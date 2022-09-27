#ifndef PATH_BUILDER_H
#define PATH_BUILDER_H

#include "main.h"
#include "drive.h"
#include "pid.h"
#include "odometry.h"
#include <functional>
#include "vector"

struct Callback {
    okapi::Point target;
    std::function<void()> func;
    okapi::QLength tol;
};

enum Direction {
    FORWARD = 1,
    REVERSE = -1
};

class Movement {

    friend class PathBuilder;

    private:
        okapi::Point target;
        okapi::QTime time;
        Direction dir;

        // Default values
        PIDGAINS headingGains  = {0.05, 0, 0};
        PIDGAINS distanceGains = {0.05, 0.00001, 0};
        double headingMax      = 1.0;
        double distanceMax     = 1.0;
        double headingSlew     = 0.1;
        double distanceSlew    = 0.1;

        okapi::QLength headingCorrectionTol = 12_in;
        okapi::QLength tol     = 2.5_in;
        void execute(std::vector<Callback>& callbacks);

    public:
        Movement(const okapi::Point& _target, const okapi::QTime& _time, const Direction& _dir) : target(_target), time(_time), dir(_dir) {}


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

       PIDGAINS turnGains = {0.015, 0.00001, 0.0003};
       double turnSlew = 0.1;
       double turnMax = 1.0;
       okapi::QAngle tol = 2_deg;

   public:

       Turn(const okapi::QAngle& _target, const okapi::QTime& _time)
       : target(_target), time(_time) {}

       Turn(const okapi::Point& _target, const okapi::QTime& _time)
       : target(Odometry::pointingTo(_target)), time(_time) {}

       void execute(const Direction& dir);
       void inPlace(const Direction& dir);

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
        std::vector<Movement> paths;
        std::vector<Callback> callbacks;

    public:

        PathBuilder& addPath(const Movement& data){
            paths.push_back(data);
            return *this;
        }

        PathBuilder& addCallback(const okapi::Point& target,const std::function<void()>& func,const okapi::QLength& tol = 4_in){
            Callback c = { target, func, tol };
            callbacks.push_back(c);
            return *this;
        }

        void execute();
};

#endif