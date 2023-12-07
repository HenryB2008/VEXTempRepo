#include "main.h"
#include "lemlib/api.hpp"
#include "routes.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::MotorGroup left_drive({pros::Motor(10, pros::E_MOTOR_GEAR_BLUE), pros::Motor(-4, pros::E_MOTOR_GEAR_BLUE), pros::Motor(19, pros::E_MOTOR_GEAR_BLUE)});	// front mid back
pros::MotorGroup right_drive({pros::Motor(-1, pros::E_MOTOR_GEAR_BLUE), pros::Motor(8, pros::E_MOTOR_GEAR_BLUE), pros::Motor(-12, pros::E_MOTOR_GEAR_BLUE)});

pros::MotorGroup cata({pros::Motor(5, pros::E_MOTOR_GEAR_RED), pros::Motor(-9, pros::E_MOTOR_GEAR_RED)});	// left right

pros::Rotation left_rot(16);
pros::Rotation right_rot(-17);
pros::Imu imu(18);	// check this port

lemlib::Drivetrain_t drivetrain {
	&left_drive,
	&right_drive,
	11.71875, // track width
	4, // wheel diameter
	300 // wheel rpm
};

lemlib::TrackingWheel left_tracking(
	&left_rot, // rotation sensor object
	2.75, // wheel diameter
	-2.890625, // tracking center offset (negative if to left of tracking center)
	1 // TRACKING WHEEL gear ratio
);

lemlib::TrackingWheel right_tracking(
	&left_rot, // rotation sensor object
	2.75, // wheel diameter
	2.890625, // tracking center offset (negative if to left of tracking center)
	1 // TRACKING WHEEL gear ratio
);

lemlib::OdomSensors_t odom_sensors {
	&left_tracking, // &left_tracking, // parallel tracking wheel left
	nullptr, // parallel tracking wheel right
	nullptr, // perpendicular tracking wheel 1
	nullptr, // perpendicular tracking wheel 2
	&imu // inertial sensor
};

// forward/backward PID
lemlib::ChassisController_t lateral_controller {
    22, // kP
    125, // kD 80 pretty good
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    100 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angular_controller {
    4, // kP
    25, // 40 kD
    1, // smallErrorRange		//1
    100, // smallErrorTimeout
    2, // largeErrorRange
    500, // largeErrorTimeout
    100 // slew rate		// 0
};

lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller, odom_sensors);

pros::ADIDigitalOut left_wing('A');
pros::ADIDigitalOut right_wing('B');

bool wings_deployed = true;		// true is actually not deployed, it's just the piston state for not deployed is 1
bool load_arm_deployed = true;

int cata_retract_length = 250;
int cata_retract_start = -cata_retract_length;



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();

	left_wing.set_value(wings_deployed);
	right_wing.set_value(wings_deployed);

	chassis.calibrate();

	cata.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);

	cata.set_zero_position(0);

	/*
	while (true) {
		pros::lcd::print(0, "%f", cata.get_positions()[1]);
		pros::delay(50);
	}
	*/
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	//initialize();
	//competition_initialize();
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	
}

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
	skills(chassis);
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
	// chassis.moveTo(0, 10, 0, 1000, false, true, 0, 0.6, 127, true);

	// chassis.turnTo(30, 0, 10000);
	// chassis.moveTo(0, 48, 10000, 40, true);

	/*
	while (true) {
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
			break;
		}
	} */

	cata.move(0);

	while (true) {
		lemlib::Pose pose = chassis.getPose();
		pros::lcd::print(0, "x: %f", pose.x);
		pros::lcd::print(1, "y: %f", pose.y);
		pros::lcd::print(2, "theta: %f", pose.theta);
		
		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);

		left_drive.move(left);
		right_drive.move(right); // right

		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
			wings_deployed = !wings_deployed;
			left_wing.set_value(wings_deployed);
		}

		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
			load_arm_deployed = !load_arm_deployed;
			right_wing.set_value(wings_deployed);
		}


		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
			cata_retract_start = pros::millis();
		}
		
		if (pros::millis() - cata_retract_start < cata_retract_length) {
			cata.move(127);
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			cata.move(127);
		} else {
			cata.move(0);
		}

		pros::delay(20);
	}
}
