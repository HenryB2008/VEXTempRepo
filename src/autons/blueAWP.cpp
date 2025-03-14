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
    iterations = 0; 
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
    chassis.follow(secondStackBLUEAWP_txt, 9, 2800, true, false);
    chassis.turnToPoint(53, -10.733, 800, {}, false); 
    
    mogo.toggle(); 
    chassis.moveToPoint(54, -12.6, 550, {.maxSpeed = 95, .minSpeed = 70, .earlyExitRange = 6});
    chassis.moveToPose(58, -19.4, 150, 1300, {.maxSpeed = 53}); 
    chassis.waitUntilDone(); 
    allianceColor = 4; 


    chassis.turnToPoint(21.8, -23.4, 900, {.forwards = false}, false);
    chassis.moveToPoint(21.8, -23.4, 1025, {.forwards = false, .maxSpeed = 88});

    chassis.waitUntilDone();
    mogo.toggle();  

    allianceColor = 1; 
    colorSortOn = true; 
    chassis.turnToPoint(21.7, -45.4, 800, {}, false);
    chassis.moveToPoint(21.7, -45.4, 800, {}, false);
    chassis.follow(touchLadderBLUEAWP_txt, 13, 1200, false, false);
    
   // chassis.moveToPoint(-23, -44, 800, {}, false);

    //chassis.moveToPose(-13, -5, -154, 8000, {.forwards = false, .lead = 0.5, .minSpeed = 50}, false);

    //chassis.moveToPose(-8.1918, 38.019, 362.3, 6000, {.lead = 0.4, .maxSpeed = 60});
}