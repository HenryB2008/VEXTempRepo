#include "..\include\autons\test.h"

bool autoClamp = true;

/*
redringrush
   /*
    allianceColor = 3; 
    colorSortOn = true; 

    chassis.setPose(-51.774, 28.354, 73);
    pros::delay(20); 
    chassis.moveToPose(-9.9, 40.9, 72, 1500, {.lead = 0.03, .earlyExitRange = 1.5});
    chassis.waitUntil(15);
    leftDoinker.toggle(); 
    chassis.waitUntilDone(); 
    chassis.follow(realRingRushMogoRED_txt, 5, 1400, false, false);
    mogo.toggle(); 
    leftDoinker.toggle();
    chassis.angularPID.kI = 0.04; 
    chassis.turnToHeading(10, 700, {}, false);
    chassis.angularPID.kI = 0; 
    allianceColor = 0; 
    colorSortOn = true; 
    chassis.moveToPose(-19, 51, 10, 1400, {.lead = 0.03}, false);
    chassis.turnToHeading(-140, 800, {}, false);
    chassis.moveToPose(-46, 21, -140, 1050, {.lead = 0.07});
    chassis.waitUntil(17);
    desiredLiftValue = 101.5; 
    iterations = 0; 
    liftPIDRunning = true;
    chassis.waitUntilDone();
    chassis.lateralPID.kI = 0.05;
    chassis.moveToPose(-54, 13, -137, 700, {.lead = 0.04}, false);
    chassis.lateralPID.kI = 0; 
    chassis.turnToHeading(-177, 800, {}, false);
    chassis.moveToPose(-55, 0, -178, 850, {.lead = 0.02}, false);
    colorSortOn = false; 
    intakeMotor1.brake(); 
    chassis.turnToHeading(-88, 850, {}, false);
    chassis.tank(34, 34);
    pros::delay(750);
    chassis.moveToPose(chassis.getPose().x - (6 * sin(chassis.getPose(true).theta)), chassis.getPose().y - 
    (6 * cos(chassis.getPose(true).theta)), chassis.getPose().theta, 700, {.forwards = false, .lead = 0.03}, false); 
    desiredLiftValue = 285; 
    iterations = 0; 
    liftPIDRunning = true; 
    pros::delay(600);
    chassis.moveToPose(chassis.getPose().x - (5 * sin(chassis.getPose(true).theta)), chassis.getPose().y - 
    (5 * cos(chassis.getPose(true).theta)), chassis.getPose().theta, 700, {.forwards = false, .lead = 0.03}, false); 
    chassis.turnToHeading(chassis.getPose().theta + 180, 1100, {}, false);
    desiredLiftValue = 64; 
    iterations = 0; 
    liftPIDRunning = true; 
    chassis.tank(46, 46);
    pros::delay(1000);
    chassis.tank(0,0);

    /*
    chassis.turnToHeading(-173, 700, {}, false);
    chassis.moveToPose(-50, 2, -175, 800, {.lead = 0.05}, false);
    colorSortOn = false; 
    chassis.turnToHeading(-84, 800, {}, false);
    chassis.moveToPose(-63, 2, -83, 800, {.lead = 0.03}, false);
    */
    /*
    chassis.moveToPose(chassis.getPose().x - (6 * sin(chassis.getPose(true).theta)), chassis.getPose().y - 
        (6 * cos(chassis.getPose(true).theta)), chassis.getPose().theta, 700, {.forwards = false, .lead = 0.03}, false); 
    desiredLiftValue = 285; 
    iterations = 0; 
    liftPIDRunning = true; 




    /*
    chassis.moveToPose(-24.4, 27.1, 2.9, 1600, {.forwards = false}, false);
    mogo.toggle(); 
    leftDoinker.toggle(); 
    allianceColor = 1; 
    colorSortOn = true; 
    */

