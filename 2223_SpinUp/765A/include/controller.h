#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "main.h"
#include "drive.h"

#define FORWARD_CONTROL okapi::ControllerAnalog::leftY
#define YAW_CONTROL okapi::ControllerAnalog::rightX

#define RESET_ODOM_BUTTON okapi::ControllerDigital::A

// Struct which stores the previous state of a button and the amount of times it has been pressed
struct ButtonData {
    bool previousState; // Previous state of the button (pressed = true, unpressed = false)
    void (*callback)(); // Callback that runs after the button is pressed
};

// Wrapper namespace for okapi::Controller
namespace Controller {
    // Called every opcontrol loop
    void step();

    // @returns forward power from the controller (used for arcade style)
    double getForward();

    // @returns turn power from the controller (used for arcade style)
    double getYaw();

    /*
       @param button digital button on the controller
       @returns the state of the button (pressed -> true, unpressed -> false)
    */
    bool getDigital(const okapi::ControllerDigital& button);
};

#endif
