#include "ports.h"

pros::Rotation rotation_sensor(9);
pros::Motor liftMotor(20);
pros::Imu imu(16); //imu.
pros::Rotation horizontal_encoder(5); 
pros::Rotation vertical_encoder(7);   
pros::adi::Pneumatics mogo('B', false); 
pros::adi::Pneumatics intakeSolenoid('H', false);  //this is actually the mogo tipper, ignore bad naming :( 
pros::adi::Pneumatics doinker('D', false);
pros::adi::Pneumatics raiseSolenoid('B', false);  //this is the intake raise 
pros::Motor intakeMotor1 (15);
pros::Controller controller(pros::E_CONTROLLER_MASTER);
