#include "goalRushRed.h"

void goalRushRed() {
    /*
    allianceColor = 0; 
    colorSortOn = false;
    chassis.setPose(-50.138, -31.475, 105);
    chassis.moveToPoint(-12.068, -42.517, 1175, {.earlyExitRange = 2.5}); //angle 105  (-14, -42)
    chassis.waitUntil(5);
    leftDoinker.extend(); 
    chassis.waitUntil(10);
    intakeMotor1.move(-127);
    chassis.waitUntil(25);
    intakeMotor1.brake(); 
    chassis.waitUntil(36.6); 
    gRushClamp.toggle(); 
    chassis.waitUntilDone(); 
    chassis.moveToPoint(-29, -38, 700, {.forwards = false}, false); //angle 104 
    leftDoinker.toggle();
    gRushClamp.toggle(); 
    pros::delay(185); 
    chassis.turnToHeading(192, 800, {}, false); //angle: 192
    chassis.moveToPoint(-25, -21, 825, {.forwards = false}, false);
    mogo.toggle(); 
    colorSortOn = true; 
    pros::delay(1000);
    mogo.toggle(); 
    chassis.lateralPID.kI = 0.025; 
    chassis.moveToPoint(-26, -28, 600, {}, false);
    chassis.lateralPID.kI = 0; 
    chassis.turnToHeading(320, 800, {}, false);
    chassis.moveToPoint(-13, -47, 1250, {.forwards = false}, false);
    mogo.toggle();
    chassis.turnToPoint(-57, -57, 900, {}, false);
    chassis.moveToPoint(-57, -57, 1800, {}, false);
    chassis.tank(88, 88);
    pros::delay(800);
    chassis.moveToPoint(chassis.getPose().x - (6 * sin(chassis.getPose(true).theta)), chassis.getPose().y - (6 * cos(chassis.getPose(true).theta)), 800., {.forwards = false}, false);  
    chassis.setPose(0,0,0);
    chassis.turnToHeading(-25, 800, {}, false);



    //-15, -47,
    /*
    chassis.moveToPose(-57, -55, 217, 3000, {.lead = 0.68, .maxSpeed = 80}, false);
    
    chassis.tank(0,0);

    pros::delay(500); 
    

    chassis.moveToPoint(chassis.getPose().x - (12 * sin(chassis.getPose(true).theta)), chassis.getPose().y - (12 * cos(chassis.getPose(true).theta)), 800., {.forwards = false}, false);    
    chassis.setPose(0,0,0);
    chassis.turnToHeading(-60, 950, {}, false);
    */
    /* 
    chassis.setPose(chassis.getPose().x, chassis.getPose().y, 0);
    chassis.moveToPose(-32, -92, 179, 3000, {.minSpeed = 38, .earlyExitRange = 5}, false);
    chassis.tank(24, 24);
    pros::delay(750);
    chassis.tank(0,0);
    */

    /*
    pros::delay(700);
    chassis.turnToHeading(90, 1000, {}, false);
    chassis.moveToPose(-24, -38, -6, 2600, {.lead = 0.45}, false);
    
    leftDoinker.toggle(); 
    pros::delay(300);
    chassis.turnToHeading(120, 1000, {}, false);
    */

}

