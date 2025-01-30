#ifndef _AUTONS_H
#define _AUTONS_H

#include "squiggles.hpp"
#include "lemlibSetup.h"
#include "ramsete.h"
#include "liftArm.h"



extern const float MAX_VEL;
extern const float MAX_ACCEL;
extern const float MAX_JERK;
extern const float ROBOT_WIDTH;

extern std::vector<float> convertUnits(lemlib::Pose position); 

extern squiggles::Constraints constraints;
extern squiggles::SplineGenerator generator;


extern void testing();
extern void qualAuto(); 





#endif 