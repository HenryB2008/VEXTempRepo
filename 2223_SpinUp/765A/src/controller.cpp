#include "controller.h"

namespace Controller {
    // initialize the controller and deadzone
    okapi::Controller masterController(okapi::ControllerId::master);
    double deadzone = 0.1;

    // initialize the map of buttons
    std::unordered_map<okapi::ControllerDigital, ButtonData> map = {
        { RESET_ODOM_BUTTON, { false, Odometry::resetOdometry } }
    };

    void step() {
        // goes through each button and iterates the count if the button is currently pressed (one time)
        //std::cout << "Starting controller step\n";
        for (auto& [ key, value ] : map) {
            bool currentState = masterController.getDigital(key); // current state of the button

            if (currentState && !value.previousState) // debouncing
                value.callback(); // runs the callback function

            value.previousState = currentState;
        }
    }

    double getForward() {
        double forward = masterController.getAnalog(FORWARD_CONTROL);

        // utilizing deadzone
        return fabs(forward) > deadzone ? forward : 0;
    }

    double getYaw() {
        double yaw = masterController.getAnalog(YAW_CONTROL);

        // utilizing deadzone
        return fabs(yaw) > deadzone ? yaw : 0;
    }

    bool getDigital(const okapi::ControllerDigital& button) {
        return masterController.getDigital(button);
    }
};