#ifndef FLYWHEEL_H
#define FLYWHEEL_H

#include "main.h"
#include "ports.h"

using okapi::Motor;

class Flywheel {
    private:
        Motor m1, m2;
        
        double previousPower;

    public:
        Flywheel(int port1, int port2);
        void runVoltage(double power = 12000);
        void toggle(double power = 12000);
};

extern Flywheel fly;

#endif