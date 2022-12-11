#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "main.h"
#include "odometry.h"
#include "auton.h"
#include "drive.h"
#include "effector.h"

#define FORWARD_CONTROL okapi::ControllerAnalog::leftY
#define YAW_CONTROL okapi::ControllerAnalog::rightX

#define RESET_ODOM_BUTTON okapi::ControllerDigital::A
#define POINT_TO_ALLIANCE_GOAL_BUTTON okapi::ControllerDigital::B
#define POINT_TO_ENEMY_GOAL_BUTTON okapi::ControllerDigital::X

#define TOGGLE_FLYWHEEL okapi::ControllerDigital::R1

#define RUN_INDEXER okapi::ControllerDigital::R2

#define INTAKE_IN okapi::ControllerDigital::up
#define INTAKE_OUT okapi::ControllerDigital::down


// Struct which stores the previous state of a button and the amount of times it has been pressed
struct ToggleData {
    bool previousState;             // Previous state of the button (pressed = true, unpressed = false)
    std::function<void()> callback; // Callback that runs after the button is pressed
};

struct HoldData {
    std::function<void()> on;  // Callback that runs when the button is held
    std::function<void()> off; // Callback that runs when the button is released
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
    bool getDigital(const okapi::ControllerDigital button);
};

#endif
