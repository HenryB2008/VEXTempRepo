#include "includes.h"
#include <array>

Drive *drive = new Drive();
Pneumatics *fourbarpneum = new Pneumatics('G');
Effectors effectors;
Intake *intake = new Intake(5);
Intake *fourbar1 = new Intake(-1);
Intake *fourbar2 = new Intake(10);
Button *buttons = new Button();
pros::Imu imu(16);

double speeds[3] = {150, 150, 150};

PIDConst forwardDefault = {0.035, 0.00005, 0};
PIDConst headingDefault = {0, 0, 0};
PIDConst turnDefault = {0.02, 0.000025, 0};

int route;

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
	fourbar1->setLimits(2200, 0);
	fourbar2->setLimits(2200, 0);
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
		output = std::max(0.2, output);

    } else if (currOutput < 0){ // negative rawOutput case

        output = std::clamp(currOutput, std::max(-1.0, prevOutput - step), prevOutput + step); // clamped for slew and so finalOutput does not exceed -maxOutput
		output = std::min(-0.2, output);

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
		printf("Odom: %f %f %f\n", temp.x.convert(inch), temp.y.convert(inch), temp.theta.convert(degree));
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

void dragTurn(double heading, double direction, double side) {
	while(abs(heading-imu.get_heading())>4) {
		if(side == 0) {
			drive->runTank(0.5*direction, 0.1*direction*-1);
		}
		if(side == 1) {
			drive->runTank(0.1*direction*-1, 0.5*direction);
		}
		pros::delay(30);
	}
	drive->runTank(0, 0);
}

void autonSelector(okapi::Controller controller) {
	while(1) {
		if(controller.getDigital(okapi::ControllerDigital::A)) {
			route = 1;
			break;
		}
		if(controller.getDigital(okapi::ControllerDigital::B)) {
			route = 2;
			break;
		}
		if(controller.getDigital(okapi::ControllerDigital::X)) {
			route = 3;
			break;
		}
		if(controller.getDigital(okapi::ControllerDigital::Y)) {
			route = 4;
			break;
		}
	}
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
		intake->run(false, buttons->getPressed(okapi::ControllerDigital::right), 175);
		fourbar1->run(buttons->getPressed(okapi::ControllerDigital::R1), buttons->getPressed(okapi::ControllerDigital::R2), 175);
		fourbar2->run(buttons->getPressed(okapi::ControllerDigital::R1), buttons->getPressed(okapi::ControllerDigital::R2), 175);
		fourbarpneum->handle(buttonCounts[5]);
		//drive->reverseOrientation(buttonCounts[7]%2);
		pros::delay(30);
		pros::lcd::clear_line(2);
	}
}

void right() {
  setEffectorPositions();
	//pros::lcd::initialize();
	printf("done\n");
	//moveTank(x);
	effectors.runOne(GOAL_LIFT, 1);

	distanceMove(43, -1);	//move towards side neutral at full speed
	fourbarpneum->turnOn(); //clamp it
	pros::delay(300); //delay 300 ms
	printf("Finished\n");
	distanceMove(9, 1); //move back



	OdomState goal = drive->getState();  //
	goal.theta = 310_deg;  //turn backside towards alliance goal
	moveTank(goal, {0, 0, 0}, turnDefault, true);  //make the turn

	pros::delay(300);
	distanceMove(12, 1); //move towards alliance goal
	effectors.runOne(GOAL_LIFT, 0);
	fourbar1->moveTarget(500);
  	fourbar2->moveTarget(500);
	intake->run(true, false, -175); //start intake
	goal = drive->getState();
	goal.theta = 180_deg; //
	moveTank(goal, {0, 0, 0}, {0.01, 0.000005, 0}, true); //turn to dump goal
	fourbarpneum->turnOff(); //dump goal
	pros::delay(750); //wait
	intake->run(true, false, 0); //end intake
	fourbar1->moveTarget(0); //lower four bar
  	fourbar2->moveTarget(0); //lower four bar
	goal = drive->getState();
	goal.theta = 295_deg; 
	moveTank(goal, {0, 0, 0}, {0.01, 0.000005, 0}, true); //turn towards center goal
	pros::delay(200);
	distanceMove(54, -1); //move towards center goal
	fourbarpneum->turnOn(); //clamp
	pros::delay(300); //wait
	goal.theta = 315_deg;
	moveTank(goal, {0, 0, 0}, {0.02, 0.000005, 0}, true); //turn slightly to be able to get back into home zone
	distanceMove(40, 1); //move backwards into homezone


}

void skills() {
	setEffectorPositions();
	//pros::lcd::initialize();
	printf("done\n");
	//moveTank(x);
	effectors.runOne(GOAL_LIFT, 1);

	distanceMove(43, -1);
	fourbarpneum->turnOn();
	pros::delay(300);
	printf("Finished\n");
	distanceMove(9, 1);



	OdomState goal = drive->getState();
	goal.theta = 310_deg;
	moveTank(goal, {0, 0, 0}, turnDefault, true);

	pros::delay(1500);
	distanceMove(12, 1);
	effectors.runOne(GOAL_LIFT, 0);
	fourbar1->moveTarget(500);
  	fourbar2->moveTarget(500);
	intake->run(true, false, -175);
	goal = drive->getState();
	goal.theta = 180_deg;
	moveTank(goal, {0, 0, 0}, {0.01, 0.000005, 0}, true);
	fourbarpneum->turnOff();
	pros::delay(750);
	intake->run(true, false, 0);
	fourbar1->moveTarget(0);
  	fourbar2->moveTarget(0);
	goal = drive->getState();
	goal.theta = 295_deg;
	moveTank(goal, {0, 0, 0}, {0.01, 0.000005, 0}, true);
	distanceMove(54, -1);
	fourbarpneum->turnOn();
	pros::delay(500);
	distanceMove(54, 1);
	goal.theta = 220_deg;
	moveTank(goal, {0, 0, 0}, {0.01, 0.000005, 0}, true);
	fourbarpneum->turnOff();
	goal.theta = 295_deg;
	moveTank(goal, {0, 0, 0}, {0.01, 0.000005, 0}, true);
	distanceMove(72, 1);
}

