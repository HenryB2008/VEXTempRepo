#include "main.h"
#include "lemlib/api.hpp"

void opposite_side(lemlib::Chassis chassis) {
    // cata.move(127);
    // pros::delay(400);
    // cata.move(0);

    // cata.move(15*127/100);

    // pros::delay(5000);

    chassis.setPose(0, 0, 0);
    // pros::delay(500);
    chassis.moveTo(0, -12, 1000, 40);
    right_wing.set_value(false);
    pros::delay(500);
    chassis.moveTo(0, 1, 1000, 40);         // was 0, 3
    pros::delay(500);
    right_wing.set_value(true);
    pros::delay(500);
    // chassis.moveTo(0, -12, 1000, 40);
    chassis.setPose(0, 0, 0);
    chassis.moveTo(0, -8, 1000, 50); // added
    chassis.turnTo(30, 50, 1000, false, 80);
    pros::delay(200);
    chassis.setPose(0, 0, 0);
    chassis.moveTo(0, -12, 1000, 40);       // 1547 was -36
    cata.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
    cata.move(-127);
    pros::delay(750);
    cata.move(0);
    chassis.moveTo(0, -50, 1500, 80);
    pros::delay(600);
    chassis.moveTo(-36, -8, 2000, 70); // -36, -6
    // wings.set_value(false);

    // final turn
    chassis.setPose(0, 0, 0);
    chassis.turnTo(10, 50, 1000, false, 80);
    chassis.moveTo(10, 50, 500, 35);
    right_wing.set_value(false);
    chassis.setPose(0, 0, 0);
    chassis.moveTo(0, 6, 500, 35);
    right_drive.move(35);       // we were tweaking this and the movement above to try to get it to line up without pushing back (i.e. riding up and pushing back). trying to drive right forward when left was back just a bit from the barrier
    pros::delay(300);
    right_drive.move(0);

}

void own_side(lemlib::Chassis chassis) {
    chassis.setPose(0, 0, 0);
    // while (cata.get_positions()[0] < 1600) {
    //     cata.move(127);
    //     pros::delay(50);
    // }
    // cata.move(15*127/100);

    chassis.moveTo(0, -18, 1000, 40);
    pros::delay(500);


    chassis.setPose(0, 0, 45);
    // chassis.turnTo(2, 40, 1000, false, 80);
    right_drive.move(60);
    left_drive.move(-20);
    while (true) {
        if (chassis.getPose().theta < 15) {
            break;
        }
        pros::delay(25);
    }
    right_drive.move(0);
    left_drive.move(0);



    pros::delay(500);
    cata.move(-127);
    pros::delay(500);
    cata.move(0);
    chassis.setPose(0, 0, 0);
    chassis.moveTo(0, -18, 1500, 100);
    pros::delay(500);
    chassis.setPose(0, 0, 0);
    chassis.moveTo(0, 4, 1000, 80);
    chassis.setPose(0, 0, 0);
    chassis.turnTo(42, 0, 3000, false, 50);
    pros::delay(500);
    chassis.moveTo(42, 0, 3000, 50);
    
    right_wing.set_value(false);
    right_drive.move(60);
    left_drive.move(-15);
    pros::delay(1000);
    right_drive.move(0);
    left_drive.move(0);
    
    
    // chassis.turnTo(47, 25, 1000, false, 60);
    chassis.setPose(0, 0, 0);
    chassis.moveTo(0, 15, 1000, 60);
    right_drive.move(80);
    pros::delay(600);
    right_drive.move(0);


    //chassis.turnTo(-10, 0, 1000, 40);
    //chassis.moveTo(0, -20, 1000, 40);
    //pros::delay(500);
    //chassis.moveTo(0, 5, 1000, 40);

    // chassis.
}