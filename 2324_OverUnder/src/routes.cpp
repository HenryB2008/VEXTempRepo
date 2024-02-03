#include "main.h"
#include "lemlib/api.hpp"

ASSET(underalt_txt);
ASSET(left_txt);

void far_driver(lemlib::Chassis* chassis) {
	chassis->setPose(42, -56.5, 45);

	left_wing.set_value(true);
	pros::delay(400);

	left_drive.move(40);
	right_drive.move(40);

	// while (chassis->getPose().x < 50) {
	// 	pros::delay(10);
	// }
	// left_wing.set_value(false);

	while (chassis->getPose().x < 50) {		// actually 52.5
		pros::delay(10);
	}
	left_drive.move(0);
	right_drive.move(80);

	// while (chassis->getPose().theta > 40) {
	// 	pros::delay(10);
	// }
	left_wing.set_value(false);

	while (chassis->getPose().theta > 25) {	// actually 22.5
		pros::delay(10);
	}
	left_drive.move(40);
	right_drive.move(40);
	pros::delay(200);
	left_drive.move(0);

	while (chassis->getPose().theta > 0) {	// actually 0
		pros::delay(10);
	}
	intake.move(127);
	left_drive.move(0);
	right_drive.move(0);
	pros::delay(400);


	left_drive.move(127);
	right_drive.move(127);
	pros::delay(500);
	left_drive.move(0);
	right_drive.move(0);
	intake.move(0);
	pros::delay(400);
	
	chassis->setPose(57, -33.5, chassis->getPose().theta);
	left_drive.move(-50);
	right_drive.move(-50);
	pros::delay(500);
	left_drive.move(0);
	right_drive.move(0);

	chassis->moveToPoint(10, -26, 3000, {.maxSpeed = 60});
	intake.move(-127);
	chassis->waitUntilDone();

	left_drive.move(10);
	right_drive.move(60);
	pros::delay(400);
	left_drive.move(0);
	right_drive.move(0);
	pros::delay(200);
	
	chassis->setPose(8.5, -26, -90);

	chassis->moveToPoint(24, -26, 3000, {.forwards = false, .maxSpeed = 60});
	chassis->waitUntilDone();

	pros::delay(150);

	left_drive.move(70);
	right_drive.move(1);

	while (chassis->getPose().theta < -45) {
		pros::delay(10);
	}
	right_drive.move(20);

	while (chassis->getPose().theta < 45) {
		pros::delay(10);
	}
	left_wing.set_value(true);
	right_drive.move(0);

	while (chassis->getPose().theta < 70) {
		pros::delay(10);
	}

	left_drive.move(0);
	right_drive.move(0);
	pros::delay(500);
	

	intake.move(127);
	left_drive.move(127);
	right_drive.move(127);
	pros::delay(600);	// ram goal

	left_drive.move(0);
	right_drive.move(0);
	intake.move(0);
	pros::delay(300);


	left_drive.move(-50);
	right_drive.move(-50);
	pros::delay(300);
	left_drive.move(0);
	right_drive.move(0);
	pros::delay(200);

	// left_drive.move(127);
	// right_drive.move(127);
	// pros::delay(500);
	// left_drive.move(0);
	// right_drive.move(0);
	// pros::delay(300);
	// left_drive.move(-50);
	// right_drive.move(-50);
	// pros::delay(300);
	// left_drive.move(0);
	// right_drive.move(0);
	// pros::delay(300);

	left_wing.set_value(false);

	chassis->turnTo(5, -70, 2000, true, 50);
	chassis->waitUntilDone();
	pros::delay(10);
	blocker.set_value(true);
	left_drive.move(80);
	right_drive.move(80);
	pros::delay(500);
	left_drive.move(40);
	right_drive.move(40);
	pros::delay(700);
	left_drive.move(0);
	right_drive.move(0);


}

void awp(lemlib::Chassis* chassis) {
    
}

void elims(lemlib::Chassis* chassis) {
    
}

void close_driver(lemlib::Chassis* chassis) {
	chassis->setPose(40.5, 58, 315);
	while (chassis->getPose().x < 46) { // 49.69, 48.81
		left_drive.move(-50);
		right_drive.move(-43);
	}
	left_drive.move(0);
	// pros::delay(100);
	right_drive.move(0);
	pros::delay(300);
	left_wing.set_value(true);
	pros::delay(700);
	right_drive.move(127);
	left_drive.move(-127);
	pros::delay(200);
	right_drive.move(0);
	left_drive.move(0);
	pros::delay(500);
	left_wing.set_value(false);
	
	chassis->turnTo(70, 24, 2000, true);
	chassis->waitUntilDone();
	left_drive.move(50);
	right_drive.move(50);
	pros::delay(450);
	left_drive.move(70);
	right_drive.move(0);
	pros::delay(75);
	intake.move(127);
	pros::delay(600);
	left_drive.move(0);
	pros::delay(300);
	intake.move(0);
	right_drive.move(50);
	pros::delay(350);
	right_drive.move(0);
	pros::delay(400);
	chassis->setPose(58, 34, chassis->getPose().theta);

	// back up
	left_drive.move(-40);
	right_drive.move(-40);
	pros::delay(500);
	left_drive.move(0);
	right_drive.move(0);
	pros::delay(300);

	
	chassis->moveToPoint(36, 67, 3000, {.maxSpeed = 65});
	chassis->turnTo(-72, 67, 2000, false, 50);

	chassis->waitUntilDone();
	pros::delay(300);
	pros::delay(100);
	left_drive.move(-80);
	right_drive.move(-80);
	pros::delay(800);
	left_drive.move(0);
	right_drive.move(0);
	pros::delay(400);
	left_drive.move(-30);
	right_drive.move(-30);
	pros::delay(400);
	left_drive.move(0);
	right_drive.move(0);
}

