#ifndef INTAKE_H
#define INTAKE_H

#include "main.h"
#include "ports.h"

using okapi::Motor;

class Intake {
    private:
        Motor m1;

        const std::vector<double> powers = { 12000, 0 };

        int currPower = 0;

    public:
        Flywheel(int port1);
        void runVoltage(double power = 12000);
        void toggle();
};

extern Flywheel fly;

#endif