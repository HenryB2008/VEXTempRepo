#ifndef PATH_BUILDER_H
#define PATH_BUILDER_H

#include "chassis.h"
#include "logistic.h"
#include "main.h"
#include "movement.h"
#include "pid.h"

#include <functional>
#include <queue>
#include <vector>

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