#include "main.h"
#include "lemlib/api.hpp"

void opposite_side(lemlib::Chassis* chassis) {
    chassis->setPose(129.4375, 24.6875, -45);

    blocker.set_value(true);
    pros::delay(400);

    while (chassis->getPose().theta > -85) {
        right_drive.move(60);
    }
    right_drive.move(0);
    
    blocker.set_value(false);
    pros::delay(600);

    chassis->moveToPoint(108, 10, 2000, 50);
    pros::delay(200);

    chassis->turnTo(0, 10, 2000, false, 60);

    intake.move(127);
    pros::delay(1000);
    intake.move(0);

    left_drive.move(128);
    right_drive.move(128);
    pros::delay(500);
    left_drive.move(0);
    right_drive.move(0);

    pros::delay(500);

    left_drive.move(-50);
    right_drive.move(-50);
    pros::delay(100);
    left_drive.move(0);
    right_drive.move(0);

    chassis->moveToPoint(132, 36, 2000, 70);

    chassis->turnTo(132, 72, 2000, true, 60);
    blocker.set_value(true);
    pros::delay(200);
    left_drive.move(-60);
    right_drive.move(-60);
    pros::delay(1000);
    left_drive.move(0);
    right_drive.move(0);
    blocker.set_value(false);
}

void awp(lemlib::Chassis* chassis) {
    
}

void elims(lemlib::Chassis* chassis) {
    
}

void own_side(lemlib::Chassis* chassis) {
    chassis->setPose(16.3125, 22.5, 45);

    blocker.set_value(true);
    pros::delay(400);

    
    while (chassis->getPose().theta < 85) {
        left_drive.move(60);
        right_drive.move(-30);
    }
    left_drive.move(0);
    right_drive.move(20);
    pros::delay(200);
    right_drive.move(0);
    
    blocker.set_value(false);
    pros::delay(600);

    chassis->moveToPoint(36, 12, 2000, 50);
    pros::delay(200);

    chassis->turnTo(144, 12, 2000, false, 60);

    intake.move(127);
    pros::delay(1000);
    intake.move(0);

    left_drive.move(128);
    right_drive.move(128);
    pros::delay(500);
    left_drive.move(0);
    right_drive.move(0);

    pros::delay(500);

    left_drive.move(-50);
    right_drive.move(-50);
    pros::delay(100);
    left_drive.move(0);
    right_drive.move(0);

    chassis->moveToPoint(14, 36, 2000, 50);

    chassis->turnTo(14, 72, 2000, false, 60);
    blocker.set_value(true);
    intake.move(-127);
    pros::delay(200);
    left_drive.move(60);
    right_drive.move(60);
    pros::delay(800);
    left_drive.move(0);
    right_drive.move(0);
    pros::delay(1000);
    intake.move(0);
}

void own_secondary(lemlib::Chassis* chassis) {
    chassis->setPose(16.3125, 22.5, 45);

    blocker.set_value(true);
    pros::delay(400);

    
    while (chassis->getPose().theta < 85) {
        left_drive.move(60);
        right_drive.move(-30);
    }
    left_drive.move(0);
    right_drive.move(20);
    pros::delay(200);
    right_drive.move(0);
    blocker.set_value(false);
    pros::delay(200);

    chassis->moveToPoint(36, 12, 2000, 50);
    pros::delay(200);

    chassis->turnTo(144, 12, 2000, false, 60);

    intake.move(127);
    pros::delay(500);
    intake.move(0);

    left_drive.move(128);
    right_drive.move(128);
    pros::delay(500);
    left_drive.move(0);
    right_drive.move(0);

    pros::delay(500);

    left_drive.move(-50);
    right_drive.move(-50);
    pros::delay(250);
    left_drive.move(0);
    right_drive.move(0);

    chassis->moveToPoint(48, 48, 2000, 50);
    pros::delay(200);
    intake.move(-127);
    chassis->moveToPoint(48, 64, 1250, 50);
    pros::delay(200);
    left_drive.move(-50);
    right_drive.move(-50);
    pros::delay(100);
    left_drive.move(0);
    right_drive.move(0);


    chassis->turnTo(68, 64, 2000, false, 50);
    chassis->moveToPoint(68, 64, 2000, 50);
    chassis->turnTo(68, 24, 2000, false, 50);
    left_wing.set_value(true);
    pros::delay(100);
    intake.move(127);
    chassis->moveToPoint(68, 24, 2000, 80);
    left_drive.move(-50);
    right_drive.move(-50);
    pros::delay(150);
    left_drive.move(0);
    right_drive.move(0);
    intake.move(0);
}

void skills(lemlib::Chassis* chassis) {
    //chassis->setPose(14.5, 20.5, -135);
    chassis->setPose(0, 0, 0, 0);

    // Change angle to shoot
    while (chassis->getPose().theta > -25) {
        left_drive.move(-40);
    }
    left_drive.move(0);
    /*
    while (chassis->getPose().theta > -18) {
        left_drive.move(-32);
    }
    pros::delay(475);
    left_drive.move(0);
    */

    pros::delay(500);

    cata.move(127);

    // Firing break
    pros::delay(46000); // 41 sec

    cata.move(0);

    //chassis->moveToPoint(0, 48, 2000, 60);
    chassis->turnTo(-150, 75, 1000, false, 50);
    intake.move(127);
    chassis->moveToPoint(-150, 75, 1000, 80);
    pros::delay(500);

    left_drive.move(53); // turn towards goal
    pros::delay(730);
    left_drive.move(0);
    intake.move(-127);

    pros::delay(200);

    intake.move(-127);

    left_drive.move(128); // push triballs in
    right_drive.move(128);
    pros::delay(1300);
    intake.move(127);
    left_wing.set_value(true);
    blocker.set_value(true);
    pros::delay(1000);
    left_drive.move(0);
    right_drive.move(0);
    intake.move(0);

    pros::delay(500);

    left_drive.move(-90); // back up
    right_drive.move(-90);
    pros::delay(500);
    left_drive.move(0);
    right_drive.move(0);
    pros::delay(200);

    right_drive.move(40);
    pros::delay(150);
    right_drive.move(0);

    left_drive.move(128); // push triballs in
    right_drive.move(128);
    pros::delay(1500);
    left_drive.move(0);
    right_drive.move(0);
    intake.move(0);

    pros::delay(500);

    left_drive.move(-90); // back up
    right_drive.move(-90);
    pros::delay(300);
    left_drive.move(0);
    right_drive.move(0);
    pros::delay(200);

    right_drive.move(40);
    pros::delay(225);
    left_drive.move(0);

    left_drive.move(128); // push triballs in
    right_drive.move(128);
    pros::delay(1500);
    left_drive.move(0);
    right_drive.move(0);
    intake.move(0);

    pros::delay(500);

    left_drive.move(-90); // back up
    right_drive.move(-90);
    pros::delay(300);
    left_drive.move(0);
    right_drive.move(0);
    pros::delay(200);




    chassis->setPose(0, 0, 0, 0);

    //left_drive.move(-60);
    //pros::delay(500);
}
