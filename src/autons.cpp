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


void skills() {
    //score preload onto alliance stake
    chassis.setPose(0,0,270);
    liftPIDRunning = true;
    desiredLiftValue = 31500;
    pros::delay(900);
    liftPIDRunning = true;
    desiredLiftValue = 23500; 


    //first mogo
    chassis.moveToPoint(11, 0, 800, {.forwards = false}, false);
    chassis.turnToHeading(180, 800, {}, false);
    chassis.moveToPoint(chassis.getPose().x, 23, 800, {.forwards = false}, false);
    mogo.toggle();
    pros::delay(250);
    chassis.turnToHeading(360, 1300, {}, false);
    intakeMotor1.move(-127);
    chassis.moveToPose(chassis.getPose().x, 52, 0, 1100, {.maxSpeed = 55}, false);
    chassis.moveToPose(chassis.getPose().x, 63.5, 0, 1000, {.maxSpeed = 55}, false);
    pros::delay(2000);
    chassis.moveToPoint(chassis.getPose().x, 55, 600, {.forwards = false}, false);
    chassis.turnToHeading(-114, 800, {}, false);


    
}


void qualAutoRed() {
    liftPIDRunning = true; 
    desiredLiftValue = 22800; 
    chassis.setPose(0, 0, 0);
    pros::delay(5);
    chassis.moveToPose(0,-35,0,2000, {.forwards = false, .minSpeed = 95, .earlyExitRange = 3, });
    chassis.moveToPose(0,-46.3, 8.5, 1175, {.forwards = false});
    chassis.waitUntilDone(); 
    mogo.toggle(); 
    pros::delay(100);
    intakeMotor1.move(-127);
    chassis.moveToPoint(0, -36, 850, {}, false); 
    mogo.toggle();
    pros::delay(150);
    chassis.turnToHeading(-123, 1000, {}, false);
    chassis.moveToPoint(10, -28.3, 1000, {.forwards = false}, false);
    mogo.toggle(); 
    pros::delay(300);
    chassis.turnToHeading(-112, 650, {}, false); 
    chassis.moveToPoint(-14, -38.4, 1200, {},false); 
    

    /*
    pros::delay(500);
    chassis.turnToHeading(-76, 1100, {}, false);
    chassis.moveToPoint(4, -38.5, 800, {.forwards = false}, false);
    mogo.toggle(); 
    pros::delay(100);
    chassis.moveToPoint(-3.3, -37.2, 800, {}, false); 
    chassis.turnToHeading(-127, 850, {}, false); 
    chassis.moveToPoint(10.9, -28, 800, {.forwards = false}, false);
    mogo.toggle();
    pros::delay(500);
    chassis.turnToHeading(-113, 450, {}, false);
    chassis.moveToPoint(-15, -37, 1100, {}, false);
    */
    
    

    chassis.moveToPose(12, -2.5, -108, 2900, {.forwards = false}, false);
    
    chassis.turnToHeading(chassis.getPose().theta +180, 1200, {}, false);
    raiseSolenoid.toggle(); 
    chassis.moveToPose(26, 0.6, 68.3, 900, {}, false);
    

    raiseSolenoid.toggle(); 
    
    pros::delay(250);
    chassis.moveToPose(18.3, -2.4, 68.7, 900, {.forwards = false}, false);
    chassis.moveToPose(34, -30  , -220, 2000, {.minSpeed = 75}, false);
}

//screw white line on corner, wiggly screw on intersection 
void qualAutoFail(){
    liftPIDRunning = true; 
    desiredLiftValue = 22800; 
    chassis.setPose(0, 0, 0);
    pros::delay(5);
    chassis.moveToPose(0,-35,0,2000, {.forwards = false, .minSpeed = 95, .earlyExitRange = 3, });
    chassis.moveToPose(0,-46.3, 8.5, 1175, {.forwards = false});
    chassis.waitUntilDone(); 
    mogo.toggle(); 
    pros::delay(300);
    intakeMotor1.move(-127);
    chassis.moveToPoint(0, -36, 600, {}, false); 
    pros::delay(500);
    chassis.turnToHeading(-76, 1100, {}, false);
    chassis.moveToPoint(4, -38.5, 1050, {.forwards = false}, false);
    mogo.toggle(); 
    pros::delay(100);
    chassis.moveToPoint(-3.3, -37.2, 800, {}, false); 
    chassis.turnToHeading(-134, 1100, {}, false);
    chassis.moveToPose(9, -27.4, -105, 2000, {.forwards = false}, false); 
    mogo.toggle(); 
    pros::delay(500);
    chassis.moveToPose(-18.5, -43.7, -125.6, 2000, {}, false);
    chassis.moveToPose(12, -2.5, -108, 3200, {.forwards = false}, false);
    
    chassis.turnToHeading(chassis.getPose().theta +180, 1200, {}, false);
    raiseSolenoid.toggle(); 
    chassis.moveToPose(25.1, 0., 67.25, 900, {}, false);

    raiseSolenoid.toggle(); 
    
    pros::delay(250);
    chassis.moveToPose(18.3, -2.4, 68.7, 900, {.forwards = false}, false);

    chassis.moveToPose(34, -30  , -220, 2000, {.minSpeed = 75}, false);




    
}


    


void testing() {
 


   
}





