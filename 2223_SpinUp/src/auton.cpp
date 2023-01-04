#include "auton.h"
#include "drive.h"

// TODO: fix overshooting

namespace Auton {
    // TOOD: fix point
    void pointToAllianceGoal() {
        //Turn(ALLIANCE_GOAL, 1.5_s)
        Turn({ 10.25_ft, 1.5_ft }, 1.5_s)
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
        Odometry::setPos( { 9_ft, 11_ft, 270_deg} );

        Turn( {7_ft, 9_ft}, 2_s)
            .execute(FORWARD);

        intake.runVoltage(12000);

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


        Turn( {3_ft, 5_ft}, 2_s)
            .execute(FORWARD);

        PathBuilder()
            .addPath(
                Movement( {3_ft, 5_ft}, 3_s, FORWARD)
            )
            .execute();

        pointToAllianceGoal();

        // Run indexer
        // TODO: fix this
        indexer.runTimed(12000, 3000);

        flywheel.runVoltage(0);
    }

    void AUTON_LEFT_crossMap() {

        // Start right in front of the roller
        Odometry::setPos( { 1_ft, 5_ft, 0_deg} );

        // Turn flywheel on
        // TODO: tweak power
        flywheel.runVoltage(12000);

        PathBuilder()
            .addPath(
                Movement( { 3_ft, 5_ft }, 3_s, FORWARD )
            )
            .execute();
        
        pointToAllianceGoal();

        // TODO: Shoot all 3 discs
        indexer.runTimed(12000, 2200);

        // Turn to disc line
        Turn( { 7_ft, 9_ft }, 3_s )
            .execute(FORWARD);

        // Collect discs
        intake.runVoltage(12000);

        // Go forward 
        PathBuilder()
            .addPath(
                Movement( {7_ft, 9_ft}, 4_s, FORWARD )
            )
            .execute();


        pointToAllianceGoal();

        // TODO: Shoot all 3 discs
        // Power feeder here
        indexer.runTimed(12000, 2200);
        
        intake.runVoltage(0);

        /*
        
        Turn( { 9_ft, 11_ft }, 3_s )
            .execute(REVERSE);
        
        PathBuilder()
            .addPath(
                Movement( { 9.5_ft, 11_ft }, 1.5_s, REVERSE )
            )
            .execute();

        Turn( 295_deg, 2_s)
            .execute(REVERSE);


        Drive::timedForward(0.5, 1000);
        intake.runTimed(-12000, 1100);

        */

        flywheel.runVoltage(0);
    }
}