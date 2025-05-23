#include "skills.h"

ASSET(alignWithLastRingFirstMogoSKILLS_txt); 
ASSET(alignWithLastRingSecondMogoSKILLS_txt);

void skills(){
    /*
    intakeMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    colorSortOn = false; 
    pros::delay(10);
    desiredLiftValue = 285; 
    iterations = 0; 
    liftPIDRunning = true; 
    pros::delay(500);
    chassis.setPose(-61.592,-7.135,311);
    pros::delay(400);
    //first mogo 
    chassis.moveToPoint(-50.462, -16.81, 650, {.forwards = false, .maxSpeed = 60});
    chassis.waitUntil(13.7);    
    mogo.toggle(); 
    chassis.waitUntilDone(); 
    intakeMotor1.move(-127);
    desiredLiftValue = 64;
    iterations = 0; 
    liftPIDRunning = true; 
    pros::delay(200);
    //first ring 
    chassis.turnToPoint(-24.263, -17, 850, {}, false);
    chassis.moveToPose(-24.263, -17,  chassis.getPose().theta, 850, {.lead = 0.1}, false);
    chassis.moveToPose(24.98, -35, 454.4, 2000, { .lead = 0.5}, false);


    //chassis.turnToHeading(460, 600,  {}, false);

    chassis.moveToPose(1.26, -32, 466, 1300, {.forwards = false, .lead = 0.3}, false);
    pros::delay(10); 
    desiredLiftValue = 102.25; 
    liftkI = 0.0000055;  
    iterations = 0; 
    liftPIDRunning = true;
 
    chassis.turnToHeading(532.2, 850, {}, false);
    desiredLiftValue = 102.25; 
    iterations = 0; 
    liftPIDRunning = true;


    //score on wallstake

    chassis.moveToPose(3, -47.35, 531.9, 850, {.lead = 0.2,.maxSpeed = 60,  .minSpeed = 20, }, false); 
    chassis.tank(20, 20);
    pros::delay(1100);
    intakeMotor1.brake(); 
    chassis.tank(0,0);
    pros::delay(300);
    desiredLiftValue = 263;
    iterations = 0; 
    liftPIDRunning = true; 
    chassis.tank(0,0);
    pros::delay(600);
    chassis.setPose(3.592, -51.67, chassis.getPose().theta);

    pros::delay(350);
    intakeMotor1.move(-127);
    chassis.moveToPoint(0.75, -38, 800, {.forwards = false});
    desiredLiftValue = 64; 
    liftkI = 0; 
    iterations = 0; 
    liftPIDRunning = true;  
    chassis.waitUntilDone();
    chassis.turnToPoint(-56, -45, 945, {}, false);     //angle 623
    //3 ring straight 
    chassis.moveToPoint(-56, -45, 2050, {.maxSpeed = 58 }, false);
    chassis.follow(alignWithLastRingFirstMogoSKILLS_txt, 5, 1250, false, false);
    
    chassis.angularPID.kI = 0.025;
    //chassis.turnToPoint(-48, -52.7, 750, {}, false);
    chassis.turnToHeading(525.4, 750, {}, false);
    chassis.angularPID.kI = 0; 
    //last ring 
    chassis.moveToPose(-42.3, -52.96, 525.4, 1100, {.lead = 0.03}, false);
    
    chassis.turnToPoint(-53.2, -58.4, 850, {.forwards = false}, false);  
    chassis.lateralPID.kI = 0.05;
    //put mogo back 
    chassis.moveToPoint(-53.2, -58.4, 1000, {.forwards = false});
    chassis.waitUntil(8);
    mogo.toggle(); 
    chassis.waitUntilDone(); 
    chassis.moveToPoint(-48, -52.7, 800, {}, false);
    chassis.lateralPID.kI = 0; 
    chassis.turnToPoint(-58, 20, 1100, {.forwards = false}, false);    //angle 531
    //clamp second mogo 
    
    chassis.moveToPoint(-54, 11, 800, {.forwards = false, .minSpeed = 80, .earlyExitRange = 7}); 
    chassis.moveToPose(-55.1, 24, 174, 1800, {.forwards = false, .lead = 0.5, .maxSpeed = 80, .earlyExitRange =  0.75});
    
   //chassis.moveToPose(-55.5, 24.8, 530, 2400, {.forwards = false, .lead = 0.4, .maxSpeed = 85, .earlyExitRange = 2.5});

   chassis.waitUntilDone();  

    mogo.toggle();  
    //first ring second mogo 
    chassis.turnToPoint(-36, 27, 800, {}, false); //angle 429 
    chassis.moveToPoint(-36, 27, 850, {}, false);
   // chassis.lateralPID.kI = 0.075;
   //chassis.moveToPoint(chassis.getPose().x - (4 * sin(chassis.getPose(true).theta)), chassis.getPose().y - (4 * cos(chassis.getPose(true).theta)), 625, {.forwards = false}, false); 
    //chassis.lateralPID.kI = 0; 
    //chassis.angularPID.kI = 0.015;

    //second ring second mogo 
    chassis.turnToHeading(407, 700, {}, false); //angle 413
    //chassis.angularPID.kI = 0;
    
    chassis.moveToPose(12.8, 57, 414.8, 2100, {.lead = 0.75}, false);

    chassis.angularPID.kI = 0.025; 
    chassis.turnToHeading(423, 600, {}, false);
    
    chassis.angularPID.kI = 0; 
    pros::delay(10); 
    chassis.moveToPoint(-12, 52, 1000, {.forwards = false}, false);
    desiredLiftValue = 102.5; 
    iterations = 0; 
    liftPIDRunning = true;
    
    //chassis.turnToPoint(-12.95, 65.007, 925, {}, false);
    chassis.turnToHeading(352, 925, {}, false);

    //2nd xwallstake stuf 
    desiredLiftValue = 102.5; 
    iterations = 0; 
    liftPIDRunning = true;
    chassis.moveToPoint(-15, 66, 850, {.minSpeed = 20}, false);
    chassis.tank(20, 20);
    pros::delay(1200);
    chassis.tank(0,0);
    intakeMotor1.brake(); 
    pros::delay(300);
    desiredLiftValue = 260;
    iterations = 0; 
    liftPIDRunning = true; 
    chassis.tank(0,0);
    pros::delay(800);
    chassis.setPose(-12.913, 67.8, chassis.getPose().theta);
    
    intakeMotor1.move(-127);
    chassis.moveToPoint(-14, 56.5, 800, {.forwards = false});
    desiredLiftValue = 64; 
    liftkI = 0; 
    iterations = 0; 
    liftPIDRunning = true;  
    chassis.waitUntilDone();
    
    chassis.turnToPoint(-67.7, 48.8, 985, {}, false);
    //3 ring straight
    chassis.moveToPoint(-67.7, 48.8, 2200, {.maxSpeed = 56}, false);
    chassis.follow(alignWithLastRingSecondMogoSKILLS_txt, 5, 1200, false, false);
    //last ring 
    chassis.angularPID.kI = 0.025;
    chassis.turnToPoint(-59.9, 55.76, 650, {}, false);
    chassis.angularPID.kI = 0; 
    chassis.moveToPoint(-59.9, 55.76, 1000, {}, false);

    //drop mogo
    chassis.turnToHeading(471, 800, {}, false);  
    chassis.lateralPID.kI = 0.075;
    chassis.moveToPoint(-69.7, 57.3, 1000, {.forwards = false}, false);
    chassis.waitUntil(7);
    mogo.toggle(); 
    chassis.waitUntilDone(); 
    //1st ring on lb 
    chassis.moveToPose(11.55, 34.564, 486, 2450, {.lead = 0.5});
    desiredLiftValue = 102.5; 
    iterations = 0; 
    liftPIDRunning = true;
    chassis.waitUntilDone(); 

    /*
    chassis.turnToPoint(40.375, 14.909, 1000, {.forwards = false}, false);
    chassis.moveToPoint(40.375, 14.909, 1150, {.forwards = false, .maxSpeed = 65});
    chassis.waitUntil(29.5);
    mogo.toggle(); 
    chassis.waitUntilDone(); 
    chassis.turnToPoint(50, 15, 900, {}, false);
    
    chassis.moveToPoint(50, 15, 950, {.minSpeed = 20}, false);
    chassis.tank(20,20);
    pros::delay(800);
    chassis.lateralPID.kI = 0.1; 
    chassis.moveToPoint(chassis.getPose().x - (6 * sin(chassis.getPose(true).theta)), chassis.getPose().y - (6 * cos(chassis.getPose(true).theta)), 800, {.forwards = false});
    chassis.waitUntil(3);
    intakeMotor1.brake(); 
    chassis.waitUntilDone(); 
    desiredLiftValue = 285; 
    iterations = 0; 
    liftPIDRunning = true; 
    pros::delay(1000);
    chassis.moveToPoint(chassis.getPose().x - (4 * sin(chassis.getPose(true).theta)), chassis.getPose().y - (4 * cos(chassis.getPose(true).theta)), 800, {.forwards = false});
    chassis.lateralPID.kI = 0;
    desiredLiftValue = 64; 
    iterations = 0; 
    liftPIDRunning = true; 
    liftkI = 0; 
    intakeMotor1.move(-127);
    chassis.turnToPoint(19, -9, 850, {}, false);
    chassis.moveToPoint(19, -9, 900, {}, false);

    pros::delay(5000);
    */

}   
    

