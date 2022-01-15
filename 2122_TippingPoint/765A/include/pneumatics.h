#ifndef PNEUMATICS_H
#define PNEUMATICS_H

#include "main.h"
#include "ports.h"

//class for pneumatics actuation
class Pneumatics {
    private:
        pros::ADIDigitalOut piston;
        bool state = false;
        int prevCount = 0;

    public:
        Pneumatics(uint8_t port);

        // helper methods
        void turnOn();
        void turnOff();

        // opcontrol
        void handle(int count);

        // auton
        void onThenOff(int delay);
        void offThenOn(uint32_t delay);
};

#endif
