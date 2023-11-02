#include "main.h"
#include "lemlib/api.hpp"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
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
void autonomous() {}

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
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor left_mtr(1);
	pros::Motor right_mtr(2);

	pros::Motor left_drive[3] = {pros::Motor(10, pros::E_MOTOR_GEAR_BLUE), pros::Motor(-4, pros::E_MOTOR_GEAR_BLUE), pros::Motor(19, pros::E_MOTOR_GEAR_BLUE)};	// front mid back
	pros::Motor right_drive[3] = {pros::Motor(-1, pros::E_MOTOR_GEAR_BLUE), pros::Motor(8, pros::E_MOTOR_GEAR_BLUE), pros::Motor(-12, pros::E_MOTOR_GEAR_BLUE)};

	pros::Motor cata[2] = {pros::Motor(5, pros::E_MOTOR_GEAR_GREEN), pros::Motor(-9, pros::E_MOTOR_GEAR_GREEN)};	// left right
	for (pros::Motor m : cata) {
		m.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	}

	pros::ADIDigitalOut wings('A');
	pros::ADIDigitalOut load_arm('B');

	bool wings_deployed = true;		// true is actually not deployed, it's just the piston state for not deployed is 1
	bool load_arm_deployed = true;

	wings.set_value(wings_deployed);
	load_arm.set_value(wings_deployed);

	int cata_retract_length = 250;
	int cata_retract_start = -cata_retract_length;

	while (true) {
		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);

		for (pros::Motor m : left_drive) {
			m.move(left);
		}

		for (pros::Motor m : right_drive) {
			m.move(right);
		}

		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
			wings_deployed = !wings_deployed;
			wings.set_value(wings_deployed);
		}

		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
			load_arm_deployed = !load_arm_deployed;
			load_arm.set_value(load_arm_deployed);
		}


		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
			cata_retract_start = pros::millis();
		}
		
		if (pros::millis() - cata_retract_start < cata_retract_length) {
			for (pros::Motor m : cata) {
				m.move(127);
			}
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			for (pros::Motor m : cata) {
				m.move(127);
			}
		} else {
			for (pros::Motor m : cata) {
				m.move(0);
			}
		}

		pros::delay(20);
	}
}
