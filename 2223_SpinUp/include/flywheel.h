#ifndef FLYWHEEL_H
#define FLYWHEEL_H

#include "main.h"
#include "ports.h"

using okapi::Motor;

class Flywheel {
    private:
        Motor m1, m2;

        const std::vector<double> powers = { 8000, 12000, 0 };
        int currPower = 0;

    public:
        Flywheel(int port1, int port2);
        void runVoltage(double power = 12000);
        void toggle();
};

extern Flywheel fly;

#endif