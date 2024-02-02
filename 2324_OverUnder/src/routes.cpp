#include "main.h"
#include "lemlib/api.hpp"

ASSET(underalt_txt);
ASSET(left_txt);

void opposite_side(lemlib::Chassis* chassis) {
    // chassis->setPose(129.4375, 24.6875, -45);

    // blocker.set_value(true);
    // pros::delay(400);

    // while (chassis->getPose().theta > -85) {
    //     right_drive.move(60);
    // }
    // right_drive.move(0);
    
    // blocker.set_value(false);
    // pros::delay(600);

    // chassis->moveToPoint(108, 10, 2000, 50);
    // pros::delay(200);

    // chassis->turnTo(0, 10, 2000, false, 60);

    // intake.move(127);
    // pros::delay(1000);
    // intake.move(0);

    // left_drive.move(128);
    // right_drive.move(128);
    // pros::delay(500);
    // left_drive.move(0);
    // right_drive.move(0);

    // pros::delay(500);

    // left_drive.move(-50);
    // right_drive.move(-50);
    // pros::delay(100);
    // left_drive.move(0);
    // right_drive.move(0);

    // chassis->moveToPoint(132, 36, 2000, 70);

    // chassis->turnTo(132, 72, 2000, true, 60);
    // blocker.set_value(true);
    // pros::delay(200);
    // left_drive.move(-60);
    // right_drive.move(-60);
    // pros::delay(1000);
    // left_drive.move(0);
    // right_drive.move(0);
    // blocker.set_value(false);
}

void awp(lemlib::Chassis* chassis) {
    
}

void elims(lemlib::Chassis* chassis) {
    
}

void own_side(lemlib::Chassis* chassis) {
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
//     pros::delay(600);

//     chassis->moveToPoint(36, 12, 2000, 50);
//     pros::delay(200);

//     chassis->turnTo(144, 12, 2000, false, 60);

//     intake.move(127);
//     pros::delay(1000);
//     intake.move(0);

//     left_drive.move(128);
//     right_drive.move(128);
//     pros::delay(500);
//     left_drive.move(0);
//     right_drive.move(0);

//     pros::delay(500);

//     left_drive.move(-50);
//     right_drive.move(-50);
//     pros::delay(100);
//     left_drive.move(0);
//     right_drive.move(0);

//     chassis->moveToPoint(14, 36, 2000, 50);

//     chassis->turnTo(14, 72, 2000, false, 60);
//     blocker.set_value(true);
//     intake.move(-127);
//     pros::delay(200);
//     left_drive.move(60);
//     right_drive.move(60);
//     pros::delay(800);
//     left_drive.move(0);
//     right_drive.move(0);
//     pros::delay(1000);
//     intake.move(0);
// }

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
}

void skills(lemlib::Chassis* chassis) {
    chassis->setPose(-48.5, -55.5, 90);
	
	while (chassis->getPose().theta > 65) {
        left_drive.move(-40);
    }
    left_drive.move(0);
	pros::delay(300);

	cata.move(127*.9);
	pros::delay(3000);
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
}
