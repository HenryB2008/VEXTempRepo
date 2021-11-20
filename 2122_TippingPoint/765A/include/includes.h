#ifndef _INCLUDES_
#define _INCLUDES_

#include "main.h"
#include "pid.h"
#include "drive.h"
#include "pneumatics.h"
#include "button.h"
#include "intake.h"
#include "effectors.h"

extern Drive *drive;
extern Pneumatics *pneum;
extern Effectors effectors;
extern Intake *intake;
extern Button *buttons;

#endif