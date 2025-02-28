#include "..\include\autons\skills.h"

void skills(){
    colorSortOn = false;
    chassis.setPose(-59.502, -0.181, 90); 
    intakeMotor1.move(-127);
    pros::delay(700);
    intakeMotor1.brake();
    chassis.moveToPoint(-47.122, -0.181, 950, {.maxSpeed = 78}, false);
    chassis.turnToHeading(180, 1000, {}, false);
    chassis.moveToPoint(-48.495, 19.5, 900, {.forwards = false, .maxSpeed = 75});
    chassis.waitUntil(17.1);
    mogo.toggle();
    
    intakeMotor1.move(-127);
    chassis.turnToHeading(79.6, 800, {}, false); 

    chassis.moveToPoint(-27.456, 22.300, 800, {}, false); 
    chassis.turnToHeading(38.2, 800, {}, false);
    chassis.moveToPoint(-3.264, 52.103, 1200, {}, false);
    chassis.moveToPoint(-7.12, 47.527, 600, {.forwards = false}, false);
    chassis.turnToHeading(-87, 800, {}, false);
    chassis.moveToPoint(-56.65, 49.8, 2800, {.maxSpeed = 80}, false);

    
    chassis.turnToHeading(40, 800, {}, false); 
    chassis.moveToPoint(-47.    , 58.985, 800, {}, false); 
    
    chassis.turnToHeading(111, 900, {}, false );
    pros::delay(100);

    
    
    chassis.moveToPose(-54.374, 58.6129064, 116.565, 775, {.forwards = false, .lead = 0.5, .maxSpeed = 50}, false);
    pros::delay(200);

    //chassis.moveToPoint(chassis.getPose().x - (5 * sin(chassis.getPose(true).theta)), chassis.getPose().y - (5 * cos(chassis.getPose(true).theta)), 800, {.forwards = false}, false);
    mogo.toggle(); 
    
        //seconnd mogo
    chassis.moveToPose(-43.757, -3.847, 178.424, 2200, {}, false);
    chassis.turnToHeading(1, 1100, {}, false);
    chassis.moveToPoint(-41.92, -21.2, 800, {.forwards = false, .maxSpeed = 75});
    chassis.waitUntil(14);
    mogo.toggle();
    chassis.waitUntilDone(); 
    chassis.turnToHeading(90.5, 800, {}, false);
    chassis.moveToPoint(-22.065, -24.297, 800, {}, false);
    
    chassis.turnToHeading(158, 800, {}, false);
    chassis.moveToPoint(-14.6710, -47.702, 800, {}, false);
    chassis.turnToHeading(265, 800, {}, false);

    chassis.moveToPoint(-51.2, -46.7, 1600, {.maxSpeed = 80}, false);
    chassis.moveToPoint(-35, -45, 800, {.forwards = false,  }, false); 
    chassis.turnToHeading(220, 800, {}, false);
    chassis.moveToPoint(-43.208893, -57.082047, 800, {}, false);
    chassis.turnToHeading(68, 800, {}, false);
    chassis.moveToPoint(chassis.getPose().x - (7 * sin(chassis.getPose(true).theta)), chassis.getPose().y - (7 * cos(chassis.getPose(true).theta)), 800, {.forwards = false}, false);
    mogo.toggle(); 
    




    /*
    chassis.setPose(-54.668, 59.708, 114.135620);
    
    pros::delay(40);

    
    chassis.moveToPose(-42.870682,-4.858637, 177.877, 24000, {}, false);    
    chassis.turnToHeading(358, 1000, {}, false);
    chassis.moveToPoint(-42.079, -21.303, 800, {.forwards = false});
    chassis.waitUntil(13);
    mogo.toggle(); 
    chassis.waitUntilDone();
    chassis.turnToHeading(446, 800, {}, false);

    */

}