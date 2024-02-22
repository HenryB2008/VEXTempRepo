#include "main.h"
#include "lemlib/api.hpp"

ASSET(startsweep_txt);
ASSET(leftmove_txt);
ASSET(frontpush_txt);

double RAM_PULLEY = 2.25; // gap between ramming area and intake pulleys
double TC_RAM = 7.75; 	// gap between vertical tracking center and ramming area


void far_driver(lemlib::Chassis* chassis) {
	// chassis->setPose(42, -56.5, 45);

	// left_wing.set_value(true);
	// pros::delay(400);

	// left_drive.move(40);
	// right_drive.move(40);

	// // while (chassis->getPose().x < 50) {
	// // 	pros::delay(10);
	// // }
	// // left_wing.set_value(false);

	// while (chassis->getPose().x < 50) {		// actually 52.5
	// 	pros::delay(10);
	// }
	// left_drive.move(0);
	// right_drive.move(80);

	// // while (chassis->getPose().theta > 40) {
	// // 	pros::delay(10);
	// // }
	// left_wing.set_value(false);

	// while (chassis->getPose().theta > 25) {	// actually 22.5
	// 	pros::delay(10);
	// }
	// left_drive.move(40);
	// right_drive.move(40);
	// pros::delay(200);
	// left_drive.move(0);

	// while (chassis->getPose().theta > 0) {	// actually 0
	// 	pros::delay(10);
	// }
	// intake.move(127);
	// left_drive.move(0);
	// right_drive.move(0);
	// pros::delay(400);


	// left_drive.move(127);
	// right_drive.move(127);
	// pros::delay(500);
	// left_drive.move(0);
	// right_drive.move(0);
	// intake.move(0);
	// pros::delay(400);
	
	// chassis->setPose(57, -33.5, chassis->getPose().theta);
	// left_drive.move(-50);
	// right_drive.move(-50);
	// pros::delay(500);
	// left_drive.move(0);
	// right_drive.move(0);

	// chassis->moveToPoint(10, -26, 3000, {.maxSpeed = 60});
	// intake.move(-127);
	// chassis->waitUntilDone();

	// left_drive.move(10);
	// right_drive.move(60);
	// pros::delay(400);
	// left_drive.move(0);
	// right_drive.move(0);
	// pros::delay(200);
	
	// chassis->setPose(8.5, -26, -90);

	// chassis->moveToPoint(24, -26, 3000, {.forwards = false, .maxSpeed = 60});
	// chassis->waitUntilDone();

	// pros::delay(150);

	// left_drive.move(70);
	// right_drive.move(1);

	// while (chassis->getPose().theta < -45) {
	// 	pros::delay(10);
	// }
	// right_drive.move(20);

	// while (chassis->getPose().theta < 45) {
	// 	pros::delay(10);
	// }
	// left_wing.set_value(true);
	// right_drive.move(0);

	// while (chassis->getPose().theta < 70) {
	// 	pros::delay(10);
	// }

	// left_drive.move(0);
	// right_drive.move(0);
	// pros::delay(500);
	

	// intake.move(127);
	// left_drive.move(127);
	// right_drive.move(127);
	// pros::delay(600);	// ram goal

	// left_drive.move(0);
	// right_drive.move(0);
	// intake.move(0);
	// pros::delay(300);


	// left_drive.move(-50);
	// right_drive.move(-50);
	// pros::delay(300);
	// left_drive.move(0);
	// right_drive.move(0);
	// pros::delay(200);

	// // left_drive.move(127);
	// // right_drive.move(127);
	// // pros::delay(500);
	// // left_drive.move(0);
	// // right_drive.move(0);
	// // pros::delay(300);
	// // left_drive.move(-50);
	// // right_drive.move(-50);
	// // pros::delay(300);
	// // left_drive.move(0);
	// // right_drive.move(0);
	// // pros::delay(300);

	// left_wing.set_value(false);

	// chassis->turnToPoint(5, -70, 2000, true, 50);
	// chassis->waitUntilDone();
	// pros::delay(10);
	// blocker.set_value(true);
	// left_drive.move(80);
	// right_drive.move(80);
	// pros::delay(500);
	// left_drive.move(40);
	// right_drive.move(40);
	// pros::delay(1000);
	// left_drive.move(0);
	// right_drive.move(0);


}

void awp(lemlib::Chassis* chassis) {
    
}

void elims(lemlib::Chassis* chassis) {
    
}

