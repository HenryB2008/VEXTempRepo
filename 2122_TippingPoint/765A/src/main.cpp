#include "includes.h"
#include <array>


//subsystem objects
Drive *drive = new Drive();
Pneumatics *fourbarpneum = new Pneumatics(FRONT_PNEUM);
Pneumatics *backclamppneum = new Pneumatics(BACK_PNEUM);
Effectors effectors;
Intake *intake = new Intake(INTAKE_PORT);
Intake *fourbar1 = new Intake(FOUR_BAR_FIRST);
Intake *fourbar2 = new Intake(FOUR_BAR_FIRST);
Button *buttons = new Button();
pros::Imu imu(IMUPORT);
pros::ADIDigitalIn but('H');
okapi::Controller controller (okapi::ControllerId::master);

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

void autonSelector() {
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
		pros::delay(15);
	}
}


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */


void initialize() {
	//make sure four bar can't go higher/lower than the mechanical stops
	fourbar1->setLimits(2400, 0);
	fourbar2->setLimits(2400, 0);

	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	//autonSelector();

	//calibrate imu
	imu.reset();

	int time = pros::millis();
	int iter = 0;
	while (imu.is_calibrating())
	{
		printf("IMU calibrating... %d\n", iter);
		iter += 10;
		pros::delay(10);
	}
	imu.set_data_rate(10);
	pros::lcd::register_btn1_cb(on_center_button);
}

//x-drive math to find difference between two odomstates
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


//slew limiter for PID
double limiter(double prevOutput, double currOutput, double step) {
	double output;
	if(currOutput > 0){ // positive rawOutput case

        output = std::clamp(currOutput, prevOutput - step, std::min(1.0, prevOutput + step)); // clamped for slew and so finalOutput does not exceed maxOutput
		output = std::max(0.2, output); //make sure output above min power

    } else if (currOutput < 0){ // negative rawOutput case

        output = std::clamp(currOutput, std::max(-1.0, prevOutput - step), prevOutput + step); // clamped for slew and so finalOutput does not exceed -maxOutput
		output = std::min(-0.2, output); //make sure output above min power

    } else { // rawOutput is 0

        output = 0; // step will return 0
    }
	return output;
}


//overhauled move function
void pidMoveForward(OdomState target, PIDConst forwardConstants, PIDConst headingConstants, double timeout = 5) {
	double forward, turn, prevForward, prevTurn;
	QLength magerr;
	QAngle headerr;
	QAngle targetAngle;
	OdomState currState;
	QLength xDiff, yDiff;
	prevForward = 0;
	prevTurn = 0;

	PID forwardObj = PID(forwardConstants);
	PID turnObj = PID(headingConstants);

	double startTime = pros::millis();
	do {
		currState = drive->getState();
		xDiff = target.x-currState.x;
		yDiff = target.y-currState.y;

		targetAngle = okapi::OdomMath::constrainAngle180((PI/2 - atan2(xDiff.convert(meter), yDiff.convert(meter)))*1_rad);
		targetAngle = 1_deg * targetAngle.convert(degree);

		//calculate errors
		QAngle curr = okapi::OdomMath::constrainAngle180(imu.get_heading()*1_deg);
		headerr = okapi::OdomMath::constrainAngle180(curr-targetAngle);
		magerr = sqrt((xDiff * xDiff) + (yDiff * yDiff));

		if(abs(magerr.convert(inch))<10) {
			headerr = 0_deg;
		}

		//if overshoot point, reverse direction and target heading
		if(abs(headerr.convert(degree)) > 100) {
			headerr = okapi::OdomMath::constrainAngle180(headerr-180_deg);
			magerr*=-1;
		}

		//limit and set motors
		forward = limiter(prevForward, forwardObj.step(magerr.convert(inch)), 0.11);
		turn = limiter(prevTurn, turnObj.step(headerr.convert(degree)), 0.11);
		printf("%f %f %f\n", drive->getX(), drive->getY(), drive->getHeading());
		drive->runTankArcade(forward, turn);
		prevForward = forward;
		prevTurn = turn;
		pros::delay(10);
	} while((abs(magerr.convert(inch)) > 2) && pros::millis()-startTime > (timeout*1000) ); //timeout and check mag err
	drive->runTankArcade(0, 0);
}

//overhauled turn function
void pidTurn(QAngle targetHeading, PIDConst turnConstants, double timeout = 3) {
	double turn, prevTurn;
	QAngle headerr;
	QAngle targetAngle;
	OdomState currState;
	QLength xDiff, yDiff;
	prevTurn = 0;

	targetAngle = targetHeading;

	PID turnObj = PID(turnConstants);
	do {
		currState = drive->getState();


		//calculate errors
		QAngle curr = okapi::OdomMath::constrainAngle180(imu.get_heading()*1_deg);
		headerr = okapi::OdomMath::constrainAngle180(curr-targetAngle);


		//limit and set motors
		turn = limiter(prevTurn, turnObj.step(headerr.convert(degree)), 0.11);
		printf("%f %f %f %f\n", drive->getX(), drive->getY(), drive->getHeading(), abs(headerr.convert(degree))>3);
		drive->runTankArcade(0, turn);
		prevTurn = turn;
		pros::delay(10);
	} while(abs(headerr.convert(degree))>3);
	drive->runTankArcade(0, 0);
}

//move to any point
void moveToPoint(OdomState target, PIDConst forwardConstants, PIDConst headingConstants, PIDConst turnConstants, double timeoutforward = 5, double timeoutturn = 3) {
	OdomState currState = drive->getState();
	QLength xDiff = target.x-currState.x;
	QLength yDiff = target.y-currState.y;

	QAngle targetAngle = okapi::OdomMath::constrainAngle180((PI/2 - atan2(xDiff.convert(meter), yDiff.convert(meter)))*1_rad);
	targetAngle = 1_deg * targetAngle.convert(degree);

	pidTurn(targetAngle, turnConstants, timeoutturn);
	printf("Done turning");
	pidMoveForward(target, forwardConstants, headingConstants, timeoutforward);
}

