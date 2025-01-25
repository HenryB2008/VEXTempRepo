#ifndef _LEMLIB_SETUP_H
#define _LEMLIB_SETUP_H

#include "main.h"
#include "ports.h"
#include <vector> 


extern lemlib::TrackingWheel horizontal_tracking_wheel;
extern lemlib::TrackingWheel vertical_tracking_wheel;

extern lemlib::OdomSensors sensors;


extern lemlib::ControllerSettings lateral_controller;


extern lemlib::ControllerSettings angular_controller;

extern pros::MotorGroup left_motors;
extern pros::MotorGroup right_motors;


extern lemlib::Drivetrain drivetrain; 

extern lemlib::Chassis chassis;

#endif