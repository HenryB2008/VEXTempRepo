#include "auton.h"

// TODO: fix overshooting

namespace Auton {
    // TOOD: fix point
    void pointToAllianceGoal() {
        Turn(ALLIANCE_GOAL, 1.5_s)
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
        // Turn flywheel on
        flywheel.runVoltage(12000);

        // Start right in front of the roller
        Odometry::setPos( { 9_ft, 11_ft, 90_deg} );

        // Back up to roller
        Drive::timedForward(0.5, 200);

        // TODO: rotate roller
        
        // Go back to where we were (start pos)
        Drive::timedForward(-0.5, 200);

        Turn( { 7_ft, 9_ft }, 3_s )
            .execute(FORWARD);

        PathBuilder()
            .addPath(
                Movement( { 7_ft, 9_ft }, 3_s, FORWARD )
            )
            .execute();

        pointToAllianceGoal();

        // Run indexer
        // TODO: fix this
        indexer.runTimed(12000, 2000);

        // Turn to 3, 5

        intake.runVoltage(12000);

        Turn( {3_ft, 5_ft}, 2_s)
            .execute(FORWARD);

        PathBuilder()
            .addPath(
                Movement( {3_ft, 5_ft}, 3_s, FORWARD)
            )

        pointToAllianceGoal();

        // Run indexer
        // TODO: fix this
        indexer.runTimed(12000, 3000);

        flywheel.runVoltage(0);
    }

    void AUTON_LEFT_crossMap() {

        // Start right in front of the roller
        Odometry::setPos( { 1_ft, 3_ft, 0_deg} );

        // Turn flywheel on
        // TODO: tweak power
        flywheel.runVoltage(12000);

        // TODO: Back up into the 
        // * timed movement here *
        // Will end up around { .5_ft, 3_ft }

        PathBuilder()
            .addPath(
                Movement( { 5_ft, 6_ft }, 3_s, FORWARD )
            )
            .execute();

        Turn( ALLIANCE_GOAL, 2_s )
            .execute(FORWARD);

        // TODO: Shoot all 3 discs
        // Power feeder here

        Turn( 0_deg, 2_s )
            .execute(FORWARD);

        PathBuilder()
            .addPath(
                Movement( { 4_ft, 6_ft }, 3_s, REVERSE )
            )
            .execute();


        // Turn to disc line
        Turn( { 7_ft, 9_ft }, 3_s )
            .execute(FORWARD);

        // Collect discs
        // TODO: Turn intake on
        PathBuilder()
            .addPath(
                Movement( { 7_ft, 9_ft }, 3_s, FORWARD )
            )
            .execute();

        Turn( ALLIANCE_GOAL, 2_s )
            .execute(FORWARD);

        // TODO: Shoot all 3 discs
        // Power feeder here

        Turn( { 9_ft, 11_ft }, 3_s )
            .execute(REVERSE);
        
        PathBuilder()
            .addPath(
                Movement( { 9_ft, 11_ft }, 3_s, REVERSE )
            )
            .execute();

        Turn( 270_deg, 2_s)
            .execute(REVERSE);

        // Back up for a set amount of time and move the roller
        // TODO: Add movement here
    }
}