#ifndef AUTON_H
#define AUTON_H

#include "main.h"
#include "path_builder.h"

#define ALLIANCE_GOAL { 10.5_ft, 1.5_ft }
#define ENEMY_GOAL { 1.5_ft, 10.5_ft }

namespace Auton {
    void pointToAllianceGoal();
    void pointToEnemyGoal();


    // Rotates both alliance rollers
    // Shoots all 3 preload disks, picks up the 3 row, and shoots all 6
    void AUTON_LEFT_crossMap();
}

#endif