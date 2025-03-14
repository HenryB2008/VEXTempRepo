#include "redRingRush.h"

ASSET(realRingRushMogoRED_txt);

void redRingRush() {
    allianceColor = 3; 
    colorSortOn = true; 

    chassis.setPose(-51.774, 28.354, 73);
    pros::delay(20); 
    chassis.moveToPose(-9.9, 40.9, 72, 1500, {.lead = 0.03, .earlyExitRange = 1.5});
    
    chassis.waitUntil(15);
    leftDoinker.toggle(); 
    chassis.waitUntilDone(); 
    chassis.follow(realRingRushMogoRED_txt, 5, 1400, false, false);
    mogo.toggle(); 
    leftDoinker.toggle();
    chassis.angularPID.kI = 0.04; 
    chassis.turnToHeading(10, 700, {}, false);
    chassis.angularPID.kI = 0; 
    allianceColor = 0; 
    colorSortOn = true; 
    chassis.moveToPose(-19, 51, 10, 1400, {.lead = 0.03}, false);
    chassis.turnToHeading(-140, 800, {}, false);
    chassis.moveToPose(-46, 21, -140, 1050, {.lead = 0.07});
    chassis.waitUntil(17);
    desiredLiftValue = 102.5; 
    iterations = 0; 
    liftPIDRunning = true;
    chassis.waitUntilDone();
    pros::delay(1500);
    chassis.turnToHeading(-173, 700, {}, false);
    chassis.moveToPose(-50, 2, -175, 800, {.lead = 0.05}, false);
    rightDoinker.toggle();
    colorSortOn = false; 
    chassis.turnToHeading(-84, 800, {}, false);
    rightDoinker.toggle(); 
    chassis.moveToPose(-63, 2, -83, 800, {.lead = 0.03}, false);
    chassis.moveToPose(chassis.getPose().x - (6 * sin(chassis.getPose(true).theta)), chassis.getPose().y - 
        (6 * cos(chassis.getPose(true).theta)), chassis.getPose().theta, 700, {.forwards = false, .lead = 0.03}, false); 
    desiredLiftValue = 285; 
    iterations = 0; 
    liftPIDRunning = true; 



    /*
    chassis.moveToPose(-24.4, 27.1, 2.9, 1600, {.forwards = false}, false);
    mogo.toggle(); 
    leftDoinker.toggle(); 
    allianceColor = 1; 
    colorSortOn = true; 
    */

    
    
}
