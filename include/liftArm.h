#ifndef _LIFTARM_H
#define _LIFTARM_H

#include "main.h"
#include "ports.h"



extern double liftkP;
extern double liftkI;
extern double liftkD;
extern double antiWindup; 


extern int liftError; 
extern int liftPrevError; 
extern int liftDerivative; 
extern int liftTotalError;

extern int iterations; 

extern int desiredLiftValue;
extern bool liftPIDRunning;

extern void liftPIDTask(void* param);

#endif