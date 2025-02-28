#include "..\include\autons\blueRingSafe.h"

void blueRingSafe(){
    
    colorSortOn = false; 

    chassis.setPose(-51,-14,-52); 
    chassis.moveToPoint(-56.5160752752, -9.69036967272, 800, {}, false);
    desiredLiftValue = 29800; 
    liftPIDRunning = true;
    pros::delay(750);
    desiredLiftValue = 6400; 
    liftPIDRunning = true; 
    chassis.moveToPoint(-26.571666638, -33.0855057351, 1200, {.forwards = false, .maxSpeed = 86}); 
    chassis.waitUntil(36);
    mogo.toggle(); 
    chassis.turnToHeading(-218.7, 900);
    allianceColor = 1; 
    colorSortOn =  true; 
    chassis.moveToPoint(-12.8163281986, -50.2549746965, 1200, {}, false); // 20
    chassis.moveToPoint(-23.4454533563, -34.2802001431, 900, {.forwards = false}); //
    chassis.turnToHeading(-165, 900, {}, false);

    chassis.moveToPoint(-27.845377123 ,-50.70093919, 1100, {}, false);  //17
    chassis.turnToHeading(30, 900, {}, false);
    desiredLiftValue = 23500;
    liftPIDRunning = true; 
    chassis.moveToPoint(chassis.getPose().x + (21 * sin(chassis.getPose(true).theta)), chassis.getPose().y + (21 * cos(chassis.getPose(true).theta)), 1300, {}, false); 

}