#include "..\include\autons\test.h"

void redRingRush() {
    chassis.setPose(-50.665, 28.868, 75); //initial position
    leftDoinker.toggle();                   //doinker extension
    chassis.moveToPoint(-9.071, 40.011, 3000, {.earlyExitRange = 1.5});     //move to the ringrush rings
    allianceColor = 2;                                      //enable colorsensor to stop intake
    colorSortOn = true;                                           //colorsensor
    chassis.turnToHeading(40, 700, {}, false);
    chassis.moveToPoint(chassis.getPose().x - (22 * sin(chassis.getPose(true).theta)), chassis.getPose().y - (22 * cos(chassis.getPose(true).theta)), 1200, {.forwards = false, .maxSpeed = 86});
    chassis.waitUntil(21);
    mogo.toggle();
    allianceColor = 0; 
    colorSortOn = true; 
    chassis.waitUntilDone(); 
    chassis.turnToHeading(15, 600, {.minSpeed = 35,  .earlyExitRange = 5});
    leftDoinker.toggle();
    chassis.turnToHeading(0, 400, {}, false);
    chassis.moveToPoint(chassis.getPose().x + (24 * sin(chassis.getPose(true).theta)), chassis.getPose().y + (24 * cos(chassis.getPose(true).theta)), 1500, {}, false);
    chassis.turnToHeading(-130, 800, {}, false);
    chassis.moveToPoint(chassis.getPose().x + (36 * sin(chassis.getPose(true).theta)), chassis.getPose().y + (36 * cos(chassis.getPose(true).theta)), 1900);
    chassis.waitUntil(30);
    desiredLiftValue = 9000;
    liftPIDRunning = true; 
    allianceColor = 3; 
    colorSortOn = true; 
    chassis.waitUntilDone();
    chassis.turnToHeading(-125, 700, {}, false);
    chassis.moveToPoint(chassis.getPose().x + (13 * sin(chassis.getPose(true).theta)), chassis.getPose().y + (13 * cos(chassis.getPose(true).theta)), 1000, {}, false);
    desiredLiftValue = 26500; 
    liftPIDRunning = true; 
    pros::delay(500);
    desiredLiftValue = 10500; 
    liftPIDRunning = true;
    
    chassis.setPose(-61.595997,12.992003,-125.355026);
    intakeMotor1.move(-127);
    chassis.waitUntil(10);
    intakeMotor1.brake(); 
    
    chassis.moveToPose(-8.848, 6.885, 321.53, 2500, {.forwards = false}, false);   

    




    
    /*
     chassis.moveToPoint(-23.2123274131, 23.1580222514, 1200, {.forwards = false, .maxSpeed = 86});
    chassis.waitUntil(21);
    mogo.toggle();
    allianceColor = 0; 
    colorSortOn = true; 
    chassis.waitUntilDone(); 
    chassis.turnToHeading(15, 600, {.minSpeed = 35,  .earlyExitRange = 5});
    leftDoinker.toggle();
    chassis.turnToHeading(0, 400, {}, false);

    */



}
    