// void own_secondary(lemlib::Chassis* chassis) {
//     chassis->setPose(16.3125, 22.5, 45);

//     blocker.set_value(true);
//     pros::delay(400);

    
//     while (chassis->getPose().theta < 85) {
//         left_drive.move(60);
//         right_drive.move(-30);
//     }
//     left_drive.move(0);
//     right_drive.move(20);
//     pros::delay(200);
//     right_drive.move(0);
//     blocker.set_value(false);
//     pros::delay(200);

//     chassis->moveToPoint(36, 12, 2000, 50);
//     pros::delay(200);

//     chassis->turnTo(144, 12, 2000, false, 60);

//     intake.move(127);
//     pros::delay(500);
//     intake.move(0);

//     left_drive.move(128);
//     right_drive.move(128);
//     pros::delay(500);
//     left_drive.move(0);
//     right_drive.move(0);

//     pros::delay(500);

//     left_drive.move(-50);
//     right_drive.move(-50);
//     pros::delay(250);
//     left_drive.move(0);
//     right_drive.move(0);

//     chassis->moveToPoint(48, 48, 2000, 50);
//     pros::delay(200);
//     intake.move(-127);
//     chassis->moveToPoint(48, 64, 1250, 50);
//     pros::delay(200);
//     left_drive.move(-50);
//     right_drive.move(-50);
//     pros::delay(100);
//     left_drive.move(0);
//     right_drive.move(0);


//     chassis->turnTo(68, 64, 2000, false, 50);
//     chassis->moveToPoint(68, 64, 2000, 50);
//     chassis->turnTo(68, 24, 2000, false, 50);
//     left_wing.set_value(true);
//     pros::delay(100);
//     intake.move(127);
//     chassis->moveToPoint(68, 24, 2000, 80);
//     left_drive.move(-50);
//     right_drive.move(-50);
//     pros::delay(150);
//     left_drive.move(0);
//     right_drive.move(0);
//     intake.move(0);


void skills(lemlib::Chassis* chassis) {
    chassis->setPose(-48.5, -55.5, 90);
	
	while (chassis->getPose().theta > 65) {
        left_drive.move(-40);
    }
    left_drive.move(0);
	pros::delay(300);

	cata.move(127*.9);
	pros::delay(30000);
	cata.move(0);

	double startTheta = chassis->getPose().theta;
	while (chassis->getPose().theta < startTheta + 25) {
        left_drive.move(40);
    }
	left_drive.move(0);

	pros::delay(300);
	chassis->setPose(-47.5, -52.5, chassis->getPose().theta);

	chassis->follow(underalt_txt, 12, 18000, true, true);

	while (chassis->getPose().x < -24) {
	 	pros::delay(10);
	}
	cata.move(70);
	pros::delay(1000);
	cata.move(0);
	chassis->waitUntilDone();
	pros::delay(200);

	chassis->turnTo(72, 0, 2000, true, 50);
	chassis->waitUntilDone();
	pros::delay(200);

	left_wing.set_value(true);
	left_drive.move(127);
	right_drive.move(127);

	while (chassis->getPose().x < 26) {
		pros::delay(10);
	}
	intake.move(127);

	pros::delay(500);
	left_drive.move(0);
	right_drive.move(0);
	left_wing.set_value(false);
	pros::delay(200);
	left_drive.move(-70);
	right_drive.move(-70);
	pros::delay(500);
	left_drive.move(0);
	right_drive.move(0);
	left_wing.set_value(true);
	pros::delay(200);
	left_drive.move(127);
	right_drive.move(127);
	pros::delay(600);
	left_drive.move(-70);
	right_drive.move(-70);
	pros::delay(500);
	left_drive.move(0);
	right_drive.move(0);
	left_wing.set_value(false);
	pros::delay(200);

	// do question mark in front
	right_drive.move(-75);
	left_drive.move(-1);
	pros::delay(500);
	left_drive.move(-75);
	right_drive.move(-1);
	pros::delay(500);
	left_drive.move(0);
	right_drive.move(0);
	left_wing.set_value(true);
	pros::delay(100);
	left_drive.move(127);
	right_drive.move(127);
	pros::delay(600);
	left_drive.move(0);
	right_drive.move(0);
	left_wing.set_value(false);
	pros::delay(200);
	left_drive.move(-60);
	right_drive.move(-60);
	pros::delay(300);
	left_drive.move(0);
	right_drive.move(0);

	// left part
	pros::delay(100);
	chassis->turnTo(chassis->getPose().x, 80, 2000, true, 50);
	chassis->waitUntilDone();
	pros::delay(300);
	chassis->setPose(33, 11, chassis->getPose().theta);
	chassis->follow(left_txt, 10, 12000, true, true);
	pros::delay(2500);
	left_wing.set_value(true);
	pros::delay(1200);
	left_wing.set_value(false);

	pros::delay(1200);
	chassis->cancelMotion();
	left_drive.move(-60);
	right_drive.move(-60);
	pros::delay(500);
	left_drive.move(0);
	right_drive.move(0);
	pros::delay(200);
	left_drive.move(127);
	right_drive.move(127);
	pros::delay(700);
	left_drive.move(-60);
	right_drive.move(-60);
	pros::delay(500);
	left_drive.move(0);
	right_drive.move(0);
	
	
	// second identical ram (third total on left)
	pros::delay(200);
	left_drive.move(127);
	right_drive.move(127);
	pros::delay(700);
	left_drive.move(-60);
	right_drive.move(-60);
	pros::delay(500);
	left_drive.move(0);
	right_drive.move(0);
	pros::delay(200);
	intake.move(0);
}