void rightrings() {
	setEffectorPositions();
	fourbar1->moveTarget(500);
  	fourbar2->moveTarget(500);
	effectors.runOne(GOAL_LIFT, 1);
	pros::delay(1500);
	distanceMove(20, 1);
	effectors.runOne(GOAL_LIFT, 0);
	distanceMove(12, -1);
	intake->run(true, false, -175);
	while(1) {
		distanceMove(7, -0.5);
		pros::delay(500);
		distanceMove(7, 0.5);
	}


}

void left() {
	setEffectorPositions();
  effectors.runOne(GOAL_LIFT, 1); //lower goal lift
  fourbar1->moveTarget(500);
  fourbar2->moveTarget(500);
  pros::delay(2000);
  	speedMove(750, 0.5); // move forwards and get goal
	effectors.runOne(GOAL_LIFT, 0); // raise goal lift
	pros::delay(500);
	speedMove(500, -0.5); // forwards
	OdomState goal = drive->getState();
  goal.theta = 90_deg;
	//moveTank(goal, {0, 0, 0}, {0.01, 0.00001, 0}, true); // turn towards central mogo
	dragTurn(100, -1, 0);
   intake->run(true, false, -175);  //run intake to deposit rings
   pros::delay(500);
   intake->run(true, false, 0);
   fourbar1->moveTarget(0);
  fourbar2->moveTarget(0);
   distanceMove(46, -1);  //move towards

   fourbarpneum->turnOn();
	 pros::delay(300);
   distanceMove(46, 1);  //move towards
	//   intake->run(true, false, 0);  //stop intake

}

void leftmiddle() {
	setEffectorPositions();
	effectors.runOne(GOAL_LIFT, 1);
	fourbar1->moveTarget(500);
	fourbar2->moveTarget(500);
	pros::delay(2000);
  	speedMove(750, 0.5); // move forwards and get goal
	effectors.runOne(GOAL_LIFT, 0); // raise goal lift
	pros::delay(500);
	speedMove(500, -0.5); // forwards
	OdomState goal = drive->getState();
  	goal.theta = 90_deg;
}

void rightmiddle() {
	setEffectorPositions();
	OdomState goal = drive->getState();
	goal.theta = -27_deg;
	moveTank(goal, {0, 0, 0}, {0.03, 0.00003, 0}, true);
//	pros::delay(1000);
	speedMove(1400, 1);
	fourbarpneum->turnOn();
	goal.theta = -60_deg;
	moveTank(goal, {0, 0, 0}, {0.03, 0.00006, 0}, true);
	effectors.runOne(GOAL_LIFT, 1); //lower goal lift
	distanceMove(48, -0.5);
	effectors.runOne(GOAL_LIFT, 0); // raise goal lift
	pros::delay(1000);
	intake->run(true, false, 150);
	pros::delay(3000);
	intake->run(true, false, 0);
}

void leftWithLeft() {
	setEffectorPositions();
	effectors.runOne(GOAL_LIFT, 1); //lower goal lift
	pros::delay(2000);
	speedMove(1300, -0.5); // move forwards and get goal
	effectors.runOne(GOAL_LIFT, 0); // raise goal lift
	pros::delay(500);
	speedMove(1000, 0.5); // forwards
	OdomState goal = drive->getState();
	goal.theta = 105_deg;
	moveTank(goal, {0, 0, 0}, {0.016, 0.00002, 0}, true); // turn towards central mogo
   intake->run(true, false, 150);  //run intake to deposit rings
   speedMove(1400, 1);  //move towards

   fourbarpneum->turnOn();
	 pros::delay(300);
   speedMove(800, -1);  //move towards
}


void autonomous() {
	drive->setMode(okapi::AbstractMotor::brakeMode::hold);
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
	right();
	drive->setMode(okapi::AbstractMotor::brakeMode::coast);
}

void esbensOdom() {
	float x = 0;		//variables for tracking
	float y = 0;

	ADIEncoder righttrack = ADIEncoder('A', 'B', false);		//encoders because i don't know how to get values
	ADIEncoder lefttrack = ADIEncoder('C', 'D', true);

	righttrack.reset();	//reset encoders to zero
	lefttrack.reset();

	int lastright = 0;		//track the last position in the previous iteration
	int lastleft = 0;

	while (true) {
		int tempright = righttrack.get();		//get right and left values
		int templeft = lefttrack.get();
		double heading = imu.get_heading();
		x += ((tempright + templeft)/2/360*2.75*2*PI)*sin(heading);		//get average degrees, convert to inches and use sin or cos to get the change in x or y
		y += ((tempright + templeft)/2/360*2.75*2*PI)*cos(heading);

		lastright = tempright;		//update the last value
		lastleft = templeft;
		pros::c::lcd_print(0, "OdomX: %f\n", x);		//display on lcd screen
		pros::c::lcd_print(1, "OdomY: %f\n", y);
		pros::c::lcd_print(2, "OdomH: %d\n", heading);
		pros::delay(20);
	}
}
