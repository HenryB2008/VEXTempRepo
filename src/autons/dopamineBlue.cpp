#include "autons\dopamineBlue.h"

void dopamineBlue() {
    colorSortOn = false; 
    chassis.setPose(53.615, -23.2, -270);
    chassis.moveToPose(31, -23, -270, 1100, {.forwards = false, .lead = 0.01, .maxSpeed = 75 }, false);

    mogo.toggle(); 
    intakeMotor1.move(-127);
    pros::delay(150);
    chassis.turnToHeading(-415, 800, {}, false);
    intakeMotor1.brake(); 
    //-13.5, 2.5
    chassis.moveToPose(13.2,1.2, -362, 1200, {.lead = 0.4, .maxSpeed = 85}, false); 
    
    chassis.waitUntil(12);
    chassis.cancelMotion();
    chassis.moveToPose(13.2, 1.2, -362, 200, {.lead = 0.4, .maxSpeed = 45}, false);

    chassis.moveToPose(13.54, -8.9, -364, 750, {.forwards = false, .lead = 0.1, }, false);
     
    chassis.angularPID.kI = 0.05;
    chassis.turnToHeading(-408.7, 500, {}, false);
    chassis.angularPID.kI = 0; 
    
    // /*
    // chassis.lateralPID.kI = 0.1;
    // chassis.moveToPose(-14.5, -7.3, 397, 600, {.forwards = false, .lead = 0.1}, false);
    // chassis.lateralPID.kI = 0; 
    // */
     leftDoinker.toggle(); 

     pros::delay(300);
    chassis.moveToPose(36.2, -21.1, -451.7, 1600, {.forwards = false, .lead = 0.4,}, false);
     leftDoinker.toggle(); 
     allianceColor = 1;
     colorSortOn = true; 
     chassis.angularPID.kI = 0.05;

     chassis.turnToHeading(-467.5, 700, {}, false);
     chassis.angularPID.kI = 0; 
     chassis.moveToPose(23.5, -25.6, -467, 800, {.lead = 0.05}, false);
    // //chassis.moveToPose(-34.1, -27.5, 469.8, 900, {.lead = 0.2}, false);
     chassis.turnToHeading(-542, 800, {}, false);
     chassis.moveToPose(26.8, -41, -542, 900, {.lead = 0.05}, false);
     chassis.turnToHeading(-615, 700, {}, false); 

    // /*
    // chassis.moveToPose(-50.7, -44.1, 632, 2000, {.lead = 0.275},false );
    // chassis.turnToHeading(589, 700, {}, false);
    // */
    //69 -58
    //64.6, -55.1
     chassis.moveToPose(64.6, -55.1, -590,2500, {.lead = 0.5, .maxSpeed = 80, .minSpeed = 70}, false);
     chassis.tank(80,80);
     pros::delay(1200);
     chassis.tank(-32, -32);
     pros::delay(300);
     intakeMotor1.move(64);
     pros::delay(100);
     intakeMotor1.move(-127);
     pros::delay(600);
     chassis.tank(0,0);
     pros::delay(2000);



    
   
}   
