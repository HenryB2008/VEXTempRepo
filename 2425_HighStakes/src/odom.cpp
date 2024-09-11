// #include "odom.h"

// // Initialize IMU
// pros::Imu imu(8);

// // Horizontal tracking wheel encoder
// pros::Rotation horizontal_encoder(19);  // Change port to finalized one
// // Vertical tracking wheel encoder
// pros::Rotation vertical_encoder(16);    // Change port to finalized one

// // Horizontal tracking wheel
// lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_275, -5.75);    // Change distance in future
// // Vertical tracking wheel
// lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_275, -2.5); // Change distance in future



// // lateral motion controller
// lemlib::ControllerSettings linearController(10, // proportional gain (kP)
//                                             0, // integral gain (kI)
//                                             3, // derivative gain (kD)
//                                             3, // anti windup
//                                             1, // small error range, in inches
//                                             100, // small error range timeout, in milliseconds
//                                             3, // large error range, in inches
//                                             500, // large error range timeout, in milliseconds
//                                             20 // maximum acceleration (slew)
// );

// // angular motion controller
// lemlib::ControllerSettings angularController(2, // proportional gain (kP)
//                                              0, // integral gain (kI)
//                                              10, // derivative gain (kD)
//                                              3, // anti windup
//                                              1, // small error range, in degrees
//                                              100, // small error range timeout, in milliseconds
//                                              3, // large error range, in degrees
//                                              500, // large error range timeout, in milliseconds
//                                              0 // maximum acceleration (slew)
// );

// // OdomSensors setup
// lemlib::OdomSensors sensors(&vertical_tracking_wheel, // Vertical tracking wheel 1, set to null
//                             nullptr, // Vertical tracking wheel 2, set to nullptr as we are using IMEs
//                             &horizontal_tracking_wheel, // Horizontal tracking wheel 1
//                             nullptr, // Horizontal tracking wheel 2, set to nullptr as we don't have a second one
//                             &imu // Inertial sensor
// );
