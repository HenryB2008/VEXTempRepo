#ifndef _AUTONTEMPLATE_H
#define _AUTONTEMPLATE_H

#include "squiggles.hpp"
#include "lemlibSetup.h"
#include "ramsete.h"
#include "liftArm.h"
#include "colorSort.h"
#include "init.h"
#include "distanceReset.h"
#include "ports.h"

extern const float MAX_VEL;
extern const float MAX_ACCEL;
extern const float MAX_JERK;
extern const float ROBOT_WIDTH;


extern std::vector<float> convertUnits(lemlib::Pose position); 

extern squiggles::Constraints constraints;
extern squiggles::SplineGenerator generator;

extern void moveToStraight(double distance, int timeout); 




#endif 