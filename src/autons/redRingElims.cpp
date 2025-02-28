#include "..\include\autons\redRingElims.h"

void redRingElims() {
    colorSortOn = true; 
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

    chassis.turnToHeading(21, 800, {.minSpeed = 35});
    leftDoinker.toggle();
    chassis.turnToHeading(7, 500, {}, false);
    chassis.moveToPoint(-19, 53, 1500, {.maxSpeed = 65}, false );
    
    chassis.turnToHeading(-140, 950, {}, false);

    chassis.moveToPoint(-46.424293, 22.258978,1100, {});
    chassis.waitUntil(30);
    allianceColor = 3; 
    colorSortOn = true; 
    desiredLiftValue = 8800; 
    liftPIDRunning = true;
    chassis.waitUntilDone();
    chassis.turnToHeading(-129, 800, {}, false);
    chassis.moveToPose(-60.1509333353,14.7561814145, -129, 1100, {}, false);
    desiredLiftValue = 26500; 
    liftPIDRunning = true; 
    pros::delay(500);
    desiredLiftValue = 10500; 
    liftPIDRunning = true;
    allianceColor = 0; 
    colorSortOn = true;         
    chassis.moveToPoint(-52, 19, 800, {.forwards = false}, false);
    desiredLiftValue = 6400; 
    liftPIDRunning = true; 
    chassis.turnToHeading(-174, 800, {}, false);
    chassis.moveToPoint(-52, 9, 800, {}, false);
    chassis.moveToPoint(-53, -13, 800, {.maxSpeed= 75}, false);
    desiredLiftValue = 14000;
    liftPIDRunning = true; 
pros::delay(500);

    /*
    chassis.moveToPoint(chassis.getPose().x + (36 * sin(chassis.getPose(true).theta)), chassis.getPose().y + (36 * cos(chassis.getPose(true).theta)), 1900);
    allianceColor = 3; 
    colorSortOn = true; 
    chassis.waitUntilDone();
    chassis.moveToPoint(chassis.getPose().x + (13 * sin(chassis.getPose(true).theta)), chassis.getPose().y + (13 * cos(chassis.getPose(true).theta)), 1000, {}, false);


*/



/*
    

    */
    /*

    chassis.moveToPoint(-54, -13, 800, {.maxSpeed = 64}, false);
    pros::delay(2000);
    
    */

    




    
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
    

