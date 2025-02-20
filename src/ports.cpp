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
pros::Distance rightDistance(3);
pros::Optical colorSensor(12); 
pros::Rotation rotation_sensor(13);
pros::Rotation vertical_encoder(14);
pros::Distance leftDistance(16);
pros::Imu imu(17);
pros::Rotation horizontal_encoder(19);
pros::Motor intakeMotor1(20); 
pros::Motor liftMotor(21);  
pros::adi::Pneumatics mogo('A', false);
pros::adi::Pneumatics leftDoinker('B', false);
pros::adi::Pneumatics rightDoinker('C', false);
pros::Controller controller(pros::E_CONTROLLER_MASTER);

