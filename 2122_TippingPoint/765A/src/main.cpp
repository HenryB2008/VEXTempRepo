#include "includes.h"
#include <array>

Drive *drive = new Drive();
Pneumatics *fourbarpneum = new Pneumatics('H');
Pneumatics *auxilclamp = new Pneumatics('G');
Effectors effectors;
Intake *intake = new Intake(5);
Button *buttons = new Button();
pros::Imu imu(16);

double speeds[3] = {150, 150, 150};

PIDConst forwardDefault = {0.035, 0.00005, 0};
PIDConst headingDefault = {0, 0, 0};
PIDConst turnDefault = {0.03, 0.00006, 0};

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
	imu.reset();

	int time = pros::millis();
	int iter = 0;
	while (imu.is_calibrating())
	{
		printf("IMU calibrating... %d\n", iter);
		iter += 10;
		pros::delay(10);
	}

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
	double output;
	if(currOutput > 0){ // positive rawOutput case

        output = std::clamp(currOutput, prevOutput - step, std::min(1.0, prevOutput + step)); // clamped for slew and so finalOutput does not exceed maxOutput

    } else if (currOutput < 0){ // negative rawOutput case

        output = std::clamp(currOutput, std::max(-1.0, prevOutput - step), prevOutput + step); // clamped for slew and so finalOutput does not exceed -maxOutput

    } else { // rawOutput is 0

        output = 0; // step will return 0
    }
	return output;
}

void moveTank(OdomState target, PIDConst forwardConstants = forwardDefault, PIDConst turnConstants = headingDefault, bool turning = false) {
	double forward, turn, prevForward, prevTurn;
	QLength magerr;
	QAngle headerr;
	QAngle targetAngle;
	OdomState currState;
	QLength xDiff, yDiff;
	double currHeading;
	prevForward = 0;
	prevTurn = 0;
	PID forwardObj = PID(forwardConstants);
	PID turnObj = PID(turnConstants);

	printf("DONE\n");

	do {
		//currHeading = imu.get_heading();
		currState = drive->getState();
		xDiff = target.x-currState.x;
		yDiff = target.y-currState.y;
		if(!turning) {
			targetAngle = okapi::OdomMath::constrainAngle180((PI/2 - atan2(xDiff.convert(meter), yDiff.convert(meter)))*1_rad);
			targetAngle = 1_deg * targetAngle.convert(degree);
		}
		else {
			targetAngle = target.theta;
		}
		QAngle curr = okapi::OdomMath::constrainAngle180(imu.get_heading()*1_deg);
		headerr = okapi::OdomMath::constrainAngle180(curr-targetAngle);
		magerr = sqrt((xDiff * xDiff) + (yDiff * yDiff));

		//if overshoot point, reverse direction and target heading
		if(abs(headerr.convert(degree)) > 100 && forwardConstants.kp != 0) {
			headerr = okapi::OdomMath::constrainAngle180(headerr-180_deg);
			magerr*=-1;
		}

		//limit and set motors
		forward = limiter(prevForward, forwardObj.step(magerr.convert(inch)), 0.11);
		turn = limiter(prevTurn, turnObj.step(headerr.convert(degree)), 0.11);
		//pros::lcd::print(2, "%f", drive->getState().theta.convert(degree));
		//printf("Errors: %f %f %f %f\n", magerr.convert(inch), targetAngle.convert(degree), headerr.convert(degree), curr.convert(degree));
		printf("%f %f %f\n", drive->getX(), drive->getY(), drive->getHeading());
		//printf("forward: %f turn: %f\n", forward, turn);
		drive->runTankArcade(forward, turn);
		prevForward = forward;
		prevTurn = turn;
		pros::delay(30);
	} while((abs(magerr.convert(inch)) > 3 && !turning) || (abs(headerr.convert(degree))>3 && turning));
	drive->runTankArcade(0, 0);
}

void distanceMove(double distance, double speed) {
	OdomState initial = drive->getState();
	double error = 0;
	drive->runTankArcade(speed, 0);
	do {
		OdomState temp = drive->getState();
		QLength xdiff = temp.x-initial.x;
		QLength ydiff = temp.y-initial.y;

		error = okapi::sqrt((xdiff*xdiff) + (ydiff*ydiff)).convert(inch);
	} while(error<distance);
	drive->runTankArcade(0, 0);
}

void speedMove(double time, double speed) {

	double start = pros::millis();
	printf("%f\n", start);
	drive->runTankArcade(speed, 0);
	while(pros::millis()-start<time) {
		pros::delay(10);
	}
	double end = pros::millis();
	printf("%f\n", end);
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
	bool fourbarpneumstate = true;
	bool auxilclampstate = false;
	while(true) {
		forward = controller.getAnalog(okapi::ControllerAnalog::leftY);
		turn = controller.getAnalog(okapi::ControllerAnalog::rightX);
		//strafe = controller.getAnalog(okapi::ControllerAnalog::rightX);
		//printf("%f, %f", forward, turn);
		drive->runTankArcade(forward*-1, turn*-1);
		printf("%f %f %f\n", drive->getX(), drive->getY(), drive->getHeading());

		buttons->handleButtons(controller);
			//printf("%d\n", buttons->getCount(x));
		int buttonCounts[8];
		for(int i = 0; i < 8; i++) {
			buttonCounts[i] = buttons->getCount(buttons->buttonList[i]);
		}
    //printf("%d", buttonCounts[7]%2);
    //printf("\n");
		effectors.step(buttonCounts, speeds);
		intake->run(buttons->getPressed(okapi::ControllerDigital::R1), buttons->getPressed(okapi::ControllerDigital::L1), 150);
		fourbarpneum->handle(buttonCounts[5]);
		auxilclamp->handle(buttonCounts[6]);
		//drive->reverseOrientation(buttonCounts[7]%2);
		pros::delay(30);
		pros::lcd::clear_line(2);
	}
}

