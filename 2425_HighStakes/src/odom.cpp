#include "odom.h"

// Initialize IMU
pros::Imu imu(10);

// Horizontal tracking wheel encoder
pros::Rotation horizontal_encoder(20);  // Change port to finalized one
// Vertical tracking wheel encoder
pros::Rotation vertical_encoder(21);    // Change port to finalized one

// Horizontal tracking wheel
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_275, -5.75);    // Change distance in future
// Vertical tracking wheel
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_275, -2.5); // Change distance in future

// OdomSensors setup
lemlib::OdomSensors sensors(&vertical_tracking_wheel, // Vertical tracking wheel 1, set to null
                            nullptr, // Vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horizontal_tracking_wheel, // Horizontal tracking wheel 1
                            nullptr, // Horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // Inertial sensor
);

