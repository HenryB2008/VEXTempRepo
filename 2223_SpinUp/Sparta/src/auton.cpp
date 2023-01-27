#include "auton.h"
#include "drive.h"
#include "path_builder.h"
#include "pneums.h"

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

    void LeftAuton_FiveDiscs_OneRoller() {
        
        // Start right in front of the roller
        Odometry::setPos( { 1_ft, 3_ft, 0_deg} );

        flywheel.runRPM(200);

        // Back up into roller
        Drive::timedForward(-0.3, 600);

        intake.runRPM(-90);

        pros::delay(300);

        intake.runRPM(0);

        Drive::timedForward(0.3, 500);

        intake.runRPM(200);

        flywheel.runRPM(133);

        Turn( ALLIANCE_GOAL, 2.5_s)
            .executeLogistic(FORWARD);

        pros::delay(1000);

        // Run the indexer to shoot all of the preloaded discs
        indexer.runRPM(200);
        pros::delay(400);
        indexer.runRPM(0);

        flywheel.runRPM(127);

        pros::delay(500);

        indexer.runRPM(200);
        pros::delay(400);
        indexer.runRPM(0);

        Turn ( {3_ft, 5_ft}, 2_s)
            .executeLogistic(FORWARD);

        PathBuilder()
            .addPath( 
                Movement({3_ft, 5_ft}, 3_s, FORWARD)
                    .withDistanceMax(0.6)
            )
            .addPath( 
                Movement({4_ft, 6_ft}, 2_s, FORWARD)
                    .withDistanceMax(0.7)
            )
            .execute();

        flywheel.runRPM(118);

        Drive::timedForward(0.5, 400);

        pros::delay(200);

        Turn( Odometry::pointingTo(ALLIANCE_GOAL), 2_s)
            .executeLogistic(FORWARD);

        pros::delay(100);

        Drive::timedForward(0.4, 300);

        pros::delay(200);

        // Run the indexer to shoot all of the preloaded discs
        indexer.runRPM(200);
        pros::delay(300);
        indexer.runRPM(0);

        flywheel.runRPM(118);
        pros::delay(300);

        indexer.runRPM(200);
        pros::delay(400);
        indexer.runRPM(0);

        flywheel.runRPM(117);
        pros::delay(500);
        
        indexer.runRPM(200);

    }

    void RightAuton_ThreeDiscs_OneRoller(){

        // Start right in facing disc
        Odometry::setPos( { 7_ft, 11_ft, 270_deg} );

        flywheel.runRPM(120);

        intake.runRPM(200);

        PathBuilder()
            .addPath( 
                Movement({7_ft, 9_ft}, 2_s, FORWARD)
            )
            .execute();

        /*

        Turn( ALLIANCE_GOAL, 1.5_s)
            .executeLogistic(FORWARD);

        pros::delay(200);

        // Run the indexer to shoot all of the preloaded discs
        indexer.runRPM(200);
        pros::delay(300);
        indexer.runRPM(0);

        indexer.runRPM(200);
        pros::delay(400);
        indexer.runRPM(0);

        indexer.runRPM(200);
        pros::delay(400);
        indexer.runRPM(0);

        Turn( {9_ft, 10.5_ft}, 2_s)
            .executeLogistic(REVERSE);

        PathBuilder()
            .addPath( 
                Movement({9_ft, 10.5_ft}, 2_s, REVERSE)
            )
            .execute();

        Turn ( -90_deg, 2_s)
            .executeLogistic(FORWARD);

        // Back up into roller
        Drive::timedForward(-0.4, 400);

        intake.runRPM(-120);

        Drive::arcade(-0.4, 0);

        pros::delay(400);

        Drive::timedForward(0.3, 500);

        */

    }

    void SKILLS() {

        // Start right in front of the roller
        Odometry::setPos( { 1_ft, 3_ft, 0_deg} );

        flywheel.runRPM(200);

        // Back up into roller
        Drive::timedForward(-0.3, 600);

        intake.runRPM(-90);

        pros::delay(300);

        intake.runRPM(0);

        Drive::timedForward(0.3, 500);

        intake.runRPM(200);

        flywheel.runRPM(133);

        Turn({2_ft, 2_ft})
            .executeLogistic(FORWARD);

        PathBuilder()
            addPath( 
                Movement({2_ft, 2_ft}, 2_s, FORWARD)
                    .withDistMax(0.5)
            )
            .execute();

        Turn(90_deg)
            .executeLogistic(FORWARD);

        // Back up into roller
        Drive::timedForward(-0.5, 700);

        intake.runRPM(-90);

        pros::delay(300);

        intake.runRPM(0);

        Drive::timedForward(0.3, 500);

        intake.runRPM(200);



        Turn( Odometry::pointingTo(ALLIANCE_GOAL), 2_s)
            .executeLogistic(FORWARD);

        pros::delay(100);

        Drive::timedForward(0.4, 300);

        pros::delay(200);

        // Run the indexer to shoot all of the preloaded discs
        indexer.runRPM(200);
        pros::delay(300);
        indexer.runRPM(0);

        flywheel.runRPM(118);
        pros::delay(300);

        indexer.runRPM(200);
        pros::delay(400);
        indexer.runRPM(0);

        flywheel.runRPM(117);
        pros::delay(500);

        indexer.runRPM(200);
        pros::delay(400);
        indexer.runRPM(0);

    }
}