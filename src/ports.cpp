#include "ports.h"


/*
pros::Rotation rotation_sensor(9);
pros::Motor liftMotor(20);
pros::Imu imu(16); //imu.
pros::Rotation horizontal_encoder(5); 
pros::Rotation vertical_encoder(7);   
pros::adi::Pneumatics mogo('B', false); 
pros::adi::Pneumatics intakeSolenoid('H', false);  //this is actually the mogo tipper, ignore bad naming :( 
pros::adi::Pneumatics doinker('D', false);
pros::adi::Pneumatics raiseSolenoid('F', false);  //this is the intake raise 
pros::Motor intakeMotor1 (15);
pros::Controller controller(pros::E_CONTROLLER_MASTER);
*/


pros::Distance frontDistance(1);
pros::Distance intakeDistance(5);
pros::Optical colorSensor(2); 
pros::Distance colorSortDistanceSensor(3);
pros::Rotation rotation_sensor(18);
pros::Rotation vertical_encoder(21);
pros::Distance leftDistance(16);
pros::Rotation horizontal_encoder(14);
pros::Motor intakeMotor1(15); 
pros::Motor lbMotor1(19);
pros::Motor lbMotor2(-20);  
pros::adi::Pneumatics mogo('A', false);
pros::adi::Pneumatics leftDoinker('B', false);
pros::adi::Pneumatics rightDoinker('C', false);
pros::adi::Pneumatics gRushClamp('E', false);
pros::Controller controller(pros::E_CONTROLLER_MASTER); 
pros::Imu imu(16);



