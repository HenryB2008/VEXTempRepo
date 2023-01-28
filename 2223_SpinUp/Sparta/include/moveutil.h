#ifndef MOVEUTIL_H
#define MOVEUTIL_H

#include "path_builder.h"
#include "main.h"

namespace MoveUtil {

    void moveTo(
        const okapi::Point& _target,
        const okapi::QTime& timeout,
        const Direction& dir,
        double distanceMax,
        std::queue<Callback> callbacks = {}
    );

    void turnTo(
        const okapi::Point& _target,
        const okapi::QTime& timeout,
        const Direction& dir, 
        const PIDGAINS& gains = {0.02, 0.00065, 0.0135}
    );

    void turnTo(
        const okapi::QAngle& _angle, 
        const okapi::QTime& timeout,
        const Direction& dir,
        const PIDGAINS& gains = {0.02, 0.00065, 0.0135}
    );
        
}

#endif