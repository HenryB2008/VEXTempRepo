#include "skills.h"

ASSET(alignWithLastRingFirstMogoSKILLS_txt); 

void skills(){
    intakeMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    colorSortOn = false; 
    chassis.setPose(-61.592,-7.135,311);
    desiredLiftValue = 285; 
    iterations = 0; 
    liftPIDRunning = true; 
    pros::delay(900);
    //first mogo 
    chassis.moveToPoint(-50.462, -16.81, 650, {.forwards = false, .maxSpeed = 70}, false);
    mogo.toggle(); 
    intakeMotor1.move(-127);
    desiredLiftValue = 64;
    iterations = 0; 
    liftPIDRunning = true; 
    pros::delay(200);
    //first ring 
    chassis.turnToHeading(449, 800, {}, false);
    chassis.moveToPoint(-24.263, -17, 850, {}, false);
    chassis.lateralPID.kI = 0.075;
    chassis.moveToPoint(chassis.getPose().x - (3 * sin(chassis.getPose(true).theta)), chassis.getPose().y - (3 * cos(chassis.getPose(true).theta)), 525, {.forwards = false}, false); 
    chassis.lateralPID.kI = 0; 
    chassis.angularPID.kI = 0.025;
    chassis.turnToHeading(469, 600, {}, false);
    chassis.angularPID.kI = 0; 
    //second ring (on lb)
    chassis.moveToPoint(26.661, -35.447, 1300, {}, false); 
    chassis.angularPID.kI = 0.1;
    chassis.turnToPoint(2, -35, 600, {.forwards = false}, false);
    //chassis.turnToHeading(460, 600,  {}, false);
    chassis.angularPID .kI= 0; 
    chassis.moveToPoint(2, -35, 1000, {.forwards = false}, false);
    pros::delay(10); 
    liftkI = 0.0000055;  
    desiredLiftValue = 101; 
    iterations = 0; 
    liftPIDRunning = true;
    chassis.turnToPoint(2.35, -50.4, 850, {}, false);
    desiredLiftValue = 101; 
    iterations = 0; 
    liftPIDRunning = true;
    //score on wallstake
    chassis.moveToPoint(2.06, -45.4, 850, {.minSpeed = 25}, false); 
    chassis.tank(20, 20);
    
    pros::delay(900);
    intakeMotor1.brake(); 
    desiredLiftValue = 239;
    iterations = 0; 
    liftPIDRunning = true; 
    chassis.tank(0,0);
    pros::delay(700);
    intakeMotor1.move(-127);
    chassis.moveToPoint(0.75, -38, 800, {.forwards = false});
    desiredLiftValue = 64; 
    liftkI = 0; 
    iterations = 0; 
    liftPIDRunning = true;  
    chassis.waitUntilDone();
    chassis.turnToPoint(-56, -45, 945, {}, false);     //angle 623
    //3 ring straight 
    chassis.moveToPoint(-56, -45, 1900, {.maxSpeed = 64 }, false);
    chassis.follow(alignWithLastRingFirstMogoSKILLS_txt, 5, 1150, false, false);
    chassis.angularPID.kI = 0.025;
    chassis.turnToPoint(-48, -54, 650, {}, false);
    chassis.angularPID.kI = 0; 
    //last ring 
    chassis.moveToPoint(-48, -54, 1000, {}, false);
    chassis.turnToHeading(413, 800, {}, false);  
    chassis.lateralPID.kI = 0.05;
    //put mogo back 
    chassis.moveToPoint(-52.19, -57.9, 800, {.forwards = false});
    chassis.waitUntil(4);
    mogo.toggle(); 
    chassis.waitUntilDone(); 
    chassis.moveToPoint(-48, -54, 800, {}, false);
    chassis.lateralPID.kI = 0; 
    chassis.turnToPoint(-58, 20, 1100, {.forwards = false}, false);    //angle 531
    //clamp second mogo 
    chassis.moveToPoint(-54, 11, 800, {.forwards = false, .minSpeed = 80, .earlyExitRange = 7}); 

    chassis.moveToPose(-57, 24, 171, 1900, {.forwards = false, .maxSpeed = 80});
    chassis.waitUntilDone(); 
    
    mogo.toggle();  
    //first ring second mogo 
    chassis.turnToPoint(-36, 27, 800, {}, false); //angle 429 
    chassis.moveToPoint(-36, 27, 850, {}, false);
    chassis.lateralPID.kI = 0.075;
    chassis.moveToPoint(chassis.getPose().x - (4 * sin(chassis.getPose(true).theta)), chassis.getPose().y - (4 * cos(chassis.getPose(true).theta)), 625, {.forwards = false}, false); 
    chassis.lateralPID.kI = 0; 
    chassis.angularPID.kI = 0.015;

    //second ring second mogo 
    chassis.turnToHeading(412, 700, {}, false); //angle 413
    chassis.angularPID.kI = 0;
    chassis.moveToPoint(11.2, 63.2, 1550, {}, false);
    chassis.angularPID.kI = 0.025; 
    chassis.turnToHeading(423, 600, {}, false);
    chassis.angularPID.kI = 0; 
    pros::delay(10); 
    chassis.moveToPoint(-12, 52, 1000, {.forwards = false}, false);
    desiredLiftValue = 101; 
    iterations = 0; 
    liftPIDRunning = true;
    chassis.turnToHeading(352, 850, {}, false);
    //2nd xwallstake stuf 
    liftkI = 0.0000055;  
    desiredLiftValue = 101; 
    iterations = 0; 
    liftPIDRunning = true;
    chassis.moveToPoint(-15, 66, 850, {.minSpeed = 25}, false);
    chassis.tank(20, 20);
    pros::delay(900);
    intakeMotor1.brake(); 
    desiredLiftValue = 239;
    iterations = 0; 
    liftPIDRunning = true; 
    chassis.tank(0,0);
    pros::delay(700);
    intakeMotor1.move(-127);
}   
    