//PID move function that can handle turns and forward movements
void pidMoveTank(OdomState target, PIDConst forwardConstants = forwardDefault, PIDConst turnConstants = headingDefault, bool turning = false) {
	double forward, turn, prevForward, prevTurn;
	QLength magerr;
	QAngle headerr;
	QAngle targetAngle;
	OdomState currState;
	QLength xDiff, yDiff;
	prevForward = 0;
	prevTurn = 0;

	//forward and turn objects for PID
	PID forwardObj = PID(forwardConstants);
	PID turnObj = PID(turnConstants);

	do {
		currState = drive->getState();
		xDiff = target.x-currState.x;
		yDiff = target.y-currState.y;

		//calculate target thetas differently depending on forward or turn
		if(!turning) {
			targetAngle = okapi::OdomMath::constrainAngle180((PI/2 - atan2(xDiff.convert(meter), yDiff.convert(meter)))*1_rad);
			targetAngle = 1_deg * targetAngle.convert(degree);
		}
		else {
			targetAngle = target.theta;
		}

		//calculate errors
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
		printf("%f %f %f\n", drive->getX(), drive->getY(), drive->getHeading());
		drive->runTankArcade(forward, turn);
		prevForward = forward;
		prevTurn = turn;
		pros::delay(10);
	} while((abs(magerr.convert(inch)) > 3 && !turning) || (abs(headerr.convert(degree))>3 && turning)); //tolerances checked differently depending on turning or forward
	drive->runTankArcade(0, 0);
}


//use odometry magnitude error to move a set distance
void distanceMove(double distance, double speed) {
	OdomState initial = drive->getState();
	double error = 0;
	// double start = drive->getEncoder();
	drive->runTankArcade(speed, 0);
	double start = pros::millis();
	do {
		OdomState temp = drive->getState();
		QLength xdiff = temp.x-initial.x;
		QLength ydiff = temp.y-initial.y;
		printf("Odom: %f %f %f\n", temp.x.convert(inch), temp.y.convert(inch), temp.theta.convert(degree));
		//  error = ((drive->getEncoder() - start) / 360*(7.0/5)) * 4 * PI ;
		error = okapi::sqrt((xdiff*xdiff) + (ydiff*ydiff)).convert(inch);
		pros::delay(30);
	} while(error<distance && pros::millis()-start<6000);
	drive->runTankArcade(0, 0);
}

void distancePID(double distance, PIDConst gains) {
	OdomState initial = drive->getState();
	double error = 0;
	double speed = 0;
	double prevSpeed = 0;
	PID obj = PID(gains);
	do {
		OdomState temp = drive->getState();
		QLength xdiff = temp.x-initial.x;
		QLength ydiff = temp.y-initial.y;
		printf("Odom: %f %f %f\n", temp.x.convert(inch), temp.y.convert(inch), temp.theta.convert(degree));
		error = okapi::sqrt((xdiff*xdiff) + (ydiff*ydiff)).convert(inch);
		speed = limiter(prevSpeed, obj.step(distance>0 ? distance-error: distance+error), 0.11);
		prevSpeed = speed;
		drive->runTankArcade(speed, 0);
		pros::delay(30);
	} while(error<abs(distance));
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
	//set all effector positions
	effectors.addPosition();
}

void turnTest() {
	OdomState goal = drive->getState();
  while(1) {
  	goal.theta = 90_deg;
  	pidMoveTank(goal, {0, 0, 0}, {0.007, 0.000005, 0}, true);
  	pros::delay(1000);
  	goal = drive->getState();
  	goal.theta = 180_deg;
  	pidMoveTank(goal, {0, 0, 0}, {0.007, 0.000005, 0}, true);
  	pros::delay(1000);
  	goal = drive->getState();
  	goal.theta = 270_deg;
  	pidMoveTank(goal, {0, 0, 0}, {0.007, 0.000005, 0}, true);
  }
}


//drag turn function
void dragTurn(double heading, double direction, double side) {
	while(abs(heading-imu.get_heading())>2) {
		//handle side and direction logic
		if(side == 0) {
			drive->runTank(0.5*direction, 0.1*direction*-1);
		}
		if(side == 1) {
			drive->runTank(0.1*direction*-1, 0.5*direction);
		}
		pros::delay(10);
	}
	drive->runTank(0, 0);
}


//experimental autonSelector function


void autobalancer(double tolerance) {
	drive->runTankArcade(-1, 0);
	pros::delay(2000);
	double curr_pitch = imu.get_pitch();
	double last_pitch = curr_pitch;
	while(curr_pitch > tolerance || curr_pitch-last_pitch>=0) {
		pros::delay(5);
		printf("Current pitch: %f\n", curr_pitch);
		last_pitch = curr_pitch;
		curr_pitch = imu.get_pitch();
	}
	drive->runTankArcade(0, 0);
	drive->setMode(okapi::AbstractMotor::brakeMode::hold);
	pros::delay(10000);
}

void testBalancing() {
	setEffectorPositions();

	fourbarpneum->turnOn();
	fourbar1->moveTarget(2400);
	fourbar2->moveTarget(2400);
	pros::delay(2000);
	fourbar1->moveTarget(0);
	fourbar2->moveTarget(0);

	pros::delay(2000);
	autobalancer(22);
}

