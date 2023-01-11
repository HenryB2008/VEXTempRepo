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

    void AUTON_rollerAndShoot() {
        // Start right in front of the roller
        Odometry::setPos( { 1_ft + 1.5_in, 2_ft + 8.75_in, 0_deg} );

        // Turn flywheel on
        flywheel.runVoltage(12000);

        // Continually back up slightly
        Drive::arcade(-0.4, 0);

        pros::delay(200);

        Drive::arcade(0,0);

        // Run the roller mechanism for a timed period
        intake.runTimed(12000, 600);

        // Stop backing up and go forward
        Drive::timedForward(0.3, 400);

        // Point towards the alliance goal
        Drive::timedTurn(-0.25, 300);

        // Run the flywheel at slightly lower power
        flywheel.runVoltage(11000);

        pros::delay(2150);

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
        flywheel.runVoltage(12000);

        // Continually back up slightly
        Drive::arcade(-0.4, 0);

        // Run the roller mechanism for a timed period
        intake.runTimed(12000, 800);

        // Stop backing up and go forward
        Drive::timedForward(0.3, 400);

        // Point towards the alliance goal
        Drive::timedTurn(-0.25, 300);

        // Run the flywheel at slightly lower power
        flywheel.runVoltage(11000);

        pros::delay(2150);

        // Run the indexer to shoot all of the preloaded discs
        indexer.runTimed(12000, 450);
        pros::delay(2150);
        indexer.runTimed(12000, 2000);

        PathBuilder()
            .addPath(
                Movement( {2_ft + 8_in, 2.5_ft}, 3_s, FORWARD)
            )
            .execute();
        
        Turn(90_deg, 1.5_s)
            .withTurnGains({0.01,0,0.002})
            .execute(FORWARD);

         // Continually back up slightly
        Drive::arcade(-0.4, 0);

        pros::delay(1000);

        // Run the roller mechanism for a timed period
        intake.runTimed(12000, 600);

        // Push out a bit
        Drive::arcade(0.4, 0);

        pros::delay(300);

        intake.runVoltage(12000);
        Turn({5_ft, 3_ft}, 3_s)
            .withTurnGains({0.01,0,0.002})
            .execute(FORWARD);

        PathBuilder()
            .addPath(
                Movement({5_ft, 3_ft}, 3_s, FORWARD)
            )
            .addPath(
                Movement({7_ft, 5_ft}, 3_s, FORWARD)
                    .withDistGains({0.06, 0, 0})
                    .withHeadingGains({0.08, 0, 0.002})
            )

        /*

        // Pick up 3-stack
        // When we appraoach the point, run the intake and start preparing the flywheel
        PathBuilder()
            .addPath(
                Movement( {3_ft, 3_ft}, 3_s, FORWARD)
            )
            .addCallback(
                { 3_ft, 3_ft },
                [](){ intake.runVoltage(12000); flywheel.runVoltage(10000); },
                10_in
            )
            .execute();
        
        // Turn toward the goal
        Turn( ALLIANCE_GOAL, 2_s)
            .withTurnGains({0.05,0,0.0002})
            .execute(FORWARD);

        // Run the indexer to shoot all three discs inputted
        indexer.runTimed(12000, 450);
        pros::delay(2150);
        indexer.runTimed(12000, 2000);       

        */

    }
}