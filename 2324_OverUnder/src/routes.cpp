#include "main.h"
#include "lemlib/api.hpp"
#include <math.h>
#include "routes.h"

ASSET(startsweep_txt);
ASSET(leftmove_txt);
ASSET(frontpush_txt);
ASSET(sixballright_txt);
ASSET(skillsend_txt);
ASSET(disruptcenter_txt);
ASSET(disruptend_txt);

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

void sixball(lemlib::Chassis* chassis) {
	chassis->setPose(13, -60, 270);
	
	// pick up triball
	intake.move(-127);
	left_drive.move(50);
	right_drive.move(50);
	pros::delay(300);
	left_drive.move(0);
	right_drive.move(0);
	pros::delay(300);

	chassis->follow(sixballright_txt, 11, 3000, false);
	pros::delay(200);
	intake.move(0);

	while (chassis->getPose().theta > 255) {
		pros::delay(10);
	}
	vert_wing.set_value(true);

	while (chassis->getPose().theta > 230) {
		pros::delay(10);
	}
	vert_wing.set_value(false);

	chassis->waitUntilDone();

	// spin for other triball
	left_drive.move(70);
	right_drive.move(20);
	pros::delay(250);
	left_drive.move(0);
	right_drive.move(0);
	pros::delay(200);

	chassis->turnToHeading(0, 750, {.maxSpeed = 80});
	chassis->waitUntilDone();
	intake.move(127);
	pros::delay(300);
	left_drive.move(127);
	right_drive.move(127);
	pros::delay(400);
	left_drive.move(0);
	right_drive.move(0);
	pros::delay(50);
	left_drive.move(-50);
	right_drive.move(-70);
	pros::delay(350);
	left_drive.move(0);
	right_drive.move(0);
	intake.move(-127);
	chassis->turnToPoint(13, -21, 750, {.maxSpeed = 90});
	chassis->moveToPoint(13, -21, 1250, {.maxSpeed = 120});
	chassis->waitUntilDone();

	left_drive.move(-70);
	right_drive.move(-70);
	pros::delay(250);
	left_drive.move(0);
	right_drive.move(0);
	chassis->turnToPoint(48, -9, 800, {.maxSpeed = 90});
	chassis->waitUntilDone();
	intake.move(127);
	pros::delay(250);

	// get first center ball
	intake.move(0);
	chassis->turnToPoint(3, -2, 1000, {.maxSpeed = 120, .minSpeed = 40});
	chassis->waitUntilDone();
	intake.move(-127);
	chassis->moveToPose(3, 4, 340, 1200, {.maxSpeed = 120, .minSpeed = 40});
	chassis->waitUntilDone();
	pros::delay(300);

	// back up to get 2nd center ball
	left_drive.move(-60);
	right_drive.move(-60);
	pros::delay(100);
	left_drive.move(0);
	right_drive.move(0);

	// turn to push all 3 in goal
	chassis->turnToHeading(90, 600, {.maxSpeed = 90});
	chassis->waitUntilDone();

	// backup to avoid hitting second ball
	left_drive.move(-80);
	right_drive.move(-80);
	pros::delay(150);
	left_drive.move(0);
	right_drive.move(0);
	left_wing.set_value(true);
	intake.move(127);
	pros::delay(200);
	
	// ram
	left_drive.move(127);
	right_drive.move(127);
	pros::delay(800);
	left_drive.move(0);
	right_drive.move(0);
	pros::delay(200);
	chassis->setPose(38, -13, chassis->getPose().theta);
	left_drive.move(-70);
	right_drive.move(-70);
	pros::delay(200);
	left_drive.move(0);
	right_drive.move(0);
	
	left_wing.set_value(false);
	pros::delay(50);

	// awp
	chassis->turnToPoint(3, -69, 700, {.maxSpeed = 90});		// was 67
	blocker.set_value(true);
	chassis->waitUntilDone();
	pros::delay(100);

	left_drive.move(127);
	right_drive.move(127);
	pros::delay(400);

	left_drive.move(0);
	right_drive.move(0);
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

void disrupt(lemlib::Chassis* chassis) {
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
	right_drive.move(127);      // move back to descore
	left_drive.move(-127);
	pros::delay(200);
	right_drive.move(0);
	left_drive.move(0);
	pros::delay(300);
	left_wing.set_value(false);

	chassis->turnToPoint(70, 24, 1000, true);   // turn towards inner corner of goal
	chassis->waitUntilDone();
	intake.move(127);
	left_drive.move(127);
	right_drive.move(50);
	pros::delay(500);
	right_drive.move(0);
	left_drive.move(0);
	pros::delay(300);
	intake.move(0);
	chassis->setPose(59, 34, chassis->getPose().theta);	// was 62


	// back up
	left_drive.move(-70);
	right_drive.move(-70);
	pros::delay(300);
	left_drive.move(0);
	right_drive.move(0);
	pros::delay(300);


	// new stuff


	// move in front of goal
	chassis->turnToHeading(270, 750, {.maxSpeed = 90});
	chassis->waitUntilDone();
	chassis->follow(disruptcenter_txt, 13, 4300, true);
	pros::delay(1000);
	blocker.set_value(true);
	intake.move(-127);
	chassis->waitUntilDone();
	pros::delay(1000);
	chassis->setPose(24, 10, chassis->getPose().theta);
	pros::delay(1400);          // camp in the center
	left_drive.move(-65);
	right_drive.move(-65);
	pros::delay(300);
	left_drive.move(0);
	right_drive.move(0);
	chassis->turnToHeading(0, 2000, {.maxSpeed = 90});

	intake.move(0);


	// turn away and leave
	chassis->follow(disruptend_txt, 11, 3600, true);
	while (chassis->getPose().x > 40 || chassis->getPose().y < 50) {
		pros::delay(10);
	}
	intake.move(127);
	pros::delay(500);
	chassis->waitUntilDone();
	intake.move(0);
}


void push(int fspd, int fdur, int bspd, int bdur, bool start_back) {
	if (start_back) {
		left_drive.move(-bspd);
		right_drive.move(-bspd);
		pros::delay(bdur);
		left_drive.move(0);
		right_drive.move(0);
		pros::delay(50);
	}

	left_drive.move(fspd);
	right_drive.move(fspd);
	pros::delay(fdur);
	left_drive.move(0);
	right_drive.move(0);

	if (!start_back) {
		pros::delay(50);
		left_drive.move(-bspd);
		right_drive.move(-bspd);
		pros::delay(bdur);
		left_drive.move(0);
		right_drive.move(0);
	}
}

void spiral(lemlib::Chassis* chassis) {
	// ONLY HAVE THIS LINE UNCOMMENTED DURING TESTING, __NOT__ ACTUAL ROUTES
	// chassis->setPose(40.5, 2, 270);
	


}


void skills(lemlib::Chassis* chassis) {
    chassis->setPose(-49, -55.25, 90);  // width front bumper to front bumper is 14.25 in
	
	while (chassis->getPose().theta > 56) {		// was 58
        left_drive.move(-40);
    }
    left_drive.move(0);
	pros::delay(150);

	cata.move(127*.9);
	pros::delay(28000);	// 22
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
	pros::delay(50);

	push(50, 200, 127, 300, false);
	left_drive.move(40);
	right_drive.move(40);
	pros::delay(200);
	left_drive.move(0);
	right_drive.move(0);
	pros::delay(50);

	chassis->turnToHeading(270, 600, {.maxSpeed = 90});

	chassis->follow(startsweep_txt, 11, 3900, false);

	while (chassis->getPose().y < -24) {
		pros::delay(10);
	}
	vert_wing.set_value(true);
	
	chassis->waitUntilDone();
	vert_wing.set_value(false);
	pros::delay(100);
	chassis->setPose(-12.5, 39.5, chassis->getPose().theta);

	intake.move(-127);
	chassis->follow(leftmove_txt, 12, 7000);

	while (chassis->getPose().x < -12 || chassis->getPose().y < 50) {
		pros::delay(10);
	}
	intake.move(127);
	cata.move(70);
	pros::delay(500);
	cata.move(0);

	chassis->waitUntilDone();
	left_wing.set_value(true);


	// second left push
	pros::delay(50);
	left_drive.move(-50);
	right_drive.move(-50);
	pros::delay(250);
	left_drive.move(0);
	right_drive.move(0);
	pros::delay(100);
	left_drive.move(127);
	right_drive.move(70);
	pros::delay(400);
	right_drive.move(127);
	pros::delay(200);
	left_drive.move(0);
	right_drive.move(0);

	intake.move(0);

	left_wing.set_value(false);
	pros::delay(200);
	chassis->setPose(61.5, 34.25, fmod(chassis->getPose().theta, 360));

	left_drive.move(-40);
	right_drive.move(-40);
	pros::delay(200);
	left_drive.move(0);
	right_drive.move(0);

	pros::delay(150);

	//chassis->turnToHeading(90, 1000, {.maxSpeed = 90});	// turn to red side for pure pursuit
	left_drive.move(-50);
	right_drive.move(0);
	pros::delay(350);
	left_drive.move(0);
	right_drive.move(0);
	pros::delay(50);

	chassis->turnToHeading(90, 500, {.maxSpeed = 90});
	chassis->waitUntilDone();
	
	intake.move(-127);
	chassis->follow(frontpush_txt, 10, 5000, false);
	
	pros::delay(600);
	vert_wing.set_value(true);
	
	chassis->waitUntilDone();

	chassis->turnToHeading(270, 400, {.maxSpeed = 90});
	chassis->waitUntilDone();

	intake.move(127);

	left_drive.move(-127);
	right_drive.move(-127);
	pros::delay(800);
	left_drive.move(0);
	right_drive.move(0);

	push(50, 300, 127, 500, false);
	intake.move(0);
	pros::delay(150);
	left_drive.move(-127);
	right_drive.move(-30);
	pros::delay(400);		// TODO: can maybe cut down
	right_drive.move(0);
	left_drive.move(0);

	pros::delay(150);		// TODO: can maybe cut down
	// spiral(chassis);

	// TODO: For the second left push have it a little more away from the wall and change
	// the corresponding position reset to not mess up the rest of the route


	chassis->setPose(40.5, 2, chassis->getPose().theta);

	intake.move(-127);
	// back up
	chassis->moveToPoint(14, 2, 2000, {.forwards = true, .maxSpeed = 80});
	pros::delay(100);
	vert_wing.set_value(false);
	chassis->waitUntilDone();

	chassis->turnToHeading(0, 2000, {.maxSpeed = 70});
	intake.move(127);
	chassis->moveToPoint(chassis->getPose().x, -10, 2500, {.forwards = false, .maxSpeed = 80});
	chassis->waitUntilDone();
	intake.move(0);

	chassis->turnToHeading(270, 2000, {.maxSpeed = 70});
	chassis->waitUntilDone();
	// back up a bit
	left_drive.move(70);
	right_drive.move(70);
	pros::delay(300);
	left_drive.move(0);
	right_drive.move(0);
	vert_wing.set_value(true);

	push(60, 250, 127, 750, true);
	intake.move(0.6 * 127);
	pros::delay(300);
	intake.move(0);
	
	left_drive.move(-127);
	right_drive.move(-127);
	pros::delay(400);
	left_drive.move(0);
	right_drive.move(0);
	pros::delay(300);

	chassis->setPose(40.5, -13.25, chassis->getPose().theta);

	chassis->moveToPoint(40.5-24, -13.25, 2500, {.maxSpeed = 80});
	chassis->waitUntilDone();
	vert_wing.set_value(false);
	chassis->turnToHeading(0, 1250, {.maxSpeed = 70});
	chassis->moveToPoint(chassis->getPose().x, -26, 2000, {.forwards = false, .maxSpeed = 70});
	chassis->waitUntilDone();

	vert_wing.set_value(true);
	right_drive.move(2);
	left_drive.move(-55);

	while (chassis->getPose().theta > -70) {
		pros::delay(10);
	}
	right_drive.move(0);
	left_drive.move(0);
	pros::delay(300);

	chassis->follow(skillsend_txt, 10, 2500, false);		// was 3500
	
	while (chassis->getPose().theta > -117) {		// was 135
		pros::delay(10);
	}
	vert_wing.set_value(false);
	chassis->waitUntilDone();

	left_drive.move(70);
	right_drive.move(70);
	pros::delay(250);
	left_drive.move(0);
	right_drive.move(0);
	pros::delay(50);
	left_drive.move(-127);
	right_drive.move(-127);
	pros::delay(500);
	left_drive.move(0);
	right_drive.move(0);

	intake.move(127);
	left_drive.move(90);
	right_drive.move(60);
	pros::delay(300);
	left_drive.move(0);
	right_drive.move(0);

	// 3rd push
	left_drive.move(-127);
	right_drive.move(-127);
	pros::delay(300);
	left_drive.move(0);
	right_drive.move(0);

	left_drive.move(127);
	right_drive.move(127);
	pros::delay(300);
	left_drive.move(0);
	right_drive.move(0);
}
