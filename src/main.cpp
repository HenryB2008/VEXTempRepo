#include "main.h"
#include "init.h"
#include "drivecode.h"
#include "autons\test.h"
#include "autons\redAWP.h"
#include "autons\dopamineRed.h"
#include "autons\blueAWP.h"
#include "ports.h"
#include "autons\goalRushRed.h"
#include "autons\goalRushBlue.h"
#include "autons\redRingRushWP.h"
#include "autons\skills.h"
#include "autons\blueRingRushWP.h"
#include "lemlibSetup.h"
#include "autons\dopamineBlue.h"
#include "autons\redRingRushWPLadder.h"
#include "autoclamp.cpp"

void initialize() {
	init();
}

void opcontrol() {
	/*
	MCLConfig mcl_config(500, 0.05, 0.2);

	std::vector<MCLSensorParamfs> sensor_params = {
		{ 1, -4.0f, 4.0f, 0.0f        }, // North sensor: port 1, offset (-4, 4), facing forward (0 rad)
		{ 3, 6.5f,  0.75f, -M_PI_2    }, // East sensor: port 3, offset (6.5, 0.75), facing -90° (-π/2 rad)
		{ 16, -6.5f, 1.25f, M_PI_2     }  // West sensor: port 16, offset (-6.5, 1.25), facing +90° (π/2 rad)
	  };

	  MCLOdom mcl(mcl_config, chassis, sensor_params);

	  mcl.initialize(24, 72, -M_PI/2);

	*/
	colorSortOn = false; 
	lbMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	lbMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	driver();

}
void autonomous(){
	colorSortOn = false; 
	blueRingRushWP();
}	




   