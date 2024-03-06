#include "main.h"
#include "lemlib/api.hpp"
#include "routes.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::MotorGroup left_drive({pros::Motor(19, pros::E_MOTOR_GEAR_BLUE), pros::Motor(-14, pros::E_MOTOR_GEAR_BLUE), pros::Motor(12, pros::E_MOTOR_GEAR_BLUE)});	// front mid back
pros::MotorGroup right_drive({pros::Motor(-10, pros::E_MOTOR_GEAR_BLUE), pros::Motor(9, pros::E_MOTOR_GEAR_BLUE), pros::Motor(-20, pros::E_MOTOR_GEAR_BLUE)});

pros::MotorGroup cata({pros::Motor(18, pros::E_MOTOR_GEAR_GREEN)});	// left right
pros::MotorGroup intake({pros::Motor(1, pros::E_MOTOR_GEAR_BLUE)});

pros::Rotation left_rot(16);
// pros::Rotation right_rot(-17);
pros::Imu imu(15);	// check this port

ASSET(underalt_txt);
ASSET(left_txt);

lemlib::Drivetrain drivetrain {
	&left_drive,
	&right_drive,
	17.37286228, // track width		11.71875
	lemlib::Omniwheel::NEW_4, // wheel diameter
	300, // wheel rpm
	2 // boomerang chase
};

lemlib::TrackingWheel left_tracking(
	&left_rot, // rotation sensor object
	2.744269794, // wheel diameter
	1.729921405, // tracking center offset (negative if to left of tracking center)
	1 // TRACKING WHEEL gear ratio
);

lemlib::TrackingWheel right_tracking(
	&left_rot, // rotation sensor object
	2.75, // wheel diameter
	2.890625, // tracking center offset (negative if to left of tracking center)
	1 // TRACKING WHEEL gear ratio
);

lemlib::OdomSensors odom_sensors {
	&left_tracking, // &left_tracking, // parallel tracking wheel left
	nullptr, // parallel tracking wheel right
	nullptr, // perpendicular tracking wheel 1
	nullptr, // perpendicular tracking wheel 2
	&imu // inertial sensor
};

// forward/backward PID
lemlib::ControllerSettings lateral_controller {
    11, // kP
	0, 	// kI
    40, // kD 80 pretty good
	0, 	// anti windup I
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    100 // slew rate
};
 
// turning PID
lemlib::ControllerSettings angular_controller {
    5, // kP
	0,
    20, // 40 kD
	0,
    1, // smallErrorRange		//1
    100, // smallErrorTimeout
    2, // largeErrorRange
    500, // largeErrorTimeout
    100 // slew rate		// 0
};

lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller, odom_sensors);

pros::ADIDigitalOut blocker('B'); // and descorer
pros::ADIDigitalOut left_wing('A');
pros::ADIDigitalOut vert_wing('C');

bool wings_deployed = false;
bool vert_deployed = false;
bool blocker_deployed = false;
bool puncher_on = false;

int cata_retract_length = 250*4.2;
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
	vert_wing.set_value(wings_deployed);
	blocker.set_value(blocker_deployed);

	chassis.calibrate();
	left_rot.set_data_rate(5);

	cata.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);

	cata.set_zero_position(0);

	left_drive.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
	right_drive.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);

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

void get_tracking_wheel_msmt() {
	left_drive.move(127);
	right_drive.move(-127);
	pros::delay(2000);
	left_drive.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
	right_drive.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
	double start_theta = imu.get_rotation();
	double start_enc = left_rot.get_position();
	double start_left = left_drive.get_positions()[1];
	double start_right = right_drive.get_positions()[1];

	pros::delay(8000);
	double end_theta = imu.get_rotation();
	double end_enc = left_rot.get_position();
	double end_left = left_drive.get_positions()[1];
	double end_right = right_drive.get_positions()[1];
	left_drive.move(0);
	right_drive.move(0);

	

	pros::lcd::print(3, "theta: %f", end_theta - start_theta);
	pros::lcd::print(4, "enc: %f", (end_enc - start_enc)/100);
	pros::lcd::print(5, "left: %f", end_left - start_left);
	pros::lcd::print(6, "right: %f", end_right - start_right);
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
	// chassis.moveToPoint(0, 24, 10000, 50);

	// chassis.turnTo(50, -50, 10000, false, 50);

	int start = pros::millis();
    
	sixball(&chassis);
	//spiral(&chassis);

	// get_tracking_wheel_msmt();

	
	pros::lcd::print(0, "Time: %d", pros::millis() - start);
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
	// chassis.moveToPoint(0, 10, 0, 1000, false, true, 0, 0.6, 127, true);

	// chassis.turnTo(30, 0, 10000);
	// chassis.moveToPoint(0, 48, 10000, 40, true);

	/*
	while (true) {
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
			break;
		}
	} */

	cata.move(0);

	// BEGIN SKILLS

	// chassis.setPose(0, 0, 0, 0);

    // Change angle to shoot
    // while (chassis.getPose().theta > -25) {
    //     left_drive.move(-40);
    // }
    // left_drive.move(0);

	// END SKILLS

	while (true) {
		lemlib::Pose pose = chassis.getPose();
		pros::lcd::print(0, "x: %f", pose.x);
		pros::lcd::print(1, "y: %f", pose.y);
		pros::lcd::print(2, "theta: %f", pose.theta);
		pros::lcd::print(3, "left rot: %ld", left_rot.get_position());
		
		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);

		left_drive.move(left);
		right_drive.move(right); // right

		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
			chassis.setPose(0, 0, 90);
			while (chassis.getPose().theta > 62) {
        		left_drive.move(-40);
				pros::lcd::print(2, "theta: %f", pose.theta);
				pros::delay(10);
    		}
    		left_drive.move(0);
		}

		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
			wings_deployed = !wings_deployed;
			left_wing.set_value(wings_deployed);
		}

		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
			vert_deployed = !vert_deployed;
			vert_wing.set_value(vert_deployed);
		}

		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
			blocker_deployed = !blocker_deployed;
			blocker.set_value(blocker_deployed);
		}

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			intake.move(127);
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			intake.move(-127);
		} else {
			intake.move(0);
		}

		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
			cata_retract_start = pros::millis();
		}
		
		if (pros::millis() - cata_retract_start < cata_retract_length) {
			cata.move(127 * .9);
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
			cata.move(127 * .9);
		} else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
			puncher_on = !puncher_on;
			if (puncher_on) {
				cata.move(127 * .9);
			} else {
				cata.move(0);
			}
		} else if (!puncher_on) {
			cata.move(0);
		}

		pros::delay(10);
	}
}