void right() {
  setEffectorPositions();
	//pros::lcd::initialize();
	OdomState x = {24_in, 0_in, 0_deg};
	OdomState y = {0_in, 0_in, 0_deg};
	OdomState z = {0_in, 0_in, -90_deg};
	/*
	lift->setTarget(250);
	lift->stepAbsolute(50);
	lift->setTarget(250);
	lift->stepAbsolute(-50);
	*/
	printf("done\n");
	//moveTank(x);
	speedMove(1500, 1);
	//fourbarpneum->turnOn();
	pros::delay(300);
	printf("Finished\n");
	//speedMove(500, -1);

	OdomState goal = drive->getState();
	goal.theta = 0_deg;
	//moveTank(y);
	moveTank(goal, {0, 0, 0}, turnDefault, true);

	goal = drive->getState();
	goal.x = 17_in;
	moveTank(goal);

	goal = drive->getState();
	goal.theta = 90_deg;
	//moveTank(y);
	moveTank(goal, {0, 0, 0}, turnDefault, true);
  speedMove(700, 0.5);
  effectors.runOne(GOAL_LIFT, 1);
  pros::delay(2000);
  goal = drive->getState();
  goal.y = -18_in;
  speedMove(1500, -0.5);
  effectors.runOne(GOAL_LIFT, 0);
  pros::delay(1500);
  intake->run(true, false, 150);
  pros::delay(10000);
  intake->run(true, false, 0);
	printf("%f %f %f", drive->getState().x.convert(inch), drive->getState().y.convert(inch), drive->getState().theta.convert(degree));
}

void left() {
  setEffectorPositions();
  OdomState goal = drive->getState();
  goal.theta = 90_deg;
  moveTank(goal, {0, 0, 0}, turnDefault, true); // turn left
  speedMove(500, 0.5);	//backwards
  effectors.runOne(GOAL_LIFT, 1); //lower goal lift
  pros::delay(2000);
  speedMove(1300, -0.5); // move forwards and get goal
	effectors.runOne(GOAL_LIFT, 0); // raise goal lift
	pros::delay(500);
	speedMove(1000, 0.5); // forwards
	goal = drive->getState();
  goal.theta = 325_deg;
	moveTank(goal, {0, 0, 0}, turnDefault, true); // turn towards central mogo
   intake->run(true, false, 150);  //run intake to deposit rings
   speedMove(2500, 1);  //move towards
   fourbarpneum->turnOn();
   speedMove(2500, -1);  //move towards
	//   intake->run(true, false, 0);  //stop intake

}

void rightmiddle() {
	setEffectorPositions();
	speedMove(500, 1);
	OdomState goal = drive->getState();
	goal.theta = -90_deg;
	moveTank(goal, {0, 0, 0}, turnDefault, true);
	pros::delay(1000);
	double currHeading = 90-imu.get_heading();
	QLength x = abs(cos(currHeading))*30_in;
	QLength y = abs(sin(currHeading))*30_in;
	goal = drive->getState();
	goal.y = goal.y-x;
	goal.x = goal.x-y;
	moveTank(goal, forwardDefault, headingDefault);

}



void autonomous() {
	/*
	std::vector<point> points;
	points.push_back({0, 0, 0, 0, 0});
	points.push_back({0, 24, 0, 0, 0});
	points.push_back({-15, 40, 0, 0, 0});
	PurePursuitPathGen path = PurePursuitPathGen(3, 0.25, 0.75,0.001, points,10.0, 10.0, 2);
	path.interpolate();
  path.smooth();
  path.calc_distances();
	path.calc_curvature();
	path.calc_velocities();
	path.print_path();
	PurePursuitFollower follow = PurePursuitFollower(8);
	follow.read(path);
	std::array<double, 4> vels = {0, 0, 0, 0};
	double x, y, theta;
	do {
		theta = 90-imu.get_heading();
		x = drive->getX();
		y = drive->getY();
		vels = follow.follow(y, x, theta);
		printf("POS: %f %f %f\n", y, x, theta);
		printf("%f %f %f %f\n", vels[0], vels[1], vels[2], vels[3]);
		drive->runTankArcade(vels[0], vels[1]);
		pros::delay(30);

	} while(vels[0] != 0 && vels[1] != 0 &&vels[2] != 0 &&vels[3] != 0);
	drive->runTank(0, 0);
*/
	rightmiddle();
}
