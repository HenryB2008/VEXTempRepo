#include "auton.h"
#include "drive.h"
#include "path_builder.h"

// TODO: fix overshooting

namespace Auton {
    // TOOD: fix point
    void pointToAllianceGoal() {
        Turn( ALLIANCE_GOAL, 1.5_s)
            .withTurnGains({0.02, 0.0, 0.002})
            .withTurnMax(0.5)
            .execute(FORWARD);
    }

    // TODO: fix point
    void pointToEnemyGoal() {
        Turn( ENEMY_GOAL, 1.5_s )
            .withTurnGains({0.02, 0.0, 0.002})
            .withTurnMax(0.5)
            .execute(FORWARD);
    }

    void AUTON_RIGHT_rollerAndShoot() {

    }

    void AUTON_LEFT_rollerAndShoot() {
        // Start right in front of the roller
        Odometry::setPos( { 1_ft + 1.5_in, 2_ft + 8.75_in, 0_deg} );

        // Turn flywheel on
        flywheel.runVoltage(9000);

        // Continually back up slightly
        Drive::arcade(-0.4, 0);

        // Run the roller mechanism for a timed period
        intake.runTimed(12000, 800);

        // Stop backing up and go forward
        Drive::timedForward(0.3, 400);

        // Point towards the alliance goal
        Drive::timedTurn(-0.25, 300);

        pros::delay(2000);

        // Run the indexer to shoot all of the preloaded discs
        indexer.runTimed(12000, 450);
        pros::delay(2150);
        indexer.runTimed(12000, 2000);

        // Turn off the flywheel
        flywheel.runVoltage(0);
    }

    void SKILLS() {
        
        // Start right in front of the roller
        Odometry::setPos( { 1_ft + 1.5_in, 2_ft + 8.75_in, 0_deg} );

        // Turn flywheel on
        flywheel.runVoltage(9000);

        // Continually back up slightly
        Drive::arcade(-0.4, 0);

        // Run the roller mechanism for a timed period
        intake.runTimed(12000, 800);

        // Stop backing up and go forward
        Drive::timedForward(0.3, 400);

        // Point towards the alliance goal
        Drive::timedTurn(-0.25, 300);

        pros::delay(2000);

        // Run the indexer to shoot all of the preloaded discs
        indexer.runTimed(12000, 450);
        pros::delay(2150);
        intake.runVoltage(12000);
        indexer.runTimed(12000, 2000);

        // To 3-stack
        PathBuilder()
            .addPath( 
                Movement({3_ft, 3_ft}, 3_s, FORWARD)
                    .withDistanceMax(0.4)
            )
            .execute();

        flywheel.runVoltage(7000);

        Turn( ALLIANCE_GOAL, 2_s)
            .withTurnGains({0.025,0,0.0002})
            .executeToPoint(ALLIANCE_GOAL, FORWARD);

        // Shoot 3 stack
        indexer.runTimed(12000, 450);
        pros::delay(1500);
        indexer.runTimed(12000, 2000);

        // Turn to roller position
        Turn( 90_deg, 5_s)
            .withTurnGains({0.01,0,0.0002})
            .withTurnMax(0.6)
            .execute(FORWARD);

        // Continually back up slightly
        Drive::arcade(-0.4, 0);

        pros::delay(2000);

        
        // Push out a bit
        Drive::arcade(0.5, 0);

        pros::delay(100);
        

        
        intake.runVoltage(12000);
        Turn({5_ft, 3_ft}, 3_s)
            .withTurnGains({0.01,0,0.002})
            .execute(FORWARD);

        angleChanger.on();

        flywheel.runVoltage(7500);

        PathBuilder()
            .addPath(
                Movement({5_ft, 3_ft}, 3_s, FORWARD)
            )
            .addPath(
                Movement({8_ft, 6_ft}, 3_s, FORWARD)
                    .withDistGains({0.07, 0, 0.0002})
                    .withHeadingGains({0.08, 0, 0.002})
            )
            .addCallback(
                {7_ft, 5_ft}, []() {intake.runVoltage(12000);}
            )
            .execute();

        Turn( ALLIANCE_GOAL, 2_s)
            .withTurnGains({0.011,0,0.0002})
            .withTurnMax(0.6)
            .executeToPoint(ALLIANCE_GOAL, FORWARD);

        indexer.runTimed(12000, 450);
        pros::delay(1500);
        indexer.runTimed(12000, 2000);

    }
}