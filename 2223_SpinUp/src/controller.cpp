#include "controller.h"

namespace Controller {

    // initialize the controller and deadzone
    okapi::Controller masterController(okapi::ControllerId::master);
    constexpr double deadzone = 0.1;

    // initialize the map of buttons
    std::unordered_map<okapi::ControllerDigital, ToggleData> toggleMap = {
        { RESET_ODOM_BUTTON, { false, Odometry::resetHeading } },
        { POINT_TO_ALLIANCE_GOAL_BUTTON, { false, Auton::pointToAllianceGoal } },
        { POINT_TO_ENEMY_GOAL_BUTTON, { false, Auton::pointToEnemyGoal } },
        { TOGGLE_FLYWHEEL, { false, [](){ flywheel.toggle(); } } },
        { INTAKE_IN, { false, [](){ intake.toggle(FORWARD); } } },
        { INTAKE_OUT, { false, [](){ intake.toggle(REVERSE); } } }
    };

    std::unordered_map<okapi::ControllerDigital, HoldData> holdMap = {
        { RUN_INDEXER, { [](){ indexer.runWhenPressed(RUN_INDEXER, 12000); }, [](){ indexer.runWhenPressed(RUN_INDEXER, 0); } } }
    };

    void addToggleControl(okapi::ControllerDigital btn, std::function<void()> func) {
        toggleMap.insert({ btn, { false, func }});
    }

    bool toggleContains(okapi::ControllerDigital btn) {
        return toggleMap.count(btn) > 0;
    }

    void step() { 
        // goes through each button and iterates the count if the button is currently pressed (one time)
        //std::cout << "Starting controller step\n";
        for (auto& [ key, value ] : toggleMap) {
            bool currentState = masterController.getDigital(key); // current state of the button

            if (currentState && !value.previousState) // debouncing
                value.callback(); // runs the callback function

            value.previousState = currentState;
        }

        // handle the hold map
        for (auto& [ key, value ] : holdMap) {
            if (masterController.getDigital(key))
                value.on();
            else
                value.off();
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

    bool getDigital(const okapi::ControllerDigital button) {
        return masterController.getDigital(button);
    }
};