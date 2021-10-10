#ifndef PNEUMATICS_H
#define PNEUMATICS_H

#include "main.h"
#include "ports.h"

class Pneumatics {
    private:
        pros::ADIDigitalOut piston;
        okapi::ControllerDigital btn;

        bool state = false;

    public:
        Pneumatics(uint8_t port);

        // helper methods
        void turnOn();
        void turnOff();

        // opcontrol
        void handle();

        // auton
        void onThenOff(int delay);
        void offThenOn(uint32_t delay);
};

#endif
