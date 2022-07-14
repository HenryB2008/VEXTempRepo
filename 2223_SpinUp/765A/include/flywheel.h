#ifndef FLYWHEEL_H
#define FLYWHEEL_H

#include "main.h"

using okapi::Motor;

class Flywheel {
    private:
        Motor m1, m2, m3;

    public:
        Flywheel(int port1, int port2, int port3);

        void runVoltage(double power);
};

#endif