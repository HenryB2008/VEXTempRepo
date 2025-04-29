#ifndef _PORTS_H
#define _PORTS_H

#include "main.h"


/*

pros::Distance leftDistance(1);
pros::Distance rightDistance(3);
pros::Optical optical(12); 
pros::Rotation rotation_sensor(13);
pros::Rotation vertical_encoder(14);
pros::Distance leftDistance(16);
pros::Imu imu(17);
pros::Rotation horizontal_encoder(19);
pros::Motor intakeMotor1(20); 
pros::Motor liftMotor(21);
pros::adi::Pneumatics mogo('A', true);
pros::adi::Pneumatics leftDoinker('B', true);
pros::adi::Pneumatics rightDoinker('C', true);
pros::Controller controller(pros::E_CONTROLLER_MASTER);


extern pros::Rotation rotation_sensor;
extern pros::Motor liftMotor;
extern pros::Imu imu;
extern pros::Rotation horizontal_encoder;
extern pros::Rotation vertical_encoder;
extern pros::adi::Pneumatics mogo;
extern pros::adi::Pneumatics intakeSolenoid;
extern pros::adi::Pneumatics doinker;
extern pros::adi::Pneumatics raiseSolenoid; 
extern pros::Controller controller;
extern pros::Motor intakeMotor1;

*/

extern pros::Distance frontDistance;
extern pros::Distance rightDistance;
extern pros::Distance intakeDistance; 
extern pros::Optical colorSensor;
extern pros::Rotation rotation_sensor;
extern pros::Rotation vertical_encoder;
extern pros::Distance leftDistance;
extern pros::Imu imu;
extern pros::Rotation horizontal_encoder;
extern pros::Motor intakeMotor1;
extern pros::Motor lbMotor1;
extern pros::Motor lbMotor2; 
extern pros::adi::Pneumatics mogo;
extern pros::adi::Pneumatics leftDoinker;
extern pros::adi::Pneumatics rightDoinker;
extern pros::Controller controller;
extern pros::adi::Pneumatics gRushClamp;
extern pros::Imu imu; 




#endif