void test(){
    colorSortOn = false; 
    
    chassis.tank(-10,10);
    pros::delay(1500);
    allianceColor = 0; 
 
    colorSortOn = true; 
    chassis.tank(10,10);
    pros::delay(10000);
}
void redCS() {
    //Grab ring rush rings and drive back
    chassis.setPose(-52.2,32.5,75);
    leftDoinker.extend();
    rightDoinker.extend();
    chassis.moveToPoint(-10.6, 43.6, 800, {}, false); 
    chassis.moveToPose(-24, 28, 0, 1200, {.forwards = false}); 
    //clamp and score 3 rings with colorSort
    chassis.waitUntil(20);
    mogo.toggle(); 
    chassis.waitUntil(25);
    leftDoinker.retract();
    rightDoinker.retract(); 
    chassis.waitUntilDone(); 
    allianceColor = 0;
    colorSortOn = true;                                         
    chassis.moveToPoint(-23.6, 57.1, 1500, {}, false);
    //score ring from corner
    chassis.turnToHeading(245, 600, {}, false);
    intakeMotor1.move(-127);
    chassis.moveToPoint(-49.3, 46.5,  1100, {.maxSpeed = 66}, false); 
    chassis.turnToHeading(320, 800, {}, false);
    chassis.moveToPoint(-63.6, 63.2, 800, {}, false);
    //put preload on ladybrown and score on alliance stake
    chassis.moveToPoint(-57.2, 56.5, 600, {.forwards = false}, false);
    chassis.turnToHeading(155, 1000, {}, false);
    chassis.moveToPose(-61.3, 7.1, 225, 1500);
    chassis.waitUntil(15);
    desiredLiftValue = 101; 
    liftPIDRunning = true; 
    chassis.waitUntilDone();
    desiredLiftValue = 298;
    liftPIDRunning = true;
    //move to positive corner
    chassis.turnToHeading(180, 800, {}, false);
    chassis.moveToPoint(-57.7, -44.3, 900, {}, false); 
}

void gRush() {
    //goal rush to 3rd mogo and back up 
    chassis.setPose(-55, -22.1, 115); 
    chassis.moveToPoint(-10.2, -43.165, 800, {}, false);
    rightDoinker.toggle();
    chassis.moveToPoint(-23, -34.5, 700, {.forwards = false}, false);
    rightDoinker.retract(); 
    //clamp on safe mogo 
    chassis.turnToHeading(180, 900, {}, false);
    chassis.moveToPoint(-24.3, -25., 950, {.forwards = false}, false);
    mogo.toggle();
    //score ring from small stack
    allianceColor = 0; 
    colorSortOn = true;
    chassis.moveToPoint(-24.4, -48, 1100, {.maxSpeed = 75}, false);
    //clamp onto 3rd mogo 
    chassis.turnToHeading(205, 950, {}, false);
    chassis.moveToPoint(-17.3, -38.3, 800, {.forwards = false});
    chassis.waitUntil(11);
    mogo.toggle();
    chassis.waitUntilDone(); 
    //go to corner and score bottom ring  
    chassis.turnToPoint(-61.6,  -64.1, 1000, {}, false);
    chassis.moveToPoint(-61.6, -64.1, 1600, {}, false);
    //score preload onto wallstake 
    chassis.moveToPoint(-27.5, -58.3, 800, {.forwards = false}); 
    chassis.turnToPoint(-5.9, -63.8,  900, {}, false);
    chassis.moveToPoint(-5.9, -63.8, 800, {}, false);
    desiredLiftValue = 298; 
    liftPIDRunning = true; 
}

void Baker(){
    //score on alliance stake
    chassis.setPose(-53.8, -11.4, 800);
    desiredLiftValue = 29800; 
    liftPIDRunning = true;
    pros::delay(500);
    desiredLiftValue = 6400; 
    liftPIDRunning = true; 
    //clamp mogo 
    chassis.turnToHeading(295, 1000, {}, false);
    chassis.moveToPoint(-28.7, -21.7, 900, {.forwards = false});
    chassis.waitUntil(31.5);
    mogo.toggle();
    chassis.waitUntilDone();
    chassis.turnToHeading(50, 800, {}, false);
    //drag center rings back
    chassis.moveToPoint(-9, -4.7, 900, {}, false);
    rightDoinker.extend();
    chassis.turnToHeading(45, 700, {}, false);
    leftDoinker.extend();
    //move back and score center rings
    chassis.moveToPoint(-37.7, -25, 800, {}, false);
    leftDoinker.retract();
    rightDoinker.retract(); 
    allianceColor = 0;  
    colorSortOn = true;
    chassis.swingToHeading(135, lemlib::DriveSide::RIGHT, 800, {.earlyExitRange = 10});
    std::vector<squiggles::ProfilePoint> clampPath = generator.generate({
        squiggles::Pose(-6.885 * 0.0254, 41.882 * 0.0254, chassis.getPose().theta * (M_PI / 180)),
        squiggles::Pose(-24.158  * 0.0254, 30.015 * 0.0254, 0 * (M_PI / 180))});
    driveRamsete(clampPath, 0.5, 0.6, false, 1); //less aggressive for clamp precision
    //score small ring stack ring and corner ring stack 
    chassis.moveToPoint(-22.391, -48.268, 1400, {}, false);
    chassis.turnToHeading(245, 950, {}, false);
    chassis.moveToPoint(-61.058, -63.774, 1500, {}, false);
    //drive back and touch ladder
    chassis.moveToPoint(-53.8, -60.2, 800, {}, false);
    desiredLiftValue = 170; 
    liftPIDRunning = true;
    chassis.moveToPose(-7.5, -16.3, 45, 1500, {},   false);

}
    
