#include "main.h"
#include "lemlib/api.hpp"

void opposite_side(lemlib::Chassis chassis) {
    // cata.move(127);
    // pros::delay(400);
    // cata.move(0);

    // cata.move(15*127/100);

    // pros::delay(5000);

    chassis.setPose(0, 0, 0);
    chassis.moveTo(0, -12, 1000, 40);
    right_wing.set_value(false);
    pros::delay(100);
    chassis.moveTo(0, 1, 1000, 40);         // was 0, 3

    // TODO: COPY FROM GITHUB BEFORE USING THIS

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

void awp(lemlib::Chassis chassis) {
    int start = pros::millis();
    chassis.setPose(0, 0, 0);
    chassis.moveTo(0, -12, 1000, 30);
    right_wing.set_value(false);
    pros::delay(100);
    chassis.moveTo(0, 1, 1000, 30);
    right_wing.set_value(true);
    
    chassis.setPose(129.5, 23.5, 45);

    chassis.moveTo(84, 48, 4000, 50);   // move to center
    pros::delay(300);
    chassis.turnTo(76, 120, 2000, true, 30);   // turn to face goal

    // // square up against barrier
    // right_drive.move(-30);
    // left_drive.move(-30);
    // pros::delay(1400);
    // right_drive.move(0);
    // left_drive.move(0);

    cata.move(127);
    pros::delay(500);
    cata.move(0);   // end firing triball
    pros::delay(500);

    // // back up
    // right_drive.move(50);
    // left_drive.move(50);
    // pros::delay(300);
    // right_drive.move(0);
    // left_drive.move(0);
    // pros::delay(100);

    right_drive.move(70);
    left_drive.move(-70);
    while (chassis.getPose().theta > 95) {
        pros::delay(25);
    }
    right_drive.move(0);
    left_drive.move(0);

    chassis.moveTo(106, chassis.getPose().y, 2000, 80);   // straight right movement towards barrier
    // was 106, if this doesn't work, then add some back left wheel turn to the final turn

    right_drive.move(40);
    left_drive.move(-40);
    while (chassis.getPose().theta > 10) {
        pros::delay(5);
    }
    right_drive.move(0);
    left_drive.move(0);

    right_drive.move(30);
    left_drive.move(60);    // was 40
    pros::delay(600);       // was 300, 200 was too low (too far back)
    right_drive.move(0);
    left_drive.move(0);

    right_drive.move(40);
    left_drive.move(40);
    pros::delay(500);
    left_drive.move(0);
    pros::delay(500);
    right_drive.move(0);
    left_drive.move(0);


    left_drive.move(-30);
    pros::delay(250);
    left_drive.move(0);

    right_wing.set_value(false);

    pros::delay(200);
    right_drive.move(35);
    pros::delay(300);
    right_drive.move(0);

    pros::lcd::print(0, "Time: %d", pros::millis() - start);
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
    right_drive.move(57);
    left_drive.move(-23);
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
    chassis.moveTo(0, -20, 1500, 100);
    pros::delay(500);
    chassis.setPose(0, 0, 0);
    chassis.moveTo(0, 4, 1000, 80);
    chassis.setPose(0, 0, 0);
    chassis.turnTo(43, 0, 3000, false, 40);
    pros::delay(500);
    chassis.moveTo(43, 0, 3000, 40);
    
    right_drive.move(60);
    left_drive.move(-20);
    right_wing.set_value(false);
    pros::delay(1000);
    right_drive.move(0);
    left_drive.move(0);
    
    
    chassis.setPose(0, 0, 0);
    chassis.moveTo(0, 15, 1000, 40);
    //right_drive.move(80);
    //pros::delay(600);
    //right_drive.move(0);
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
    // pros::delay(35000);
    // master.rumble("-");
    // pros::delay(5000);

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
