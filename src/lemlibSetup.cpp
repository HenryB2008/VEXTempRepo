#include "lemlibSetup.h"



lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, 2, 0.7);  
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, 2, -3.5); 
lemlib::OdomSensors sensors(&vertical_tracking_wheel, // Vertical tracking wheel 1, set to null
                            nullptr, // Vertical tracking wheel 2, set to nullptr as we are using IMEs
                           &horizontal_tracking_wheel, // Horizontal tracking wheel 1
                            nullptr, // Horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // Inertial sensor
);


// latetral PID controller
lemlib::ControllerSettings lateral_controller(10.75 , // proportional gain (kP)6.2
                                              0, // integral gain (kI)
                                              29    , // derivative gain (kD) 1.9
                                              0, // anti windup
                                              0.5, // small error range, in inches
                                              450, // small error range timeout, in milliseconds
                                              1.5, // large error range, in inches
                                              900, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (s5lew)
);

// angular PID controller (8, 44 FOR SKILLS) 1.9, 9SET TO 3, 14 FOR THE OTHER AUTON 
lemlib::ControllerSettings angular_controller(8.5,  // proportional gain (kP) 12.5
                                              0, // integral gain (kI)
                                            59,               // derivative gain (kD) 30
                                              0, // anti windup
                                              0.5, // small error range, in degrees
                                              450, // small error range timeout, in milliseconds
                                              1.5, // large error range, in degrees
                                              900, // large error range timeout, in milliseconds
                                                0 // maximum acceleration (slew)
);

pros::MotorGroup left_motors({-4, -5, 7}, pros::MotorGearset::blue);
pros::MotorGroup right_motors({8, -9, 10}, pros::MotorGearset::blue);
// Initialize the drivetrain with the specified settings

lemlib::Drivetrain drivetrain (
   &left_motors,
   &right_motors,
   11.5,       // track width          // this might be wrong
   2.75,              // wheel diameter      
   450,            // wheel rpm            
   8             // horizontal drift
);

lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);