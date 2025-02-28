#include "main.h"
#include "init.h"
#include "drivecode.h"
#include "autons\test.h"
#include "autons\redRingRush.h"
#include "autons\redGoal.h"
#include "autons\blueGoal.h"
#include "autons\blueRingRush.h"
#include "autons\skills.h"
#include "autons\redRingSafe.h"
#include "autons\blueRingSafe.h"
#include "autons\redRingElims.h"
#include "autons\blueRingElims.h"

void initialize() {
	init();
}

void opcontrol() {
	
	colorSortOn = false; 
	driver();
}

void autonomous(){








	test();
	}
