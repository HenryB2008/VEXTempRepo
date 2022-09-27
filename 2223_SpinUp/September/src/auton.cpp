#include "auton.h"

// TODO: fix overshooting

namespace Auton {

    // TOOD: fix point
    void pointToAllianceGoal() {
        Turn(ALLIANCE_GOAL, 1.5_s)
            .withTurnGains({0.02, 0.0, 0.002})
            .withTurnMax(0.5)
            .execute(FORWARD);
    }

    // TODO: fix point
    void pointToEnemyGoal() {
        Turn(ENEMY_GOAL, 1.5_s)
            .withTurnGains({0.02, 0.0, 0.002})
            .withTurnMax(0.5)
            .execute(FORWARD);
    }

    void leftRoute() {

    }

    void rightRoute() {

    }
}