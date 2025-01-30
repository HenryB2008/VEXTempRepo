#include "autons.h"

const float MAX_VEL = 1.645 * 0.5; //meters PER SCEOND
const float MAX_ACCEL = 3.894; //meters PER SECOND^2 
const float MAX_JERK = 2 * MAX_ACCEL; 
const float ROBOT_WIDTH = 0.3429; //meters



std::vector<float> convertUnits(lemlib::Pose position) {
    std::vector<float> converted = {static_cast<float>(position.x * 0.0254),
                                    static_cast<float>(position.y * 0.0254),
                                    static_cast<float>(position.theta * M_PI/180)}; 
    return converted; 
}




squiggles::Constraints constraints = squiggles::Constraints(MAX_VEL, MAX_ACCEL, MAX_JERK);
squiggles::SplineGenerator generator = squiggles::SplineGenerator(
    constraints,
    std::make_shared<squiggles::TankModel>(ROBOT_WIDTH, constraints));


void qualAutoActual() {
    
}

//screw white line on corner, wiggly screw on intersection 
void qualAuto(){
    liftPIDRunning = true; 
    desiredLiftValue = 22800; 
    chassis.setPose(0, 0, 0);
    pros::delay(5);
    chassis.moveToPose(0,-35,0,2000, {.forwards = false, .minSpeed = 95, .earlyExitRange = 3, });
    chassis.moveToPose(0,-47, 8.5, 1350, {.forwards = false});
    chassis.waitUntilDone(); 
    mogo.toggle(); 
    pros::delay(300);
    intakeMotor1.move(-127);
    chassis.moveToPoint(0, -36, 600, {}, false); 
    pros::delay(500);
    chassis.turnToHeading(-76, 1100, {}, false);
    chassis.moveToPoint(4, -38.5, 800, {.forwards = false}, false);
    mogo.toggle(); 
    pros::delay(100);
    chassis.moveToPoint(-3.3, -37.2, 800, {}, false); 
    chassis.turnToHeading(-134, 1100, {}, false);
    chassis.moveToPose(9, -27.4, -105, 2000, {.forwards = false}, false); 
    mogo.toggle(); 
    pros::delay(500);
    chassis.moveToPose(-18.5, -43.7, -125.6, 2000, {}, false);
    chassis.moveToPose(16.7, -0.5, -106, 3800, {.forwards = false}, false);
    chassis.turnToHeading(chassis.getPose().theta + 180, 1000, {}, false);

    
}

void skills() {
    //score preload onto alliance stake
    chassis.setPose(0,0,0);
    liftPIDRunning = true;
    desiredLiftValue = 31500;
    pros::delay(900);
    liftPIDRunning = true;
    desiredLiftValue = 22800; 

    //clamp onto first mogo
    chassis.moveToPoint(0, 16, 1000, {}, false);
    chassis.turnToHeading(90, 800, {}, false);
    chassis.moveToPoint(-24, chassis.getPose().y, 1000, {.forwards = false, .earlyExitRange = 4});
    mogo.toggle(); 
    
    //score 3 rings onto mogo 
    chassis.turnToHeading(chassis.getPose().theta + 180, 800);
    intakeMotor1.move(-127);
    chassis.moveToPoint(-47, chassis.getPose().y, 1000, {}, false);
    chassis.moveToPoint(-59, 15.5, 1000, {}, false);
    chassis.turnToPoint(-48, 3, 800, {}, false);
    chassis.moveToPoint(-48, 3, 100, {}, false); 
    chassis.turnToPoint(-62, -3, 800, {.forwards = false}, false); 

    //place mogo onto corner 
    chassis.moveToPoint(-62, -3, 1000,  {.forwards = false});
    chassis.waitUntil(8);
    mogo.toggle(); 
    chassis.waitUntilDone(); 


    //move to second mogo and clamp 
    chassis.turnToPoint(21.484, 15.365, 800, {.forwards = false}, false); 
    chassis.moveToPoint(21.484, 15.365, 1300, {.forwards = false});
    chassis.waitUntil(75);
    mogo.toggle(); 
    chassis.waitUntilDone(); 

    //score 3 rings onto second mogo 
    chassis.turnToPoint(59, 14, 800, {}, false);
    chassis.moveToPoint(59, 14, 1200, {.maxSpeed = 65}, false);
    chassis.turnToPoint(47, 1, 800, {}, false);
    chassis.moveToPoint(47, 1, 800, {}, false);

    //place second mogo into corner 
    chassis.turnToPoint(64, -3, 800, {.forwards = false}, false);
    chassis.moveToPoint(64, -3, 1000, {.forwards = false});
    chassis.waitUntil(8);
    mogo.toggle(); 
    chassis.waitUntilDone(); 

    //move to wallstake and score
    chassis.turnToPoint(58, 61, 800, {}, false);
    chassis.moveToPoint(58, 62, 1300, {}, false);
    chassis.turnToHeading(90, 800, {}, false);
    chassis.moveToPoint(65, chassis.getPose().y, 800, {.forwards = false}, false);
    liftPIDRunning = true;
    desiredLiftValue = 31500;
    pros::delay(900);
    liftPIDRunning = true;
    desiredLiftValue = 22800; 

    //move to third mogo and intake red
    chassis.turnToPoint(46, 84, 800, {}, false);
    chassis.moveToPoint(46, 84, 1200, {}, false);
    chassis.turnToPoint(-1, 107, 800, {.forwards = false}, false);

    //clamp and score ring
    chassis.moveToPoint(-1, 107, 1200, {.forwards = false});
    chassis.waitUntil(45);
    mogo.toggle();
    chassis.waitUntilDone(); 
    pros::delay(900);
    
    //move to second ring and intake and score
    chassis.turnToPoint(23, 82, 800, {}, false);
    chassis.moveToPoint(23, 82, 1200, {}, false);
    pros::delay(500);
    
    //clamp third mogo 
    chassis.turnToPoint(64, 127, 800, {.forwards = false}, false); 
    chassis.moveToPoint(64, 127, 1100, {.forwards = false}, false);
    mogo.toggle(); 

    //move to fourth  mogo and push into corner
    chassis.turnToPoint(23, 101, 800, {}, false);
    chassis.moveToPoint(23, 101, 1000, {}, false);
    chassis.turnToPoint(-24, 121, 800, {.forwards = false}, false);
    chassis.moveToPoint(-24, 121, 800, {.forwards = false});
    chassis.waitUntil(40);
    mogo.toggle();
    chassis.waitUntilDone(); 
    chassis.turnToPoint(-66, 127, 800, {.forwards = false}, false);
    chassis.moveToPoint(-66, 127, 800, {.forwards = false}, false);
    mogo.toggle(); 

    //move to second wall stake and score
    chassis.turnToPoint(-60, 61, 800, {}, false);
    chassis.moveToPoint(-60, 61, 1200, {}, false);
    chassis.turnToHeading(90, 800, {}, false);
    chassis.moveToPoint(-70, chassis.getPose().y, 800, {}, false); 
    liftPIDRunning = true;
    desiredLiftValue = 31500;
    pros::delay(900);
    liftPIDRunning = true;
    desiredLiftValue = 22800; 
    
}
    


void testing() {
 


   
}





