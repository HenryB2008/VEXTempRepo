#include "main.h"
#include "pid.h"
#include "drive.h"
#include "pneumatics.h"
#include "button.h"
#include "intake.h"
#include "effectors.h"

Drive *drive = new Drive();
Pneumatics *pneum = new Pneumatics('F');
Effectors effectors;
Intake *intake = new Intake(5);
Button *buttons = new Button();

double speeds[3] = {150, 150, 150};


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

OdomState transform(OdomState curr, OdomState target) {
	OdomState diff;
	diff.x = target.x - curr.x;
	diff.y = target.y - curr.y;
	diff.theta = OdomMath::constrainAngle180(target.theta-curr.theta);


	//rotate vector
	diff.x = diff.y * sin(curr.theta.convert(radian)) + diff.x*cos(curr.theta.convert(radian));
	diff.y = diff.y*cos(curr.theta.convert(radian)) - diff.x*sin(curr.theta.convert(radian));

	return diff;
}

double limiter(double prevOutput, double currOutput, double step) {
	double output = std::clamp(currOutput, prevOutput-step, prevOutput+step);
	if(abs(output) < 0.05) {
		return 0;
	}
	return output;
}

void move(OdomState target) {
	double xOutput, yOutput, turnOutput;
	double prevX, prevY, prevTurn;
	prevX = 0;
	prevY = 0;
  prevTurn = 0;
	PID x = PID(0.1, 0, 0);
	PID y = PID(0.1, 1, 0);
	PID turn = PID(0.01, 0, 0);
	do {
		OdomState diff = transform(drive->getState(), target);
		xOutput = limiter(prevX, x.step(diff.x.convert(inch)), 0.1);
		yOutput = limiter(prevY, y.step(diff.y.convert(inch)), 0.1);
		turnOutput = limiter(prevTurn, turn.step(diff.theta.convert(degree)), 0.1);

		drive->run(xOutput, yOutput, turnOutput);
		prevX = xOutput;
		prevY = yOutput;
		prevTurn = turnOutput;
	} while(abs(xOutput) >0 || abs(yOutput) >0 || abs(turnOutput) >0);
	drive->run(0, 0, 0);
	printf("Done");
}

void moveTank(OdomState target) {
	double forward, turn, prevForward, prevTurn;
	QLength magerr;
	QAngle headerr;
	QAngle targetAngle;
	OdomState currState;
	QLength xDiff, yDiff;
	prevForward = 0;
	prevTurn = 0;
	PID forwardObj = PID(0.05, 0, 0);
	PID turnObj = PID(0.005, 0, 0);

	do {
		currState = drive->getState();
		xDiff = target.x-currState.x;
		yDiff = target.y-currState.y;
		targetAngle = 90_deg - okapi::atan2(xDiff, yDiff);
		headerr = targetAngle-drive->getState().theta;
		magerr = sqrt((xDiff * xDiff) + (yDiff * yDiff));

		//if overshoot point, reverse direction and target heading
		if(abs(headerr.convert(degree)) > 100) {
			headerr = okapi::OdomMath::constrainAngle180(headerr-180_deg);
			magerr*=-1;
		}

		//limit and set motors
		forward = limiter(prevForward, forwardObj.step(magerr.convert(inch)), 0.08);
		turn = limiter(prevTurn, turnObj.step(headerr.convert(degree)), 0.08);
		printf("forward: %f turn: %f\n",  forward, turn);
		drive->runTankArcade(forward, turn);
		prevForward = forward;
		prevTurn = turn;
	} while(abs(forward) > 0 || abs(turn) > 0);
	drive->runTankArcade(0, 0);
}

void setEffectorPositions() {

	effectors.addPosition();
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

	okapi::Controller controller (okapi::ControllerId::master);

	setEffectorPositions();

	double forward;
	double turn;
	double strafe;
	int i = 0;

	while(true) {
		forward = controller.getAnalog(okapi::ControllerAnalog::rightY);
		turn = controller.getAnalog(okapi::ControllerAnalog::leftX);
		//strafe = controller.getAnalog(okapi::ControllerAnalog::rightX);
		//printf("%f, %f", forward, turn);
		drive->runTankArcade(forward, turn);
		printf("%f %f %f\n", drive->getX(), drive->getY(), drive->getHeading());
		
		buttons->handleButtons(controller);
			//printf("%d\n", buttons->getCount(x));
		int buttonCounts[3];
		for(int i = 0; i < 3; i++) {
			buttonCounts[i] = buttons->getCount(buttons->buttonList[i]);
		}
		effectors.step(buttonCounts, speeds);
		intake->run(buttons->getPressed(okapi::ControllerDigital::L1), buttons->getPressed(okapi::ControllerDigital::R1), 200);
		
		pros::delay(10);

	}
}


void autonomous() {
	OdomState x = {24_in, 0_in, 0_deg};
	/*
	lift->setTarget(250);
	lift->stepAbsolute(50);
	lift->setTarget(250);
	lift->stepAbsolute(-50);
	*/
	printf("done\n");
	moveTank(x);
}
