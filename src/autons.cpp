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
    chassis.moveToPoint(chassis.getPose().x, 23, 850, {.forwards = false}, false);
    mogo.toggle();
    pros::delay(300);
    chassis.turnToHeading(360, 1300, {}, false);
    pros::delay(10);
    intakeMotor1.move(-127);
    pros::delay(10);
    chassis.moveToPose(13.6, 48.9, 2.6, 2300, {.maxSpeed = 55}, false);
    chassis.moveToPose(chassis.getPose().x, 63, 2.6, 1000, {.maxSpeed = 55}, false);
    pros::delay(900);
    chassis.moveToPoint(chassis.getPose().x, 55, 600, {.forwards = false}, false);
    chassis.turnToHeading(-114, 800, {}, false);
    chassis.moveToPoint(1.7, 47.6, 1600, {}, false);
    chassis.turnToHeading(-182, 800, {}, false);
    chassis.moveToPoint(0.9, 58.15, 900, {.forwards = false}, false);
    pros::delay(100);
    mogo.toggle(); 
    pros::delay(200);

    //second mogo 
    chassis.moveToPose(9.6, -1.6, -176, 2050, {}, false);
    chassis.turnToHeading(-353.6, 1000, {}, false);
    chassis.moveToPoint(6.5, -17, 800, {.forwards = false}, false);
    mogo.toggle(); 
    pros::delay(400);
    chassis.turnToHeading(-175.6, 1000, {}, false); 
    chassis.moveToPose(4.7, -41.9, -175.5, 2200, {.maxSpeed = 55}, false);
    chassis.moveToPose(4.3, -50.8, -175.5, 1250, {.maxSpeed = 55}, false);  
    chassis.moveToPose(4.3, -45, -175.5, 800, {.forwards = false}, false);
    chassis.turnToHeading(290, 800, {}, false);
    chassis.moveToPoint(-7, -39, 1000, {}, false);
    
    chassis.turnToHeading(25, 800, {}, false);
    chassis.moveToPoint(-7, -48, 900, {.forwards = false}, false); 
    mogo.toggle();
    pros::delay(200);


    //wallstake
    chassis.moveToPoint(-5, -40, 900, {}, false);
    chassis.moveToPose(35, -28, 121, 1450,{.minSpeed = 65,  .earlyExitRange = 3}); 
    intakeMotor1.move(127);
    chassis.moveToPose(52, -49.4, 178, 3800);
    chassis.waitUntil(12.5);
    liftPIDRunning = true; 
    desiredLiftValue = 21200; 
    intakeMotor1.move(-127); 
    chassis.moveToPose(52, -58, 180, 1650, {}, false);
    chassis.waitUntilDone();
    liftPIDRunning = true;
    desiredLiftValue = 32000;
    pros::delay(1100);
    chassis.moveToPoint(chassis.getPose().x, -43, 800, {.forwards = false}, false);
    liftPIDRunning = true;
    desiredLiftValue = 26000;
    pros::delay(1000);


    //mogo 3
    chassis.turnToHeading(45, 900, {}, false);
    chassis.moveToPoint(76, -24, 1200, {}, false);
    chassis.waitUntilDone();
    intakeMotor1.brake(); 
    chassis.turnToHeading(218.5, 1000, {}, false); 
    
    chassis.moveToPoint(100, 0, 1350, {.forwards = false, .maxSpeed = 65}, false);  ////angle -131.5 
    mogo.toggle();
    intakeMotor1.move(-127); 
    chassis.turnToHeading(8, 900, {}, false);
    chassis.moveToPose(99, -26, 10, 900, {.forwards = false}, false); //angle 10
    chassis.turnToHeading(28, 1000, {}, false);
    chassis.turnToHeading(334, 1000, {}, false);
    mogo.toggle(); 
    chassis.moveToPoint(110, -55, 2000, {.forwards = false}, false);     
    chassis.setPose(0,0,0);
    chassis.moveToPoint(0,39,1000, {}, false);
    chassis.turnToHeading(71, 900, {}, false);
    chassis.moveToPose(32, 61, 55, 1400, {}, false);
    chassis.turnToHeading(22, 700, {}, false);
    chassis.setPose(30,64,22);
    pros::delay(5);
    chassis.turnToHeading(15, 900, {}, false);
    chassis.moveToPose(41, 106,15, 2500, {}, false);


    //chassis.moveToPose(72, -31, -92, 1000, {.forwards = false}, false); 
    




    
    

    

    
}



void qualAutoBlue() {
    liftPIDRunning = true; 
    desiredLiftValue = 22800; 
    chassis.setPose(0, 0, 0);
    pros::delay(5);
    chassis.moveToPose(0,-35,0,2000, {.forwards = false, .minSpeed = 95, .earlyExitRange = 3, });
    chassis.moveToPose(0,-46.3, 351.5, 1475, {.forwards = false});
    chassis.waitUntilDone(); 
    mogo.toggle(); 
    pros::delay(100);
    intakeMotor1.move(-127);
    chassis.moveToPoint(0, -36, 850, {}, false); 
    mogo.toggle();
    pros::delay(150);
    chassis.turnToHeading(123, 1000, {}, false);
    chassis.moveToPoint(-10, -28.3, 1000, {.forwards = false}, false);
    mogo.toggle(); 
    pros::delay(300);
    chassis.turnToHeading(112, 650, {}, false); 
    chassis.moveToPoint(14, -38.4, 1200, {},false); 
    chassis.moveToPose(-12, -2.5, 108, 2900, {.forwards = false}, false);
    chassis.turnToHeading(chassis.getPose().theta +180, 1200, {}, false);
    raiseSolenoid.toggle(); 

    chassis.moveToPose(-26.2, 2, 287, 900, {}, false);


    raiseSolenoid.toggle(); 
    pros::delay(250);
    chassis.moveToPose(-18.3, -2.4, 291.3, 900, {.forwards = false}, false);
    chassis.moveToPose(-34, -30  , 220, 2000, {.minSpeed = 75}, false); 
    
    
    
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

    chassis.moveToPose(25.1, 0, 67.25, 900, {}, false);
    

    raiseSolenoid.toggle(); 

    
    pros::delay(250);
    chassis.moveToPose(18.3, -2.4, 68.7, 900, {.forwards = false}, false);
    chassis.moveToPose(34, -30  , -220, 2000, {.minSpeed = 75}, false);
}

//screw white line on corner, wiggly screw on intersection 


    


void testing() {
 
    chassis.setPose(0,0,0);
    intakeMotor1.move(-127);
    chassis.moveToPoint(0,5, 1000, {}, false);
    pros::delay(10000);
  

   
}





