#pragma once
#include "lemlib/api.hpp"
#include "pros/imu.hpp"
#include "pros/rotation.hpp"

using namespace pros;


extern pros::Imu imu;
extern pros::Rotation horizontal_encoder;
extern pros::Rotation vertical_encoder;
extern lemlib::TrackingWheel horizontal_tracking_wheel;
extern lemlib::TrackingWheel vertical_tracking_wheel;
extern lemlib::OdomSensors sensors;