void close_driver(lemlib::Chassis* chassis) {
	// chassis->setPose(40.5, 58, 315);
	// while (chassis->getPose().x < 46) { // 49.69, 48.81
	// 	left_drive.move(-50);
	// 	right_drive.move(-43);
	// }
	// left_drive.move(0);
	// // pros::delay(100);
	// right_drive.move(0);
	// pros::delay(300);
	// left_wing.set_value(true);
	// pros::delay(700);
	// right_drive.move(127);
	// left_drive.move(-127);
	// pros::delay(200);
	// right_drive.move(0);
	// left_drive.move(0);
	// pros::delay(500);
	// left_wing.set_value(false);
	
	// chassis->turnToPoint(70, 24, 2000, true);
	// chassis->waitUntilDone();
	// left_drive.move(50);
	// right_drive.move(50);
	// pros::delay(450);
	// left_drive.move(70);
	// right_drive.move(0);
	// pros::delay(75);
	// intake.move(127);
	// pros::delay(600);
	// left_drive.move(0);
	// pros::delay(300);
	// intake.move(0);
	// right_drive.move(50);
	// pros::delay(350);
	// right_drive.move(0);
	// pros::delay(400);
	// chassis->setPose(58, 34, chassis->getPose().theta);

	// // back up
	// left_drive.move(-40);
	// right_drive.move(-40);
	// pros::delay(500);
	// left_drive.move(0);
	// right_drive.move(0);
	// pros::delay(300);

	
	// chassis->moveToPoint(36, 67, 3000, {.maxSpeed = 65});
	// chassis->turnToPoint(-72, 67, 2000, false, 50);

	// chassis->waitUntilDone();
	// pros::delay(300);
	// pros::delay(100);
	// left_drive.move(-80);
	// right_drive.move(-80);
	// pros::delay(800);
	// left_drive.move(0);
	// right_drive.move(0);
	// pros::delay(400);
	// left_drive.move(-30);
	// right_drive.move(-30);
	// pros::delay(400);
	// left_drive.move(0);
	// right_drive.move(0);
}

void push(int fspd, int fdur, int bspd, int bdur, bool start_back) {
	if (start_back) {
		left_drive.move(-bspd);
		right_drive.move(-bspd);
		pros::delay(bdur);
		left_drive.move(0);
		right_drive.move(0);
		pros::delay(0);
	}
	pros::delay(50);

	left_drive.move(fspd);
	right_drive.move(fspd);
	pros::delay(fdur);
	left_drive.move(0);
	right_drive.move(0);

	if (!start_back) {
		pros::delay(0);
		left_drive.move(-bspd);
		right_drive.move(-bspd);
		pros::delay(bdur);
		left_drive.move(0);
		right_drive.move(0);
	}
}


void skills(lemlib::Chassis* chassis) {
    chassis->setPose(-49, -55.25, 90);  // width front bumper to front bumper is 14.25 in
	
	while (chassis->getPose().theta > 65) {
        left_drive.move(-40);
    }
    left_drive.move(0);
	pros::delay(150);

	cata.move(127*.9);
	pros::delay(2000);
	cata.move(0);

	// double startTheta = chassis->getPose().theta;
	// while (chassis->getPose().theta < startTheta + 25) {
    //     left_drive.move(40);
    // }
	// left_drive.move(0);

	// begin skills route

	left_drive.move(50);
	right_drive.move(-1);

	while (chassis->getPose().theta < 140) {
		pros::delay(10);
	}
	left_drive.move(0);
	right_drive.move(0);
	pros::delay(100);

	chassis->moveToPose(-57, -31, 180, 3000, {.forwards = false, .minSpeed = 127});
	chassis->waitUntilDone();
	pros::delay(150);

	push(50, 200, 127, 300, false);
	left_drive.move(40);
	right_drive.move(40);
	pros::delay(200);
	left_drive.move(0);
	right_drive.move(0);
	pros::delay(50);

	chassis->turnToHeading(270, 1000, {.maxSpeed = 90});

	chassis->follow(startsweep_txt, 11, 5000, false);

	while (chassis->getPose().y < -24) {
		pros::delay(10);
	}
	vert_wing.set_value(true);
	
	chassis->waitUntilDone();
	vert_wing.set_value(false);
	pros::delay(200);
	chassis->setPose(-12.5, 39.5, chassis->getPose().theta);

	intake.move(127);
	chassis->follow(leftmove_txt, 12, 8500);

	while (chassis->getPose().x < 12) {
		pros::delay(10);
	}
	cata.move(70);
	pros::delay(500);
	cata.move(0);

	chassis->waitUntilDone();
	left_wing.set_value(true);
	pros::delay(100);
	push(127, 500, 50, 250, true);		// second left push
	intake.move(0);

	left_wing.set_value(false);
	pros::delay(100);
	chassis->setPose(34.25, 61.5, chassis->getPose().theta);

	left_drive.move(-40);
	right_drive.move(-40);
	pros::delay(200);
	left_drive.move(0);
	right_drive.move(0);

	//chassis->turnToHeading(90, 1000, {.maxSpeed = 90});	// turn to red side for pure pursuit
	left_drive.move(-40);
	right_drive.move(2);
	pros::delay(300);
	left_drive.move(0);
	right_drive.move(0);

	chassis->turnToHeading(90, 1000, {.maxSpeed = 90});
	
	chassis->follow(frontpush_txt, 11, 5000, false);
	
	pros::delay(300);
	vert_wing.set_value(true);
	//pros::delay(3000);

	// intake 

	chassis->waitUntilDone();

	//push(127, 500, 50, 250, true);
}
