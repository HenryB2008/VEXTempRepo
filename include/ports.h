#ifndef _PORTS_H
#define _PORTS_H

#include "main.h"

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


#endif