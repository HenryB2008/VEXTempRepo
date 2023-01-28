#include "moveutil.h"

namespace MoveUtil {

    void moveTo(
        const okapi::Point& _target,
        const okapi::QTime& timeout,
        const Direction& dir,
        double distanceMax,
        std::queue<Callback> callbacks
    ) {

        Movement(_target, timeout, dir)
            .withDistanceMax(distanceMax)
            .execute(callbacks);
        
    }

    void turnTo(
        const okapi::Point& _target,
        const okapi::QTime& timeout,
        const Direction& dir, 
        const PIDGAINS& gains
    ) {
        Turn( _target, timeout)
            .executeLogistic(dir, gains);
    }

    void turnTo(
        const okapi::QAngle& _angle, 
        const okapi::QTime& timeout,
        const Direction& dir,
        const PIDGAINS& gains
    ) {
        Turn( _angle, timeout)
            .executeLogistic(dir, gains);
    }

};