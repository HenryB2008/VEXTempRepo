#include "autonTemplate.h"

//ROBOT WEIGHT 14 LB 

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

void moveToStraight(double distance, int timeout){
    chassis.moveToPoint((chassis.getPose().x + (distance * cos(chassis.getPose().theta * M_PI/ 180))), (chassis.getPose().y + (distance * sin(chassis.getPose().theta * M_PI/ 180))), timeout);
}







