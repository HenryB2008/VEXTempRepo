#ifndef _DRIVECODE_H
#define _DRIVECODE_H

#include "main.h"
#include "ports.h"
#include "lemlibSetup.h"
#include "liftArm.h"


extern bool intake_forward;
extern bool intake_reverse;
extern bool driveState; 

extern int leftY;
extern int rightY;
extern int LiftMotorPosition;

extern void driver();






#endif