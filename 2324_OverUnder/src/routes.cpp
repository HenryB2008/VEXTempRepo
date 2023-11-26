#include "main.h"
#include "lemlib/api.hpp"

void opposite_side(lemlib::Chassis chassis) {
    // cata.move(127);
    // pros::delay(400);
    // cata.move(0);

    cata.move(15*127/100);

    // pros::delay(5000);

    chassis.setPose(0, 0, 0);
    // pros::delay(500);
    chassis.moveTo(0, -12, 1000, 40);
    load_arm.set_value(false);
    pros::delay(500);
    chassis.moveTo(0, 3, 1000, 40);
    pros::delay(500);
    load_arm.set_value(true);
    pros::delay(500);
    // chassis.moveTo(0, -12, 1000, 40);
    chassis.setPose(0, 0, 0);
    chassis.turnTo(20, 50, 1000, false, 80);
    pros::delay(200);
    chassis.setPose(0, 0, 0);
    chassis.moveTo(0, -36, 1000, 40);
    cata.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
    cata.move(-127);
    pros::delay(750);
    cata.move(0);
    chassis.moveTo(0, -50, 1500, 80);
    pros::delay(600);
    load_arm.set_value(false);
    chassis.moveTo(-36, -8, 3000, 70); // -36, -6
    // wings.set_value(false);

    // final turn
    chassis.setPose(0, 0, 0);
    chassis.turnTo(10, 50, 1000, false, 80);
    chassis.moveTo(10, 50, 500, 100);

}

void own_side(lemlib::Chassis chassis) {
    chassis.setPose(0, 0, 0);
    while (cata.get_positions()[0] < 1500) {
        cata.move(127);
        pros::delay(50);
    }
    cata.move(15*127/100);

    chassis.moveTo(0, -18, 1000, 40);
    pros::delay(500);
    chassis.turnTo(-20, 30, 1000, false, 80);
    chassis.moveTo(20, -30, 1000, 60);
    cata.move(-127);
    pros::delay(500);
    chassis.turnTo(-10, 0, 1000, 40);
    chassis.moveTo(0, -20, 1000, 40);
    //pros::delay(500);
    //chassis.moveTo(0, 5, 1000, 40);

    // chassis.
}