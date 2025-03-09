#include "..\autons\blueAWP.h"

ASSET(ringRushBLUEAWP_txt);
ASSET(secondStackBLUEAWP_txt);
ASSET(touchLadderBLUEAWP_txt);

/*
// latetral PID controller
lemlib::ControllerSettings lateral_controller(7.25, // proportional gain (kP)6.2
                                              0, // integral gain (kI)
                                                13, // derivative gain (kD) 1.9
                                              5, // anti windup
                                              0, // small error range, in inches
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in inches
                                              0, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (s5lew)
);

// angular PID controller 5.3, 47 
lemlib::ControllerSettings angular_controller(5.3,  // proportional gain (kP) 12.5
                                            0,// integral gain (kI)
                                            47,               // derivative gain (kD) 30
                                             15, // anti windup
                                              0, // small error range, in degrees
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in degrees
                                              0, // large error range timeout, in milliseconds
                                                0 // maximum acceleration (slew)
);
*/
void blueAWP(){

    allianceColor = 1;
    colorSortOn = false;  
    chassis.setPose(53,8.5,120);
    chassis.lateralPID.kI = 0.05;
    chassis.moveToPoint(57.7631397208, 5.75, 600, {}, false);
    chassis.lateralPID.kI = 0; 
    desiredLiftValue = 285; 
    iterations = 1; 
    liftPIDRunning = true; 
    pros::delay(900);
    chassis.moveToPoint(31.2, 21.2, 900, {.forwards = false, .maxSpeed = 80});
    chassis.waitUntil(8); 
    desiredLiftValue = 126;
    iterations = 0; 
    liftPIDRunning = true; 
    chassis.waitUntilDone(); 
    pros::delay(100);
    mogo.toggle();  
    colorSortOn = true; 
    chassis.turnToHeading(292, 900, {}, false);
    chassis.follow(ringRushBLUEAWP_txt, 10, 3000, true, false);
    chassis.follow(secondStackBLUEAWP_txt, 9, 2800, true);
    chassis.turnToPoint(45, 6, 800, {}, false); 

    mogo.toggle(); 
    chassis.moveToPoint(45, 6, 1250, {.maxSpeed = 85}, false);
    allianceColor = 4;     
    
    chassis.moveToPoint(55, -9, 800, {.maxSpeed = 60}, false);
    chassis.turnToPoint(23, -20, 900, {.forwards = false}, false);
    chassis.moveToPoint(23, -20, 900, {.forwards = false, .maxSpeed = 88}, false);
    mogo.toggle(); 
    allianceColor = 1; 
    colorSortOn = true; 
    //-24, -21, -183
    chassis.turnToHeading(183, 950, {}, false);
    colorSortOn = false; 
    intakeMotor1.move(-127);
    chassis.moveToPoint(chassis.getPose().x + (25 * sin(chassis.getPose(true).theta)), chassis.getPose().y + (25 * cos(chassis.getPose(true).theta)), 800., {}, false); 
    chassis.setPose(24.774,-57.657,180);
    pros::delay(20);
    chassis.follow(touchLadderBLUEAWP_txt, 1200, false, false);
   // chassis.moveToPoint(-23, -44, 800, {}, false);

    //chassis.moveToPose(-13, -5, -154, 8000, {.forwards = false, .lead = 0.5, .minSpeed = 50}, false);

    //chassis.moveToPose(-8.1918, 38.019, 362.3, 6000, {.lead = 0.4, .maxSpeed = 60});
}