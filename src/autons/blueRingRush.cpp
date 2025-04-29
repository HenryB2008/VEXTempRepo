#include "blueRingRush.h"

ASSET(realRingRushMogoBLUE_txt);

/**/
void blueRingRush() {
    /*
    allianceColor = 1; 
    colorSortOn = false;

    chassis.setPose(51.774, 28.354, -73);
    pros::delay(20); 
    intakeMotor1.move(-127); 

    chassis.moveToPose(9.9, 40.9, -72, 1500, {.lead = 0.03, .earlyExitRange = 1.5});
    
    chassis.waitUntil(15);
    rightDoinker.toggle(); 
    chassis.waitUntilDone(); 
    intakeMotor1.brake(); 
    chassis.follow(realRingRushMogoBLUE_txt, 5, 1400, false);

    chassis.waitUntilDone();
    mogo.toggle(); 
    rightDoinker.toggle();
    chassis.angularPID.kI = 0.04; 
    chassis.turnToHeading(-10, 700, {}, false);
    chassis.angularPID.kI = 0; 
    allianceColor = 1; 
    colorSortOn = true; 
    chassis.moveToPose(19, 51, -10, 1400, {.lead = 0.03}, false);
    chassis.turnToHeading(140, 800, {}, false);
    chassis.moveToPose(46, 21, 140, 1050, {.lead = 0.07});
    chassis.waitUntil(17);
    desiredLiftValue = 101.5; 
    iterations = 0; 
    liftPIDRunning = true;
    chassis.waitUntilDone();

    chassis.lateralPID.kI = 0.05;
    chassis.moveToPose(55, 13, 137, 700, {.lead = 0.04}, false);
    chassis.lateralPID.kI = 0; 
    chassis.turnToHeading(177, 800, {}, false);
    chassis.moveToPose(56, -3.25, 178, 950, {.lead = 0.02}, false);
    colorSortOn = false; 

    
    chassis.turnToHeading(88, 850, {}, false);
    
    chassis.tank(34, 34);

    pros::delay(750);
    intakeMotor1.brake(); 
    chassis.moveToPose(chassis.getPose().x - (6 * sin(chassis.getPose(true).theta)), chassis.getPose().y - 
    (6 * cos(chassis.getPose(true).theta)), chassis.getPose().theta, 700, {.forwards = false, .lead = 0.03}, false); 
    desiredLiftValue = 285; 
    iterations = 0; 
    liftPIDRunning = true; 
    pros::delay(600);
    chassis.moveToPose(chassis.getPose().x - (5 * sin(chassis.getPose(true).theta)), chassis.getPose().y - 
    (5 * cos(chassis.getPose(true).theta)), chassis.getPose().theta, 700, {.forwards = false, .lead = 0.03}, false); 
    chassis.turnToHeading(chassis.getPose().theta + 180, 1200, {}, false);
    desiredLiftValue = 64; 
    iterations = 0; 
    liftPIDRunning = true; 
    chassis.tank(46, 46);
    pros::delay(1000);
    chassis.tank(0,0);







    /*
    chassis.turnToHeading(-173, 700, {}, false);
    chassis.moveToPose(-50, 2, -175, 800, {.lead = 0.05}, false);
    colorSortOn = false; 
    chassis.turnToHeading(-84, 800, {}, false);
    chassis.moveToPose(-63, 2, -83, 800, {.lead = 0.03}, false);
    */
    /*
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
