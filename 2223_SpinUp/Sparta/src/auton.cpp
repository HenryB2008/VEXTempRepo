#include "auton.h"
#include "drive.h"
#include "path_builder.h"
#include "pneums.h"
#include "moveutil.h"

// TODO: fix overshooting

namespace Auton {

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

        MoveUtil::turnTo(ALLIANCE_GOAL, 2.5_s, FORWARD);

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

        MoveUtil::turnTo( {3_ft, 5_ft}, 2_s, FORWARD);

        PathBuilder()
            .addPath( 
                Movement({3_ft, 5_ft}, 3_s, FORWARD)
                    .withDistanceMax(0.9)
            )
            .addPath( 
                Movement({4_ft, 6_ft}, 2_s, FORWARD)
                    .withDistanceMax(0.5)
            )
            .execute();

        flywheel.runRPM(118);

        Drive::timedForward(0.3, 400);

        pros::delay(200);

        MoveUtil::turnTo(ALLIANCE_GOAL, 2_s, FORWARD);

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

    void overturnTest(){
        Odometry::setPos( { 6_ft, 8_ft, 150_deg });

        // Move towards roller
        MoveUtil::turnTo({ 6_ft, 10_ft }, 2_s, REVERSE);
        // MoveUtil::moveTo({ 9_ft, 11_ft }, 2_s, REVERSE, 1.0);

    }

    void SKILLS() {

        // Start right in front of the roller
        Odometry::setPos( { 1_ft, 3_ft, 0_deg} );

        flywheel.runRPM(200);

        // Back up into roller
        Drive::timedForward(-0.3, 600);

        intake.runRPM(-90);

        pros::delay(500);

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
        pros::delay(600);
        indexer.runRPM(0);

        Turn({2_ft, 2_ft}, 2_s)
            .executeLogistic(FORWARD);

        
        PathBuilder()
            .addPath( 
                Movement({2_ft, 2_ft}, 2_s, FORWARD)
                    .withDistanceMax(1)
            )
            .execute();

        pros::delay(500);

        Turn(90_deg, 2_s)
            .executeLogistic(FORWARD);

        intake.runRPM(135);

        // Back up into roller
        Drive::timedForward(-0.4, 800);

        pros::delay(800);

        Drive::timedForward(0.3, 300);

        intake.runRPM(200);

        Turn({5_ft, 3_ft}, 2_s)
            .executeLogistic(FORWARD);

        PathBuilder()
            .addPath( 
                Movement({5_ft, 3_ft}, 3_s, FORWARD)
                    .withDistanceMax(0.6)
            )
            .addPath( 
                Movement({6_ft, 4_ft}, 2_s, FORWARD)
                    .withDistanceMax(0.7)
            )
            .execute();  

        flywheel.runRPM(113);

        Turn(ALLIANCE_GOAL, 2_s)
            .executeLogistic(FORWARD);  
        
        // Run the indexer to shoot all of the preloaded discs
        indexer.runRPM(200);
        pros::delay(300);
        indexer.runRPM(0);

        flywheel.runRPM(108);
        pros::delay(300);

        indexer.runRPM(200);
        pros::delay(400);
        indexer.runRPM(0);

        flywheel.runRPM(110);
        pros::delay(500);
        indexer.runRPM(200);
        pros::delay(1000);
        indexer.runRPM(0);
        
        // Picking up some discs
        MoveUtil::turnTo({ 8_ft, 6_ft }, 2_s, FORWARD);
        MoveUtil::moveTo({ 8_ft, 6_ft }, 2_s, FORWARD, 0.8);

        MoveUtil::turnTo({ 7_ft, 7_ft }, 2_s, FORWARD);
        
        PathBuilder()
            .addPath( 
                Movement({7_ft, 7_ft}, 2.5_s, FORWARD)
                    .withDistanceMax(0.8)
            )
            .addPath( 
                Movement({6_ft, 8_ft}, 2.5_s, FORWARD)
                    .withDistanceMax(0.8)
            )
            .execute();

        pros::delay(300);

        // Turn to the enemy goal
        Drive::timedTurn(0.375, 200);

        // Run the indexer to shoot all of the preloaded discs
        indexer.runRPM(200);
        pros::delay(300);
        indexer.runRPM(0);

        flywheel.runRPM(105);
        pros::delay(300);

        indexer.runRPM(200);
        pros::delay(400);
        indexer.runRPM(0);

        flywheel.runRPM(107);
        pros::delay(500);
        indexer.runRPM(200);
        pros::delay(400);
        indexer.runRPM(0);

        // Move towards roller
        MoveUtil::turnTo({ 9_ft, 11.5_ft }, 2_s, REVERSE);
        intake.runRPM(0);
        MoveUtil::moveTo({ 9_ft, 11.5_ft }, 2_s, REVERSE, 0.8);

        // Turn flush with the roller
        MoveUtil::turnTo(270_deg, 2_s, FORWARD);

        // Back up into roller
        Drive::timedForward(-0.3, 750);

        intake.runRPM(-130);
        pros::delay(400);
        intake.runRPM(0);

        Drive::timedForward(0.3, 500);
    }
}