void moveUntilButton(double speed) {
	drive->runTankArcade(speed, 0);
	while(!but.get_value()) {
		pros::delay(10);
	}
	drive->runTankArcade(0, 0);
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

 void driverMovementTrack() {
 	//initialize variables and set effector positions
 	setEffectorPositions();
 	int parking = 0;
 	double forward;
 	double turn;
 	double strafe;
 	int i = 0;
 	bool fourbarpneumstate = true;
 	bool backclampstate = false;
 	ADIEncoder righttrack = ADIEncoder('A', 'B', false);		//encoders because i don't know how to get values
 	ADIEncoder lefttrack = ADIEncoder('C', 'D', true);
 	righttrack.reset();
 	lefttrack.reset();
 	okapi::Motor fourbar(FOUR_BAR_FIRST);

   	double max = 1;
   	drive->setMode(okapi::AbstractMotor::brakeMode::hold);
 	fourbarpneum->turnOn();
 	backclamppneum->turnOff();
 	while(true) {
 		//toggle between coast and hold brake modes
 		//get controller and drive chassis base
 		// printf("%f %f\n", righttrack.get(), lefttrack.get());
 		// printf("%f %f %d\n", drive->getX(), drive->getY(), (int)drive->getHeading()%360);
 		//update all button values
 		buttons->handleButtons(controller);
 		int buttonCounts[9];
 		for(int i = 0; i < 9; i++) {
 			buttonCounts[i] = buttons->getCount(buttons->buttonList[i]);
 		}

     	if(buttonCounts[7]%2) {
       		max = 5.0/7;
 			drive->setMode(okapi::AbstractMotor::brakeMode::hold);
     	}
     	else {
       		max = 1;
 			drive->setMode(okapi::AbstractMotor::brakeMode::coast);
     	}

     	forward = controller.getAnalog(okapi::ControllerAnalog::leftY);
 		turn = controller.getAnalog(okapi::ControllerAnalog::rightX);
     	if(forward>=0) {
 		    drive->runTankArcade(std::max(forward*-(6.0/7), max*-1), turn*-0.6);
     	}
     	else {
         	drive->runTankArcade(std::min(forward*-(6.0/7), max), turn*-0.6);
     	}

 		// effectors.step(buttonCounts, speeds); //handle two bar

 		//intake->run(false, buttons->getPressed(okapi::ControllerDigital::right), 150); //handle intake
 		//runs the intake backwards
 		if (buttonCounts[8]%2 == 1) {
 			intake->handle(buttonCounts[8], -180);
 		}
 		else {
 			intake->handle(buttonCounts[3], 180); //handle intake (toggle)
 		}

 		//handle four bar
 		fourbar1->run(buttons->getPressed(okapi::ControllerDigital::R1), buttons->getPressed(okapi::ControllerDigital::R2), 175);
 		//fourbar2->run(buttons->getPressed(okapi::ControllerDigital::R1), buttons->getPressed(okapi::ControllerDigital::R2), 175);

 		//handle clamp
 		fourbarpneum->handle(buttonCounts[5]);
 		backclamppneum->handle(buttonCounts[0]);
 		// parking = buttonCounts[7] % 2;
 		// if (parking == 1) {
 		// 	drive->setMode(okapi::AbstractMotor::brakeMode::hold);
 		// } else {
 		// 	drive->setMode(okapi::AbstractMotor::brakeMode::coast);
 		// }
 		//printf("%d\n", parking);

 		if (buttonCounts[1]%2) {
 			printf("Heading: %f    Distance from last point: %f inches     Four Bar position: %f\n\n", imu.get_heading(), ((righttrack.get() + lefttrack.get())/2 * 2.81665 * PI / 360), fourbar.getEncoder());
 			righttrack.reset();
 			lefttrack.reset();
 		}

 		pros::delay(60);
 		pros::lcd::clear_line(2);
 	}
 }

void opcontrol() {



	//initialize variables and set effector positions
	setEffectorPositions();
	int parking = 0;
	double forward;
	double turn;
	double strafe;
	int i = 0;
	bool fourbarpneumstate = true;
	bool auxilclampstate = false;
	ADIEncoder righttrack = ADIEncoder('A', 'B', false);		//encoders because i don't know how to get values
	ADIEncoder lefttrack = ADIEncoder('C', 'D', true);

  double max = 1;
  drive->setMode(okapi::AbstractMotor::brakeMode::hold);
	while(true) {
		//toggle between coast and hold brake modes
		//get controller and drive chassis base
		printf("%f %f\n", righttrack.get(), lefttrack.get());
		// printf("%f %f %d\n", drive->getX(), drive->getY(), (int)drive->getHeading()%360);
		//update all button values
		buttons->handleButtons(controller);
		int buttonCounts[9];
		for(int i = 0; i < 9; i++) {
			buttonCounts[i] = buttons->getCount(buttons->buttonList[i]);
		}

    if(buttonCounts[7]%2) {
      max = 5.0/7;
    }
    else {
      max = 1;
    }

    forward = controller.getAnalog(okapi::ControllerAnalog::leftY);
		turn = controller.getAnalog(okapi::ControllerAnalog::rightX);
    if(forward>=0) {
		    drive->runTankArcade(std::max(forward*-(6.0/7), max*-1), turn*-0.6);
    }
    else {
        drive->runTankArcade(std::min(forward*-(6.0/7), max), turn*-0.6);
    }

		// effectors.step(buttonCounts, speeds); //handle two bar

		//intake->run(false, buttons->getPressed(okapi::ControllerDigital::right), 150); //handle intake
		if (buttonCounts[8]%2 == 1) {
			intake->handle(buttonCounts[8], -200);
		}
		else {
			intake->handle(buttonCounts[3], 200); //handle intake (toggle)
		}

		//handle four bar
		fourbar1->run(buttons->getPressed(okapi::ControllerDigital::R1), buttons->getPressed(okapi::ControllerDigital::R2), 175);
		//fourbar2->run(buttons->getPressed(okapi::ControllerDigital::R1), buttons->getPressed(okapi::ControllerDigital::R2), 175);

		//handle clamp
		fourbarpneum->handle(buttonCounts[5]);
		backclamppneum->handle(buttonCounts[0]);
		parking = buttonCounts[7] % 2;
		if (parking == 1) {
			drive->setMode(okapi::AbstractMotor::brakeMode::hold);
		} else {
			drive->setMode(okapi::AbstractMotor::brakeMode::coast);
		}
		//printf("%d\n", parking);
		pros::delay(60);
		pros::lcd::clear_line(2);
	}
}

void right() {
  setEffectorPositions();
	printf("done\n");
	distanceMove(39, -1);	//move towards side neutral at full speed
	fourbarpneum->turnOn(); //clamp it
	pros::delay(100);
	printf("Finished\n");
	distanceMove(10, 1); //move back
	distanceMove(4, 0.6);


	pidTurn(270_deg, {0.01, 0.000008, 0});  //make the turn

	drive->runTankArcade(0.5, 0); //move towards alliance goal
	pros::delay(1400);
	backclamppneum->turnOn();
	drive->runTankArcade(-0.5, 0);
	pros::delay(1000);
	drive->runTankArcade(0, 0);
	intake->run(true, false, -180);



}

void leftfast() {
	setEffectorPositions();

	distanceMove(42, -1);	//move towards side neutral at full speed
	fourbarpneum->turnOn(); //clamp it
	printf("Finished\n");
	distanceMove(30, 1); //move back
}

void thenewnewskills() {

	//first alliance pickup
	setEffectorPositions();
	distanceMove(10, -0.5);
	pidTurn(270_deg, {0.007, 0.000008, 0});
	drive->runTankArcade(0.5, 0);
	pros::delay(1000);
	backclamppneum->turnOn();
	pidTurn(270_deg, {0.007, 0.000008, 0});
	drive->runTankArcade(0, 0);
	distanceMove(15, -0.5);
	// drive->runTankArcade(0, 0);
	intake->run(true, false, -180); //start intake
	pidTurn(0_deg, {0.007, 0.000008, 0});


	//first neutral and to goal
	// distanceMove(15, -0.8);
	// distancePID(-15, {0.01, 0.0000008, 0});
	// pidTurn(0_deg, {0.006, 0.000008, 0});
	distanceMove(34, -0.6);
	fourbarpneum->turnOn(); //clamp
	pros::delay(100);
	fourbar1->moveTarget(2400);
	pidTurn(331_deg, {0.020, 0.000009, 0}); //turn to seesaw
	distanceMove(51, -0.3); //move to seesaw
	// distancePID(-27, {0.01, 0.0000008, 0});
	pros::delay(300);
	fourbar1->moveTarget(1900);
	pros::delay(500);
	fourbarpneum->turnOff();
	pros::delay(200);
	// fourbar1->moveTarget(2400);

	//alliance currently in two bar
	distanceMove(18, 0.4);
	fourbar1->moveTarget(0);
	backclamppneum->turnOff();
	//move forwards and turn 180
	pros::delay(1000);
	distanceMove(9, -0.4);
	double curr = imu.get_heading();
	pidTurn((curr+175) * 1_deg, {0.005, 0.000008, 0});
	//move forwards and clamp on goal
	distanceMove(20, -0.4);
	fourbarpneum->turnOn();
	pros::delay(100);
	//raise four bar
	fourbar1->moveTarget(2100);
	//turn back towards seesaw
	pidTurn(345_deg, {0.006, 0.000008, 0});
	//forward to seesaw
	distanceMove(30, -0.6);
	//drop goal
	fourbar1->moveTarget(1900);
	pros::delay(700);
	fourbarpneum->turnOff();
	pros::delay(200);

	//alliance under first seesaw
	printf("Moving back\n");
	distanceMove(12, 0.4); //move back from seesaw
	fourbar1->moveTarget(0); //lower four bar
	pidTurn(272_deg, {0.009, 0.000008, 0}); //turn to the wall
	//distanceMove(33, 0.4); //forward
	drive->runTankArcade(0.4, 0); //run into wall
	pros::delay(3500);
	drive->runTankArcade(0, 0);
	distanceMove(1, -0.5);
	pidTurn(318_deg, {0.011, 0.000008, 0}); //turn towards goal under seesaw
	distanceMove(31, -0.4); //forwards to that goal
	fourbarpneum->turnOn(); //clamp
	pros::delay(200);
	distanceMove(20, 0.4); //get back out
	fourbar1->moveTarget(2400); //raise four bar
	pidTurn(226_deg, {0.010, 0.00001, 0}); //turn towards other side seesaw
	distanceMove(84, -0.6); //beeline there
	pros::delay(400);
	fourbar1->moveTarget(1400); //lower four bar
	pros::delay(1000);
	fourbarpneum->turnOff(); //drop clamp

	fourbar1->moveTarget(2400); //raise four bar

	//tall neutral
	distanceMove(13, 0.6);//back from seesaw
	fourbar1->moveTarget(0);
	pidTurn(305_deg, {0.014, 0.000008, 0}); //turn towards tall neutral
	distanceMove(30, -0.6); //beeline to tall
	fourbarpneum->turnOn();
	pros::delay(400);
	fourbar1->moveTarget(300);
	distanceMove(50, -0.6); //beeline to tall
	fourbarpneum->turnOff(); // drop tall
	pros::delay(500);
	distanceMove(9, 0.6);

	//side alliance with back clamp
	pidTurn(89_deg, {0.006, 0.000008, 0}); //turn towards side alliance
	drive->runTankArcade(0.5, 0);
	pros::delay(1700);
	backclamppneum->turnOn();
	drive->runTankArcade(0, 0);
	distanceMove(15, -0.5);
	fourbar1->moveTarget(0);
	pidTurn(180_deg, {0.007, 0.000008, 0});

	//last neutral goal
	distanceMove(38, -0.8);
	fourbarpneum->turnOn(); //clamp
	pros::delay(100);
	fourbar1->moveTarget(2400);
	pidTurn(146_deg, {0.01, 0.000009, 0}); //turn to seesaw
	distanceMove(40, -0.5); //move to seesaw
	pros::delay(300);
	fourbar1->moveTarget(2100);//drop four bar
	pros::delay(500);
	fourbarpneum->turnOff(); //drop neutral goal
	pros::delay(200);
	fourbar1->moveTarget(2400); //four bar back up

	//deposit alliance on seesaw
	distanceMove(18, 0.4); // away from seesaw
	fourbar1->moveTarget(0);//lower four bar
	backclamppneum->turnOff(); //let go of alliance goal
	//move forwards and turn 180
	distanceMove(8, -0.4); //go forward to lose the goal
	curr = imu.get_heading();
	pidTurn((curr+170)*1_deg, {0.008, 0.000008, 0}); //turn back towards the goal
	distanceMove(13, -0.4);	//move forwards and clamp on goal
	fourbarpneum->turnOn();
	pros::delay(100);
	//raise four bar
	fourbar1->moveTarget(2100);
	//turn back towards seesaw
	pidTurn(155_deg, {0.009, 0.000008, 0});
	//forward to seesaw
	distanceMove(40, -0.6);
	//drop goal
	fourbarpneum->turnOff();
	distanceMove(15, 0.6);
	pros::delay(200);
}

void skills() {
	setEffectorPositions();
	printf("done\n");
	effectors.runOne(GOAL_LIFT, 1); //lower two-bar

	distanceMove(43, -1);	//move towards side neutral at full speed
	fourbarpneum->turnOn(); //clamp it
	pros::delay(300); //delay 300 ms
	printf("Finished\n");
	distanceMove(9, 1); //move back



	OdomState goal = drive->getState();
	goal.theta = 310_deg;  //turn backside towards alliance goal
	pidMoveTank(goal, {0, 0, 0}, turnDefault, true);  //make the turn

	pros::delay(300);
	distanceMove(12, 1); //move towards alliance goal
	effectors.runOne(GOAL_LIFT, 0);


	goal = drive->getState();
	goal.theta = 180_deg; //
	pidMoveTank(goal, {0, 0, 0}, {0.01, 0.000005, 0}, true); //turn to dump goal
	intake->run(true, false, -200); //start intake
	fourbarpneum->turnOff(); //dump goal
	pros::delay(750); //wait
	goal = drive->getState();
	goal.theta = 295_deg;
	pidMoveTank(goal, {0, 0, 0}, {0.01, 0.000005, 0}, true); //turn towards center goal
	pros::delay(200);
	intake->run(true, false, 0); //end intake
	fourbar1->moveTarget(0); //lower four bar
  	fourbar2->moveTarget(0); //lower four bar
	distanceMove(54, -1); //move towards center goal
	fourbarpneum->turnOn(); //clamp
	pros::delay(300); //wait
	//goal.theta = 225_deg;
	//pidMoveTank(goal, {0, 0, 0}, {0.02, 0.000005, 0}, true); //turn slightly to be able to get back into home zone
	distanceMove(30, -1); //move goal forwards
	// goal.theta = 225_deg;
	// pidMoveTank(goal, {0, 0, 0}, {0.02, 0.000005, 0}, true); //drop neutral
	fourbarpneum->turnOff();
	distanceMove(5, 1);
	goal.theta = 225_deg;
	pidMoveTank(goal, {0, 0, 0}, {0.02, 0.000005, 0}, true); //turn towards other neutral
	distanceMove(30, -1);
	fourbarpneum->turnOn();
	pros::delay(600);
	// goal.theta = 0_deg;
	// pidMoveTank(goal, {0, 0, 0}, {0.02, 0.000005, 0}, true); //turn towards other zone
	distanceMove(35, 1);
}

void newSkills() {
	setEffectorPositions();
	effectors.runOne(GOAL_LIFT, 1);	//two bar down
	pros::delay(750);				//wait
	distanceMove(16, 0.7);			//Move backwards to grab alliance goal
	effectors.runOne(GOAL_LIFT, 0);	//two bar up
	distanceMove(2, -0.4);			//moving away from seesaw
	OdomState goal = drive->getState();
	goal.theta = 270_deg;
	pidMoveTank(goal, {0, 0, 0}, {0.007, 0.000005, 0}, true);	//turn to 90 deg
//---------------------------------------------------------------
//FIRST NEUTRAL

	distanceMove(24, 1);			//moving towards goal
	goal.theta = 90_deg;			//stop and turn
	pidMoveTank(goal, {0, 0, 0}, {0.007, 0.000005, 0}, true);	//turn 180 to face goal with four bar
	distanceMove(30, -1);			//move the rest of the distance to the goal
	fourbarpneum->turnOn();			//clamp
	fourbar1->moveTarget(500);		//raise four bar
	fourbar2->moveTarget(500);		//raise four bar
	intake->run(true, false, -150);	//start intake
	distanceMove(30, -0.9);			//move the rest of the way towards the ring line
//---------------------------------------------------------------
//RINGS ON ALLIANCE GOAL
	goal.theta = 180_deg;			//make the turn towards 180 deg
	pidMoveTank(goal, {0, 0, 0}, {0.01, 0.000005, 0}, true);
	distanceMove(24, -1);			//move quickly to the rings
	distanceMove(48, -0.5);			//then move slowly to intake the rings
//-----------------------------------------------------------------
//FIRST NEUTRAL ON PLATFORM

	distanceMove(36, 0.8);			//backwards to orient for the platform
	goal.theta = 90_deg;			//turn towards platform
	pidMoveTank(goal, {0, 0, 0}, {0.01, 0.000005, 0}, true);
	fourbar1->moveTarget(2400);		//four bar up
	fourbar2->moveTarget(2400);
	pros::delay(300);
	distanceMove(12, -0.4);			//move towards platform
	fourbar1->moveTarget(2000);
	fourbar2->moveTarget(2000);
	fourbarpneum->turnOff();		//release clamp
	distanceMove(12, 0.4);			//back away from seesaw
	fourbar1->moveTarget(0);		//four bar down
	fourbar2->moveTarget(0);

// -------------------------------------------------------------------------
// ALLIANCE GOAL MANIPULATION

	goal.theta = 0_deg;				//turn towards forwards
	pidMoveTank(goal, {0, 0, 0}, {0.007, 0.000005, 0}, true);
	effectors.runOne(GOAL_LIFT, 1);	//drop two bar
	distanceMove(12, 0.8);			//move forwards
	effectors.runOne(GOAL_LIFT, 2);	//bring two bar all the way up
	pros::delay(1000);				//wait for that to happen before turning
	goal.theta = 180_deg;			//turn around
	pidMoveTank(goal, {0, 0, 0}, {0.01, 0.000005, 0}, true);
	distanceMove(12, -1);			//Move forwards back towards the alliance goal
	fourbarpneum->turnOn();			//clamp
	fourbar1->moveTarget(2400);		//four bar up
	fourbar2->moveTarget(2400);
	pros::delay(1000);
	goal.theta = 90_deg;			//turn towards platform
	pidMoveTank(goal, {0, 0, 0}, {0.01, 0.000005, 0}, true);
	fourbar1->moveTarget(2000);		//four bar slightly down
	fourbar2->moveTarget(2000);
	distanceMove(12, -0.4);			//move towards platform
	fourbarpneum->turnOff();		//release clamp
	distanceMove(12, 0.4);			//backwards movement
	fourbar1->moveTarget(0);		//four bar down
	fourbar2->moveTarget(0);

//-------------------------------------------------------------------------
// SECOND SIDE NEUTRAL MANIPULATION

	goal.theta = 180_deg;
	pidMoveTank(goal, {0, 0, 0}, {0.01, 0.000005, 0}, true);
	distanceMove(36, -0.9);			//moving towards the side neutral
	goal.theta = 270_deg;			//turn towards it
	pidMoveTank(goal, {0, 0, 0}, {0.01, 0.000005, 0}, true);
	distanceMove(36, -1);			//move quickly towards it
	fourbarpneum->turnOn();			//clamp
	fourbar1->moveTarget(500);		//four bar up
	fourbar1->moveTarget(500);
	distanceMove(36, 0.9);			//move backwards to retrace steps
	goal.theta = 0_deg;				//turn to 0
	pidMoveTank(goal, {0, 0, 0}, {0.01, 0.000005, 0}, true);
	fourbar1->moveTarget(2100);
	fourbar2->moveTarget(2100);
	distanceMove(36, -1);			//moving forwards to platform
	goal.theta = 90_deg;
	pidMoveTank(goal, {0, 0, 0}, {0.01, 0.000005, 0}, true);
	distanceMove(12, -0.4);
	fourbarpneum->turnOff();
	distanceMove(12, 0.4);			//backwards from seesaw
	fourbar1->moveTarget(0);		//four bar down
	fourbar2->moveTarget(0);

//-------------------------------------------------------------------
//MOVEMENT FOR FIRST RED ALLIANCE GOAL

	goal.theta = 180_deg;			//turning towards back wall
	pidMoveTank(goal, {0, 0, 0}, {0.01, 0.000005, 0}, true);
	distanceMove(48, -1);			//moving towards the turn location
	goal.theta = 48_deg;			//turning towards alliance goal
	pidMoveTank(goal, {0, 0, 0}, {0.01, 0.000005, 0}, true);
	distanceMove(30, -0.6);			//move towards the goal
	fourbarpneum->turnOn();			//clamp
	distanceMove(30, 0.6);			//move away from the goal
	fourbar1->moveTarget(500);		//four bar slightly up
	fourbar2->moveTarget(500);		//four bar slightly up
	pros::delay(500);
	goal.theta = 0_deg;				//turning towards other alliance goal
	pidMoveTank(goal, {0, 0, 0}, {0.01, 0.000005, 0}, true);
//-------------------------------------------------------------------
//MOVEMENT FOR SECOND RED ALLIANCE GOAL

	distanceMove(80, -1);
	effectors.runOne(GOAL_LIFT, 1);	//lower two bar
	pros::delay(1500);
	distanceMove(15, -0.7);			//move the rest of the distance
	pros::delay(500);
	effectors.runOne(GOAL_LIFT, 0);	// two bar up
	distanceMove(1, 0.8);
	goal.theta = 270_deg;
	pidMoveTank(goal, {0, 0, 0}, {0.01, 0.000005, 0}, true);

//------------------------------------------------------------------
//RINGS
	fourbar1->moveTarget(2400);
	fourbar2->moveTarget(2400);
	distanceMove(96, -0.7);
	goal.theta = 180_deg;
	pidMoveTank(goal, {0, 0, 0}, {0.01, 0.000005, 0}, true);
	distanceMove(3, -0.6);
	fourbar1->moveTarget(100);
	fourbar2->moveTarget(100);
	autobalancer(23.5);
}

void leftskills() {
	OdomState goal = drive->getState();
	setEffectorPositions();
  	effectors.runOne(GOAL_LIFT, 1); 			//lower goal lift
  	pros::delay(1500);
  	distanceMove(15, 0.5); 						// move forwards and get goal
	effectors.runOne(GOAL_LIFT, 0); 			// raise goal lift
	pros::delay(500);
	goal = drive->getState();
	goal.theta = 270_deg;
	pidMoveTank(goal, {0, 0, 0}, {0.006, 0.000005, 0}, true);	//turn to 90 deg
   	distanceMove(24, 0.7);  						//move towards side neutral mogo
	pros::delay(500);
	goal = drive->getState();
	goal.theta = 110_deg;
	pidMoveTank(goal, {0, 0, 0}, {0.005, 0.000005, 0}, true);	//turn to 90 deg
	distanceMove(32, -1);  						//move towards side neutral mogo

   	fourbarpneum->turnOn(); 					//clamp
	pros::delay(300);
	fourbar1->moveTarget(2400);  				//four bar up
	fourbar2->moveTarget(2400);

	goal = drive->getState();
  	goal.theta = 90_deg;   					//turn towards center
	pidMoveTank(goal, {0, 0, 0}, {0.01, 0.000005, 0}, true);
   	distanceMove(10, -0.5);  					//move towards ring cross line
	goal = drive->getState();
  	goal.theta = 180_deg;  						//turn towards ring crosses
	pidMoveTank(goal, {0, 0, 0}, {0.008, 0.000005, 0}, true);
	intake->run(true, false, -150);
	// effectors.runOne(GOAL_LIFT, 1);
	distanceMove(40, -0.5);  					//move through rings
	distanceMove(3, 0.8);						//move back to platform
	goal = drive->getState();
  goal.theta = 92_deg;  						//turn towards platform
	pidMoveTank(goal, {0, 0, 0}, {0.008, 0.000005, 0}, true);
	distanceMove(14, -0.5);
	fourbar1->moveTarget(1800);  				//four bar down to balance platform
	fourbar2->moveTarget(1800);
	pros::delay(500);
	fourbarpneum->turnOff();  					//release clamp
	pros::delay(500);
	fourbar1->moveTarget(2400);
	fourbar2->moveTarget(2400);
	pros::delay(500);
	distanceMove(2, 0.5);  						//move away from platform
	goal = drive->getState();
  	goal.theta = 180_deg;  						//turn towards other side neutral
	pidMoveTank(goal, {0, 0, 0}, {0.007, 0.000005, 0}, true);
	intake->run(true, false, -150);
	fourbar1->moveTarget(0);  					//four bar down
	fourbar2->moveTarget(0);
	distanceMove(35, -0.65);  					//move towards side neutral
	goal = drive->getState();
	goal.theta = 272_deg;  						//turn towards other side neutral
	pidMoveTank(goal, {0, 0, 0}, {0.008, 0.000005, 0}, true);
	distanceMove(35, -0.65);
	fourbarpneum->turnOn();  					//clamp

	distanceMove(30, 0.65);   					//move backwards to line
	fourbar1->moveTarget(2400);
	fourbar2->moveTarget(2400);
	goal = drive->getState();
	goal.theta = 359_deg;
	pidMoveTank(goal, {0, 0, 0}, {0.008, 0.000005, 0}, true);
	distanceMove(36, -0.65);  //move backwards to goal
	pros::delay(500);
	fourbar1->moveTarget(2150); 				//lower four bar
	fourbar2->moveTarget(2150);
	goal = drive->getState();
  	goal.theta = 86_deg;						//turn towards platform
	pidMoveTank(goal, {0, 0, 0}, {0.0085, 0.000008, 0}, true);
	distanceMove(4, -0.8);     				//move forwards to platform

	fourbar1->moveTarget(2000); 				//lower four bar
	fourbar2->moveTarget(2000);
	pros::delay(750);

	fourbarpneum->turnOff();    				//release clamp
	pros::delay(500);
	fourbar1->moveTarget(2200); 				//lower four bar
	fourbar2->moveTarget(2200);

	pros::delay(500);
	distanceMove(3, 0.6);						//backwards from platform


	goal = drive->getState();
	goal.theta = 180_deg;
	pidMoveTank(goal, {0, 0, 0}, {0.007, 0.00000, 0}, true);
	effectors.runOne(GOAL_LIFT, 1);  			//drop two bar
	fourbar1->moveTarget(0);					//four bar down
	fourbar2->moveTarget(0);
	distanceMove(8, -0.6);						//move forwards
	pros::delay(500);
	effectors.runOne(GOAL_LIFT, 2);				//two bar up
	goal.theta = (imu.get_heading() + 180) * 1_deg;						//turn around to go back towards the dropped alliance goal
	pidMoveTank(goal, {0, 0, 0}, {0.005, 0.00000, 0}, true);
	distanceMove(14, -0.8);						//move towards alliance goal
	pros::delay(500);
	fourbarpneum->turnOn();						//clamp
	pros::delay(500);
	fourbar1->moveTarget(2400);					//four bar up
	fourbar2->moveTarget(2400);
	distanceMove(6, 0.8);						//move towards alliance goal
	goal = drive->getState();
  	goal.theta = 87_deg;						//turn back towards platform with alliance goal
	pidMoveTank(goal, {0, 0, 0}, {0.008, 0.000008, 0}, true);
	// fourbar1->moveTarget(2400);				//four bar up
	// fourbar2->moveTarget(2400);
	pros::delay(500);
	fourbar1->moveTarget(2000);
	fourbar2->moveTarget(2000);
	distanceMove(4, -0.6);						//forwards to platform
	// fourbar1->moveTarget(2000);				//four bar down to deposit
	// fourbar2->moveTarget(2000);
	fourbarpneum->turnOff();					//release clamp
	pros::delay(500);
	distanceMove(3, 0.8);						//backwards from platform
	goal.theta = 170_deg;						//turn towards alliance goal that fell off the seesaw
	pidMoveTank(goal, {0, 0, 0}, {0.007, 0.000008, 0}, true);
	fourbar1->moveTarget(0);					//lower four bar
	fourbar2->moveTarget(0);
	distanceMove(37, -1);						//moving forwards towards the first alliance goal that came off the seesaw
	goal.theta = 50_deg;						//turn towards alliance goal
	pros::delay(500);
	pidMoveTank(goal, {0, 0, 0}, {0.007, 0.000008, 0}, true);
	distanceMove(28, -0.5);						//move towards alliance goal
	fourbarpneum->turnOn();						//clamp
	distanceMove(24, 0.7);						//Move away from alliance goal
	fourbar1->moveTarget(2400);					//four bar slightly up
	fourbar2->moveTarget(2400);
	// goal.theta = 85_deg;
	// pidMoveTank(goal, {0, 0, 0}, {0.007, 0.000008, 0}, true);
	// distanceMove(6, 1);
	// pros::delay(250);
	goal.theta = 141_deg;						//turn so that we can move backwards to the other alliance goal
	pidMoveTank(goal, {0, 0, 0}, {0.005, 0.000008, 0}, true);
	effectors.runOne(GOAL_LIFT, 1);				//drop two bar
	pros::delay(500);
	distanceMove(110, 0.8);						//move quickly to the alliance goal
	pros::delay(750);
	effectors.runOne(GOAL_LIFT, 0); 			//raise two bar
	pros::delay(1000);
	goal.theta = 270_deg;						//turn to face the rings
	pidMoveTank(goal, {0, 0, 0}, {0.007, 0.000008, 0}, true);
	fourbar1->moveTarget(2400);					//four bar up a bit
	fourbar2->moveTarget(2400);
	intake->run(true, false, -150);				//start intake


	speedMove(1000, -0.7);
	distanceMove(1, 0.5);
	//distanceMove(86, -0.6);					//move along the rings
	goal.theta = 175_deg;						//turn to climb on the seesaw
	pidMoveTank(goal, {0, 0, 0}, {0.007, 0.000008, 0}, true);
	// fourbar1->moveTarget(2000);				//four bar up to put the seesaw down
	// fourbar2->moveTarget(2000);
	distanceMove(1, -0.5);
	fourbar1->moveTarget(0);					//four bar down to put the seesaw down
	fourbar2->moveTarget(0);
	pros::delay(2000);
	fourbar1->moveTarget(150);
	fourbar2->moveTarget(150);
	// distanceMove(40, -1.0);					//autobalance
	autobalancer(24);
	pros::delay(10000);
}

void rightrings() {
	setEffectorPositions();
	fourbar1->moveTarget(500); //lift four bar to intake
  	fourbar2->moveTarget(500);
	effectors.runOne(GOAL_LIFT, 1); //lower two bar
	pros::delay(1500);
	distanceMove(20, 1); //pick up alliance
	effectors.runOne(GOAL_LIFT, 0); //raise two bar
	distanceMove(12, -1); //move back
	intake->run(true, false, -175); //turn on intake
	while(1) {
		//oscillate to pick up rings
		distanceMove(7, -0.5);
		pros::delay(500);
		distanceMove(7, 0.5);
	}


}

void rightMiddle() {
	distanceMove(53, -1);	//move towards side neutral at full speed
	fourbarpneum->turnOn(); //clamp it
	pros::delay(300); //delay 300 ms
	printf("Finished\n");
	distanceMove(53, 1); //move back
}

void left() {
	setEffectorPositions();
  	printf("done\n");
	distanceMove(43, -1);	//move towards side neutral at full speed
	fourbarpneum->turnOn(); //clamp it
	pros::delay(200);
	printf("Finished\n");
	distanceMove(10, 1); //move back
	pidTurn(20_deg, {0.02, 0.000008, 0});
	distanceMove(7, 0.6);
}

void middle() {
	setEffectorPositions();
	printf("done\n");
	distanceMove(50, -1);	//move towards side neutral at full speed
	fourbarpneum->turnOn(); //clamp it
	pros::delay(100);
	printf("Finished\n");
	distanceMove(10, 1); //move back
	distanceMove(14, 0.6);
}

void rightthenmiddle() {
	setEffectorPositions();
	printf("done\n");
	distanceMove(39, -1);	//move towards side neutral at full speed
	fourbarpneum->turnOn(); //clamp it
	pros::delay(100);
	printf("Finished\n");
	distanceMove(10, 1); //move back
	pidTurn(270_deg, {0.01, 0.000008, 0});
	fourbarpneum->turnOff();

}

void leftmiddle() {
	setEffectorPositions();
	intake->run(true, false, -180);
	printf("done\n");
	distanceMove(69, -0.7);	//move towards side neutral at full speed
	fourbarpneum->turnOn(); //clamp it
	pros::delay(100);
	printf("Finished\n");
	distanceMove(10, 1); //move back
	distanceMove(20, 0.6);
}



void esbensOdom() {
	// jank, Esben-coded odom that involves taking the current angle at the middle of an interval of 50 ms and after 50 ms,
	// calculating a linear distance in x and y even if the movement is a curve
	// essentially a linear approximation of the movement, 20 times per second

	float x = 0;		//variables for tracking
	float y = 0;

	ADIEncoder righttrack = ADIEncoder('A', 'B', false);		//encoders because i don't know how to get values
	ADIEncoder lefttrack = ADIEncoder('C', 'D', true);

	righttrack.reset();	//reset encoders to zero
	lefttrack.reset();

	float currangle = imu.get_heading();
	float right = 0;
	float left = 0;

	while (true)
	{
		pros::delay(25);
		currangle = imu.get_heading();
		pros::delay(25);
		int currright = righttrack.get();
		int currleft = lefttrack.get();
		int rightencchange = currright - right;
		int leftencchange = currleft - left;
		float average = (rightencchange + leftencchange)/2 / 360 * 2.75 * PI;
		x += average * cos(currangle);
		y += average * sin(currangle);
		pros::c::lcd_print(0, "OdomX: %f\n", x);		//display on lcd screen
		pros::c::lcd_print(1, "OdomY: %f\n", y);
		pros::c::lcd_print(2, "OdomH: %d\n", currangle);
		right = currright;
		left = currleft;
	}

}





void autonomous() {

	//okapi::Controller controller (okapi::ControllerId::master);
	drive->setMode(okapi::AbstractMotor::brakeMode::hold);
	left();
	//right();
	//middle();
	//left();
	//leftfast();
	//drive->setMode(okapi::AbstractMotor::brakeMode::coast);
}

//experimental pure pursuit handler
void PurePursuitHandler() {
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
}