void awp(){
    //move back and score on alliance stake
    chassis.setPose(-57, 13, 255);
    chassis.moveToPoint(-62.2, 7.9, 700, {.forwards = false}, false);
    desiredLiftValue = 29800; 
    liftPIDRunning = true;
    pros::delay(500);
    desiredLiftValue = 6400; 
    liftPIDRunning = true; 
    //clamp mogo 
    chassis.moveToPoint(-28.762, 22.4, 800, {.forwards = false});
    chassis.waitUntil(27);
    mogo.toggle();
    chassis.waitUntilDone();
    chassis.turnToHeading(51, 1050, {}, false);
    //score ring rush stack 
    allianceColor = 0;
    colorSortOn = true; 
    chassis.moveToPoint(-5.9, 40, 1000, {} ,false); 
    chassis.turnToHeading(0, 800, {}, false);
    chassis.moveToPoint(-5.9, 49, 1100, {}, false);
    //score from both small stacks
    chassis.turnToHeading(255, 900, {}, false);
    chassis.moveToPoint(-21, 46, 1100, {}, false);
    chassis.turnToHeading(205, 900, {}, false);
    chassis.moveToPoint(-47, 1.8, 1150, {}, false);
    //unclamp first mogo, clamp second
    mogo.toggle();
    chassis.turnToHeading(315, 800, {}, false);
    chassis.moveToPoint(-27.5, -21, 800);
    chassis.waitUntil(27.5);
    mogo.toggle();
    chassis.waitUntilDone();
    //score last ring and touch ladder
    chassis.turnToHeading(175, 1200, {}, false);
    chassis.moveToPoint(-23.6, -46.5, 900, {}, false);
    desiredLiftValue = 170;
    liftPIDRunning = true; 
    chassis.moveToPoint(-12.4, -17.85, 1000, {}, false);

}


void RAMSETE() {
    chassis.setPose(0,0,1);
    std::vector<squiggles::ProfilePoint> knai = generator.generate({
        squiggles::Pose(0, 0, 1),
        squiggles::Pose(48 * 0.0254,48 * 0.0254, 1)});
    driveRamsete(knai, 0.7, 0.5, false, 0);
}

ASSET(alignWithLastRingFirstMogoSKILLS_txt); 

void find_tracking_center(float turnVoltage, uint32_t time) {
    chassis.setPose(0, 0, 0);
    unsigned long n = 0;
    float heading;
  
    std::cout << std::fixed << "\033[1mCopy this:\033[0m\n\\left[";
    left_motors.move_voltage(turnVoltage);
    right_motors.move_voltage(-turnVoltage);
    std::ostringstream out;
  
    auto end_time = time + pros::millis();
  
    int i = 0;
    
    while (pros::millis() < end_time && i++ < 10000) {
      std::cout << "\\left(" << chassis.getPose().x << "," <<chassis.getPose().y<< "\\right),";
      /*if (i % 250 == 0) {
        std::cout << "\\right]\n\\left[" ;
      } */
      if (i % 50 == 0) {
        std::cout.flush();
      }
      pros::delay(75);
    }  
    
    left_motors.brake();
    right_motors.brake(); 
    std::cout << "\b\\right]" << std::endl;
  
    std::cout << "Go to https://www.desmos.com/calculator/rxdoxxil1j to solve for offsets." << std::endl;
  }


