#include "distanceReset.h"
#include "lemlibSetup.h"


double getDistCos(char side) {
    float distance = 0;
    float globalDistance = 0;   
    float offset = 0; 
    if (side == 'L') {
        offset = 6.5; 
        distance = leftDistance.get() / 25.4;
        globalDistance =  (offset + distance) * (cos(chassis.getPose(true).theta - M_PI_2));
    } else if(side == 'R') {
        offset = 6.5; 
        distance = rightDistance.get() /25.4; 
        globalDistance = (offset + distance) * (cos(chassis.getPose(true).theta + M_PI_2));
    } else if(side == 'F'){
        offset = 4.0; 
        distance = frontDistance.get() / 25.4;
        globalDistance = (offset + distance) * (cos(chassis.getPose(true).theta));

    }
    return globalDistance;
}

double getDistSin(char side) {
    float distance = 0;
    float globalDistance = 0;   
    float offset = 0; 
    if (side == 'L') {
        offset = 6; 
        distance = leftDistance.get() / 25.4;
        globalDistance =  (offset + distance) * (sin(chassis.getPose(true).theta - M_PI_2));
    } else if(side == 'R') {
        offset = 6.5; 
        distance = rightDistance.get() /25.4; 
        globalDistance = (offset + distance) * (sin(chassis.getPose(true).theta + M_PI_2));
    }
    else if(side == 'F'){
        offset = 4.0; 
        distance = frontDistance.get() / 25.4;
        globalDistance = (offset + distance) * (cos(chassis.getPose(true).theta));
    }
    return globalDistance;

}