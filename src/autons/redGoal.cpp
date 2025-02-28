#include "..\include\autons\redGoal.h"

void redGoal() {
    colorSortOn = false; 

    chassis.setPose(-51,-14,-52); 
    chassis.moveToPoint(-56.5160752752, -9.69036967272, 800, {}, false);
    desiredLiftValue = 29800; 
    liftPIDRunning = true;
    pros::delay(500);
    desiredLiftValue = 6400; 
    liftPIDRunning = true; 
    chassis.moveToPoint(-26.571666638, -33.0855057351, 1300, {.forwards = false, .maxSpeed = 86}); 
    chassis.waitUntil(36);
    mogo.toggle(); 

    chassis.turnToHeading(56, 1100, {}, false);

    
    chassis.moveToPose(-9.7, -21.9016476657, 51, 1000,  {}, false);      //travvelled 20 inches, 

    
    rightDoinker.toggle(); 
    pros::delay(400);
    chassis.turnToHeading(70, 700, {}, false);
    lateral_controller.kP = 8; 
    lateral_controller.kD = 1; 
    pros::delay(400);
    lateral_controller.kP = 10.75;
    lateral_controller.kD = 29; 

    chassis.moveToPoint(-43.3500032248, -34.0433627537,1200, {.forwards = false, .maxSpeed = 80}, false);
    allianceColor = 0; 
    colorSortOn = true; 

    rightDoinker.toggle();
    
    chassis.setPose(-43.35,-34.043  ,312);
    
    chassis.moveToPoint(-54.357102, -24.042818, 700, {}, false);

    chassis.turnToHeading(422, 800, {.maxSpeed = 75}, false);
    chassis.moveToPoint(-29.7, -14, 1200, {.maxSpeed = 80}, false);

    chassis.turnToHeading(630, 1100, {}, false);
    desiredLiftValue = 22500;
    liftPIDRunning = true; 
    chassis.moveToPoint(chassis.getPose().x + (23 * sin(chassis.getPose(true).theta)), chassis.getPose().y + (23 * cos(chassis.getPose(true).theta)), 1200., {}, false);
    

    /*
    chassis.turnToHeading(65, 800, {}, false);
    rightDoinker.toggle();
    pros::delay(500);
    chassis.turnToHeading(79, 800, {}, false);
    lateral_controller.kP = 8; 
    lateral_controller.kD = 1; 
    chassis.moveToPoint(chassis.getPose().x + (4 * sin(chassis.getPose(true).theta)), chassis.getPose().y + (4* cos(chassis.getPose(true).theta)), 800., {}, false);
    lateral_controller.kP = 10.75;
    lateral_controller.kD = 29; 
    leftDoinker.toggle();
    pros::delay(500);
    chassis.setPose(-7, -21, 78);
    chassis.moveToPoint(-46.1259040294,-29.3164676327, 1100, {.forwards = false   }, false); //
    allianceColor = 4; 
    stopTransition = false; 
    colorSortOn = true; 
    rightDoinker.toggle();
    leftDoinker.toggle(); 
    */  
 

    /*
    rightDoinker.toggle(); 
    pros::delay(300);
    chassis.turnToHeading(77, 800, {}, false);
    lateral_controller.kP = 7; 
    lateral_controller.kD = 1; 
    chassis.moveToPoint(chassis.getPose().x + (4 * sin(chassis.getPose(true).theta)), chassis.getPose().y + (4* cos(chassis.getPose(true).theta)), 800);
    lateral_controller.kP = 10.75;
    lateral_controller.kD = 29; 
    leftDoinker.toggle(); 
    chassis.waitUntilDone(); 
    chassis.setPose(-8.68551974086,  -20.8581957826, 77);
    pros::delay(20);
    chassis.turnToHeading(64, 800, {}, false);
    chassis.moveToPoint(-42.0165856668, -36.864, 1100, {.forwards = false}, false);
    */
}
