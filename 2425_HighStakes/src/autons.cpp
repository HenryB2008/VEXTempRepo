#include "main.cpp"
#include "autons.h"

ASSET(IntakeRedRing_txt);
ASSET(left_five_txt);
ASSET(cross_field_first_txt);
ASSET(right_five_txt);
ASSET(cross_field_second_txt);

void skills()
{
    int start = millis();

    chassis.setPose(-160, 0, 90);

    // back up into wall stake and score
    mogo.toggle();
    left_motors.move(-40);
    right_motors.move(-40);
    delay(100);
    left_motors.move(0);
    right_motors.move(0);
    IntakeMotor1.move(-127);
    delay(500);
    IntakeMotor1.move(0);

    // left 5 rings
    chassis.moveToPoint(-145, 0, 1000);
    mogo.toggle();
    delay(100);
    chassis.turnToHeading(180, 5000);
    chassis.waitUntilDone();
    delay(200);
    left_motors.move(-80);
    right_motors.move(-80);
    delay(500);
    left_motors.move(0);
    right_motors.move(0);
    delay(500);
    mogo.toggle();
    delay(500);
    chassis.turnToHeading(90, 5000);
    chassis.waitUntilDone();

    IntakeMotor1.move(-127);
    chassis.follow(left_five_txt, 9, 7000); // speed is ~50
    chassis.waitUntilDone();
    delay(100);
    /*
    IntakeMotor1.move(0);                       // heading ~200 at this point
    chassis.turnToHeading(160, 3000);
    left_motors.move(-90);
    right_motors.move(-90);
    delay(1000);
    mogo.toggle();
    left_motors.move(0);                        // back up into corner
    right_motors.move(0);
    delay(100);
    left_motors.move(40);                       // move up again
    right_motors.move(40);
    delay(200);
    left_motors.move(0);
    right_motors.move(0);


    /*


    // travel to right 5
    chassis.setPose(-155, 153, 170);
    chassis.follow(cross_field_first_txt, 9, 3000, false);  // false for backwards
    chassis.waitUntilDone();


    // right 5 rings
    mogo.toggle();
    chassis.turnToHeading(90, 3000);
    IntakeMotor1.move(-127);
    chassis.follow(right_five_txt, 9, 7000);
    chassis.waitUntilDone();
    delay(100);
    IntakeMotor1.move(0);
    chassis.turnToHeading(20, 3000);
    left_motors.move(-90);
    right_motors.move(-90);
    delay(1000);
    mogo.toggle();
    left_motors.move(0);                        // back up into corner
    right_motors.move(0);


    // reset odom
    left_motors.move(40);
    right_motors.move(40);
    delay(100);
    left_motors.move(0);
    right_motors.move(0);
    chassis.turnToHeading(90, 3000);
    left_motors.move(-40);
    right_motors.move(-40);
    delay(300);
    left_motors.move(0);
    right_motors.move(0);
    chassis.setPose(-162, -120, 90);


    /*
        TODO:
        get a bunch of rings
        score on mogo and push mogo to far corner
        push remaining mogo into last corner
    *

    // more red rings + mogo
    IntakeMotor1.move(-90);
    chassis.follow(cross_field_second_txt, 11, 5000);
    while (chassis.getPose().x < 69 || chassis.getPose().y < -110)
    {
        delay(10);
    }
    IntakeMotor1.move(0); // stop motor as soon as 2 rings are picked up
    chassis.waitUntilDone();
    delay(200);
    chassis.turnToHeading(195, 2000);
    chassis.waitUntilDone();
    delay(200);
    left_motors.move(-20);
    right_motors.move(-20);
    delay(100);
    left_motors.move(0);
    right_motors.move(0);
    delay(100);
    mogo.toggle();
    delay(200);
    IntakeMotor1.move(-127);
    delay(100);
*/

    lcd::print(0, "Time: %d", millis() - start);
}