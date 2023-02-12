#ifndef TURN_H
#define TURN_H

#include "chassis.h"
#include "logistic.h"
#include "main.h"
#include "pid.h"

#include <functional>
#include <queue>
#include <vector>


class Turn {

   private:

       okapi::QAngle target;
       okapi::QTime time;
       PIDGAINS turnGains = {0.02, 0.00065, 0.0135};
       double turnSlew = 0.1;
       double turnMax = 1.0;
       double integralMax = 0.2;
       okapi::QAngle tol = 0.25_deg;

   public:

       Turn(const okapi::QAngle& _target, const okapi::QTime& _time)
       : target(_target), time(_time) {}

       Turn(const okapi::Point& _target, const okapi::QTime& _time)
       : target(Chassis::Odometry::pointingTo(_target)), time(_time) {}

       void execute(const Direction& dir);

       /*

       --------- CONTROLLER CHAINING PATTERN ---------

       */

       Turn& withTurnGains(const PIDGAINS& turn) {turnGains = turn; return *this;}
       Turn& withTurnMax(const double& max) {turnMax = max; return *this;}
       Turn& withTurnSlew(const double& slew) {turnSlew = slew; return *this;}
       Turn& withTolerance(const okapi::QAngle& _tol) {this->tol = _tol; return *this;}

};

#endif