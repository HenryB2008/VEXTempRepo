#include "blueRingRushWP.h"

ASSET(realRingRushMogoRED_txt);
ASSET(blueRRWorlds_txt); 

void blueRingRushWP() {
    chassis.setPose(53.3, 9.1, -240);  
    chassis.lateralPID.kI = 0.075; 
    chassis.moveToPose(58.7, 5.7, -239, 650 , {.lead = 0.03}, false);
    chassis.lateralPID.kI = 0;
    desiredLiftValue = 110;
    iterations = 0; 
    liftPIDRunning = true; 
    pros::delay(700);

    

    chassis.moveToPose(26.8, 25.5, -236.5, 900, {.forwards = false, .lead = 0.35, .maxSpeed = 95}, false); 
    mogo.toggle(); 
    desiredLiftValue = 315 ; 
    iterations = 0; 
    liftPIDRunning = true; 
    chassis.turnToHeading(-51.5, 850, {}, false);
    allianceColor =  1; 
    colorSortOn = true; 
    chassis.follow(blueRRWorlds_txt,8, 2350, true, false);
    chassis.moveToPose(15.9, 31, -376.7, 800, {.forwards = false, .lead = 0.35}, false);
    chassis.turnToHeading(-330, 800, {.minSpeed = 50, .earlyExitRange = 5.5},false);
    chassis.moveToPose(26.348, 44.398, -319,900, {.lead = 0.3, .minSpeed = 55, .earlyExitRange = 3}, false);
    chassis.moveToPose(51.2, 45.7, -265, 1000, {.lead = 0.425, .minSpeed = 40, .earlyExitRange = 2.5}, false);
    chassis.moveToPose(65.7, 56.3, -314, 1600, {.lead = 0.5, .minSpeed = 35, .earlyExitRange = 2.5}, false);

    chassis.tank(70,70);
    pros::delay(1200);
    chassis.tank(-60,-60);
    pros::delay(400);
    chassis.tank(0,0);
    pros::delay(50);
    chassis.turnToHeading(-176, 800, {.minSpeed = 50, .earlyExitRange = 15}, false);
    chassis.moveToPose(50, 2, -176, 1300, {.lead = 0.4, .minSpeed = 95, .earlyExitRange = 31.5}, false);
    chassis.moveToPose(48, -23, -176, 1400, {.lead = 0.4, .maxSpeed = 45}, false);
    pros::delay(1200);

    // chassis.moveToPose(-25.3, 26.4, 380, 1250, {.forwards = false, .lead = 0.425}, false);
    // chassis.moveToPose(-38, 47, 318, 1100, {.lead = 0.35, .minSpeed = 45, .earlyExitRange = 2.5});
    // chassis.moveToPose(-70.2, 57.4  , 314, 1600, {.lead = 0.5, .minSpeed = 40, .earlyExitRange = 2.5}, false);
    // chassis.waitUntilDone(); 

    // chassis.tank(70, 70);
    // pros::delay(1250);
    // chassis.tank(-60, -60);
    // pros::delay(500);

    // /*
    // chassis.tank(70,70);
    // pros::delay(1000);
    // chassis.tank(-60,-60);
    // pros::delay(500);
    // chassis.tank(0,0);
    // */
    // chassis.turnToHeading(176, 800, {.minSpeed = 45, .earlyExitRange = 15});
    // chassis.moveToPose(-70, -12, 176, 1900, {.lead = 0.3});
    // chassis.waitUntil(38);
    // chassis.cancelMotion();
    // chassis.moveToPose(-70, -12, 176, 1000, {.lead = 0.15, .maxSpeed = 50});
    
    // pros::delay(2000);
    // //chassis.moveToPose(-29.6, 29, 375, 1250, {.forwards = false, .lead = 0.35}, false);


    // chassis.turnToHeading(333, 700, {.minSpeed = 32, .earlyExitRange = 3});
    // chassis.moveToPose(-40, 48.7, 313, 800, {.lead = 0.35, .maxSpeed = 70, .minSpeed = 32, .earlyExitRange = 3.5}); 
    // //chassis.moveToPose(-65.4, 50.2, 313, 1400, {.lead = 0.4,  .maxSpeed = 80, .minSpeed = 40}, false);



}   
