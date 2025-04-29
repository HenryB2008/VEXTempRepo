#include "autons\dopamineRed.h"


void dopamineRed() {
    colorSortOn = false; 
    chassis.setPose(-53.615, -23.2, 270);
    chassis.moveToPose(-31, -23, 270, 1100, {.forwards = false, .lead = 0.01, .maxSpeed = 75 }, false);
    mogo.toggle(); 
    intakeMotor1.move(-127);
    pros::delay(150);
    chassis.turnToHeading(415, 800, {}, false);
    intakeMotor1.brake(); 
    //-13.5, 2.5
    chassis.moveToPose(-13.5,2.25, 362, 1200, {.lead = 0.4, .maxSpeed = 85}, false); 
    chassis.waitUntil(12);
    chassis.cancelMotion();
    chassis.moveToPose(-13.5, 2.25, 362, 200, {.lead = 0.4, .maxSpeed = 45}, false);

    chassis.moveToPose(-14.2, -7.7, 364, 750, {.forwards = false, .lead = 0.1, }, false);
    chassis.angularPID.kI = 0.05;
    chassis.turnToHeading(397, 500, {}, false);
    chassis.angularPID.kI = 0; 
    /*
    chassis.lateralPID.kI = 0.1;
    chassis.moveToPose(-14.5, -7.3, 397, 600, {.forwards = false, .lead = 0.1}, false);
    chassis.lateralPID.kI = 0; 
    */
    rightDoinker.toggle(); 

    pros::delay(300);
    chassis.moveToPose(-45.5, -21.1, 454, 1600, {.forwards = false, .lead = 0.4,}, false);
    rightDoinker.toggle(); 
    allianceColor = 1; 
    colorSortOn = true; 
    chassis.angularPID.kI = 0.05;
    chassis.turnToHeading(473, 700, {}, false);
    chassis.angularPID.kI = 0; 
    chassis.moveToPose(-29.9, -27.3, 473, 800, {.lead = 0.05}, false);
    //chassis.moveToPose(-34.1, -27.5, 469.8, 900, {.lead = 0.2}, false);
    chassis.turnToHeading(540, 800, {}, false);
    chassis.moveToPose(-30.05, -41.4, 542, 900, {.lead = 0.05}, false);
    chassis.turnToHeading(615, 700, {}, false); 

    /*
    chassis.moveToPose(-50.7, -44.1, 632, 2000, {.lead = 0.275},false );
    chassis.turnToHeading(589, 700, {}, false);
    */
    chassis.moveToPose(-64., -58.3, 589,2500, {.lead = 0.5, .maxSpeed = 70, .minSpeed = 60}, false);
    chassis.tank(70,70);
    pros::delay(1000);
    chassis.tank(-32, -32);
    pros::delay(1000);
    chassis.tank(0,0);
    pros::delay(2000);


    
   
}   
