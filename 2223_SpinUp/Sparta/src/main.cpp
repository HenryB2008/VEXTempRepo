#include "main.h"
#include "drive.h"
#include "controller.h"
#include "odometry.h"
#include "ports.h"
#include "auton.h"
#include <cstdio>
#include <sys/_stdint.h>

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */


void initialize() {
	pros::lcd::initialize();

	Drive::setBrakeMode(okapi::AbstractMotor::brakeMode::coast);

	Odometry::init();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {

	// Auton::AUTON_rollerAndShoot();
	Auton::SKILLS();
	
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

	const uint32_t START_TIME = pros::c::millis();

	Odometry::setPos({ 0_ft, 0_ft, 0_deg });

	//okapi::ADIEncoder rightEnc(RIGHT_TRACKING_WHEEL_TOP, RIGHT_TRACKING_WHEEL_BOTTOM);
    //okapi::ADIEncoder midEnc(MID_TRACKING_WHEEL_TOP, MID_TRACKING_WHEEL_BOTTOM, true);

	//rightEnc.reset();
	//midEnc.reset();
	
	while (true) {
		// If the controller map doesn't contain the endgame button key and enough time has passed (so it's endgame), add the input
		// 110000 ms = 110 seconds = 1 minute 50 seconds
		// TODO: add an actual endgame method
		if (!Controller::toggleContains(ENDGAME) && pros::c::millis() - START_TIME > 110000) {
			printf("woop");
			Controller::addToggleControl(ENDGAME, [](){ pros::ADIDigitalOut piston('A'); piston.set_value(true); });
		}

		Controller::step();
		
		Drive::arcade(Controller::getForward(), Controller::getYaw());

		pros::delay(DELAY);
	}
	
} 