#include "main.h"
#include "lemlib/api.hpp"

void opposite_side(lemlib::Chassis chassis) {
    chassis.setPose(129.4375, 24.6875, -45);

    blocker.set_value(false);
    pros::delay(400);

    while (chassis.getPose().theta > -85) {
        right_drive.move(60);
    }
    right_drive.move(0);
    
    blocker.set_value(true);
    pros::delay(600);

    chassis.moveTo(108, 10, 2000, 50);
    pros::delay(200);

    chassis.turnTo(0, 10, 2000, false, 60);

    intake.move(127);
    pros::delay(1000);
    intake.move(0);

    left_drive.move(50);
    right_drive.move(50);
    pros::delay(500);
    left_drive.move(0);
    right_drive.move(0);

    pros::delay(500);

    left_drive.move(-50);
    right_drive.move(-50);
    pros::delay(100);
    left_drive.move(0);
    right_drive.move(0);

    chassis.moveTo(132, 36, 2000, 70);

    chassis.turnTo(132, 72, 2000, true, 60);
    blocker.set_value(false);
    pros::delay(200);
    left_drive.move(-60);
    right_drive.move(-60);
    pros::delay(800);
    left_drive.move(0);
    right_drive.move(0);
    blocker.set_value(true);
}

void awp(lemlib::Chassis chassis) {
    
}

void elims(lemlib::Chassis chassis) {
    
}

void own_side(lemlib::Chassis chassis) {
    chassis.setPose(16.3125, 22.5, 45);

    blocker.set_value(false);
    pros::delay(400);

    
    while (chassis.getPose().theta < 85) {
        left_drive.move(60);
        right_drive.move(-30);
    }
    left_drive.move(0);
    right_drive.move(20);
    pros::delay(200);
    right_drive.move(0);
    
    blocker.set_value(true);
    pros::delay(600);

    chassis.moveTo(36, 12, 2000, 50);
    pros::delay(200);

    chassis.turnTo(144, 12, 2000, false, 60);

    intake.move(127);
    pros::delay(1000);
    intake.move(0);

    left_drive.move(50);
    right_drive.move(50);
    pros::delay(500);
    left_drive.move(0);
    right_drive.move(0);

    pros::delay(500);

    left_drive.move(-50);
    right_drive.move(-50);
    pros::delay(100);
    left_drive.move(0);
    right_drive.move(0);

    chassis.moveTo(14, 36, 2000, 50);

    chassis.turnTo(14, 72, 2000, false, 60);
    blocker.set_value(false);
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

void own_secondary(lemlib::Chassis chassis) {
    chassis.setPose(16.3125, 22.5, 45);

    blocker.set_value(false);
    pros::delay(400);

    
    while (chassis.getPose().theta < 85) {
        left_drive.move(60);
        right_drive.move(-30);
    }
    left_drive.move(0);
    right_drive.move(20);
    pros::delay(200);
    right_drive.move(0);
    blocker.set_value(true);
    pros::delay(200);

    chassis.moveTo(36, 12, 2000, 50);
    pros::delay(200);

    chassis.turnTo(144, 12, 2000, false, 60);

    intake.move(127);
    pros::delay(500);
    intake.move(0);

    left_drive.move(50);
    right_drive.move(50);
    pros::delay(500);
    left_drive.move(0);
    right_drive.move(0);

    pros::delay(500);

    left_drive.move(-50);
    right_drive.move(-50);
    pros::delay(250);
    left_drive.move(0);
    right_drive.move(0);

    chassis.moveTo(48, 48, 2000, 50);
    pros::delay(200);
    intake.move(-127);
    chassis.moveTo(48, 64, 1250, 50);
    pros::delay(200);
    left_drive.move(-50);
    right_drive.move(-50);
    pros::delay(100);
    left_drive.move(0);
    right_drive.move(0);


    chassis.turnTo(68, 64, 2000, false, 50);
    chassis.moveTo(68, 64, 2000, 50);
    chassis.turnTo(68, 24, 2000, false, 50);
    left_wing.set_value(false);
    pros::delay(100);
    intake.move(127);
    chassis.moveTo(68, 24, 2000, 80);
    left_drive.move(-50);
    right_drive.move(-50);
    pros::delay(150);
    left_drive.move(0);
    right_drive.move(0);
    intake.move(0);
}

void skills(lemlib::Chassis chassis) {
    chassis.setPose(14.5, 20.5, -135);

    // Change angle to shoot
    left_drive.move(-35);
    pros::delay(475);
    left_drive.move(0);

    pros::delay(1000);

    cata.move(127);

    // Firing break
    pros::delay(35000);
    // master.rumble("-");
    pros::delay(12000);

    cata.move(0);

    chassis.turnTo(60, 48, 800, true, 40);
    chassis.moveTo(60, 48, 1000, 70);
    pros::delay(500);
    // chassis.turnTo()
    // left_wing.set_value(false);
    // right_wing.set_value(false);
    chassis.turnTo(60, 120, 1000, false, 50);   // TODO
    pros::delay(500);

    int push_speed = 95;        // TODO: this was 80 on the last run but maybe didnt have enough push power

    left_wing.set_value(false);
    right_wing.set_value(false);
    left_drive.move(85);
    right_drive.move(85);
    pros::delay(1200);
    right_drive.move(push_speed);
    left_drive.move(push_speed);
    pros::delay(1100);      // was 1200 - 1322
    left_drive.move(0);
    right_drive.move(0);

    left_drive.move(-push_speed);
    right_drive.move(-push_speed);
    pros::delay(500);
    left_drive.move(0);
    right_drive.move(0);

    left_drive.move(40);
    pros::delay(500);
    right_drive.move(0);

    right_drive.move(push_speed);
    left_drive.move(push_speed);        // added this and next
    pros::delay(300);
    left_drive.move(-55);
    pros::delay(500);
    left_drive.move(push_speed);
    pros::delay(600);
    left_drive.move(0);
    right_drive.move(0);

    left_drive.move(-push_speed);
    right_drive.move(-push_speed);
    pros::delay(800);
    left_drive.move(0);
    right_drive.move(0);

    // left_drive.move(40);
    // pros::delay(400);
    // left_drive.move(0);

    // left_drive.move(push_speed);
    // right_drive.move(push_speed);
    // pros::delay(1000);
    // left_drive.move(0);
    // right_drive.move(0);

    // left_drive.move(-push_speed);
    // right_drive.move(-push_speed);
    // pros::delay(500);
    // left_drive.move(0);
    // right_drive.move(0);
}
