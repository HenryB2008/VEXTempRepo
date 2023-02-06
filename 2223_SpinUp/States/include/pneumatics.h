#ifndef PNEUMATICS_H
#define PNEUMATICS_H

#include "main.h"

// Enum representeing if a pneumatic is turned on or not
enum PneumaticState {

    DEACTIVATED,
    ACTIVATED

};

// Class for pneumatic actuation
class Pneumatics {

    private:

        // ADiDigitalOut has 2 modes - on or off
        pros::ADIDigitalOut piston;

        // Stores the current state of the piston, with false being off
        bool state = false;

    public:

        // Constructor takes in an unsigned int
        Pneumatics(uint8_t port);

        // Activates pneumatic
        void on();

        // Deactivates pneumatoc
        void off();

        //
        bool getPreviousState

};

#endif