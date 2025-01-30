#ifndef _RAMSETE_H
#define _RAMSETE_H 

#include <cmath> 
#include <vector> 
#include "lemlibSetup.h"
#include "autons.h"




extern void printPath(std::vector<squiggles::ProfilePoint> path);

extern void driveRamsete(
    std::vector<squiggles::ProfilePoint> path, 
    float zeta, 
    float b,
    bool backward,
    float errorDistance,
    int timeout
); 

#endif 