#ifndef AUTON_H
#define AUTON_H

#include "main.h"
#include "path_builder.h"
#include "effector.h"

/*

        Our coordinate grid exists in a 12_ft by 12_ft field, with 0_ft, 0_ft serving 
    as the bottom-left corner orthogonal to both the goals. The alliance goal is
    at 10.5_ft in the x direction and 1.5_ft in the y direction: (x and y are
    swapped in our code to handle an airplane heading instead of a unit circle). The 
    enemy goal is at 1.5_ft in the y direction and 10.5_ft in the x direction.

*/

#define ALLIANCE_GOAL { 10.5_ft, 1.5_ft }
#define ENEMY_GOAL { 1.5_ft, 10.5_ft }  

/*

        This namespace effectively contains all required functions for running an
    auton program. Utility functions, such as pointToAllianceGoal and
    pointToEnemyGoal, provide reusability and consistency to increase programming
    effeciency. These functions can also be used during an opcontrol period to
    minimize the tasks a driver has to manage.

*/

namespace Auton {


    /*
    
        ========== UTILITY FUNCTIONS ==========
    
    */

    // Turns to the alliance goal, chained to macro specified by the driver

    void pointToAllianceGoal();

    // Turns to the enemy goal, chained to macro specified by the driver
    // Not nearly as useful as the pointToAllianceGoal function

    void pointToEnemyGoal();

    /*
    
        ========== AUTON ROUTES ==========
    
    */

    //   This particular autonomous route rotates both rollers and should shoot 
    // the 3 preload discs and 3 discs found in a row near the center. 

    void AUTON_LEFT_rollerAndShoot();
    
    /*

        Skills Routes
    
    */

    void SKILLS();
}

#endif