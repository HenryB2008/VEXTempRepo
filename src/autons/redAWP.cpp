#include "..\autons\redAWP.h"

ASSET(ringRushREDAWP_txt);
ASSET(secondStackREDAWP_txt);
ASSET(touchLadderREDAWP_txt);

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
void    redAWP(){
  /*
      allianceColor = 0;
    colorSortOn = false;  
    chassis.setPose(-53,8.5,240);
    chassis.lateralPID.kI = 0.05;
    chassis.moveToPoint(-57.7631397208, 5.75, 600, {}, false);
    chassis.lateralPID.kI = 0; 
    desiredLiftValue = 285; 
    iterations = 0; 
    liftPIDRunning = true; 
    pros::delay(1050);
    chassis.moveToPoint(-31.2, 21.2, 900, {.forwards = false, .maxSpeed = 80});
    chassis.waitUntil(8); 
    desiredLiftValue = 140;
    iterations = 0; 
    liftPIDRunning = true; 
    chassis.waitUntilDone(); 
    pros::delay(100);
    mogo.toggle();  
    colorSortOn = true; 
    chassis.turnToHeading(68, 1050, {}, false);
    chassis.follow(ringRushREDAWP_txt, 10, 3000, true, false);
    chassis.follow(secondStackREDAWP_txt, 9, 2800, true, false);
  
    chassis.turnToPoint(-53, -10.733, 800, {}, false); 
    mogo.toggle(); 
    chassis.moveToPoint(-53, -10.733, 550, {.maxSpeed = 95, .minSpeed = 70, .earlyExitRange = 6});
    chassis.moveToPose(-53.6, -11.9, -150, 1100, {.maxSpeed = 65}); 
    chassis.waitUntilDone(); 
    
    
    allianceColor = 3;     
  
    chassis.turnToPoint(-26.6, -27.3, 900, {.forwards = false}, false);
  
    chassis.moveToPoint(-24.6, -25.14, 1025, {.forwards = false, .maxSpeed = 88}, false);
    mogo.toggle();  
    allianceColor = 0; 
    colorSortOn = true; 
    chassis.turnToPoint(-25.1, -45.4, 800, {}, false);
    chassis.moveToPoint(-25.1, -45.4, 800, {}, false);
    chassis.follow(touchLadderREDAWP_txt, 13, 1200, false, false);
    liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    
    
    //chassis.turnToPoint(-23, -20, 900, {.forwards = false}, false);
    //chassis.moveToPoint(-23, -20, 900, {.forwards = false, .maxSpeed = 88}, false);
   /* 
    mogo.toggle(); 
    allianceColor = 0; 
    colorSortOn = true; 
    //-24, -21, -183
    chassis.turnToHeading(-183, 950, {}, false);
    colorSortOn = false; 
    intakeMotor1.move(-127);
    chassis.moveToPoint(chassis.getPose().x + (25 * sin(chassis.getPose(true).theta)), chassis.getPose().y + (25 * cos(chassis.getPose(true).theta)), 800., {}, false); 
    chassis.setPose(-24.774,-57.657,180);
    pros::delay(20);
    chassis.follow(touchLadderREDAWP_txt, 13, 1200, false, false);
    */
    
   // chassis.moveToPoint(-23, -44, 800, {}, false);

    //chassis.moveToPose(-13, -5, -154, 8000, {.forwards = false, .lead = 0.5, .minSpeed = 50}, false);

    //chassis.moveToPose(-8.1918, 38.019, 362.3, 6000, {.lead = 0.4, .maxSpeed = 60});

} 