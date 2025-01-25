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





void testing() {
    chassis.setPose(0, 0, 0);
    pros::delay(100);
    std::vector<squiggles::ProfilePoint> firstPath =  generator.generate({
        squiggles::Pose(0.0, 0.0, 0),
        squiggles::Pose(24 * 0.0254, 24 *  0.0254, 0 * (M_PI/180  ))});

    std::vector<squiggles::ProfilePoint> secondPath =  generator.generate({
        squiggles::Pose(chassis.getPose().x * 0.0254, chassis.getPose().y * 0.0254, chassis.getPose().theta * (M_PI/180)),
        squiggles::Pose(0,0, 0)});

    

    printPath(firstPath);

    driveRamsete(firstPath, 0.7, 1.3, false, 0.5 * 0.0254);
    //      driveRamsete(secondPath, 0.7, 1.3, true, 0.5 * 0.0254);
    
    //chassis.moveToPose(24,24,90, 10000, {.earlyExitRange = 0.5}, false);

   
}



