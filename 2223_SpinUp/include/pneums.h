#ifndef PNEUMATICS_H
#define PNEUMATICS_H

#include "main.h"
#include "ports.h"

//class for pneumatics actuation
class Pneumatics {
    private:
        pros::ADIDigitalOut piston;
        bool state = false;

    public:

        Pneumatics(uint8_t port);

        void on();

        void off();

        void toggle();

};

extern Pneumatics angleChanger;

#endif