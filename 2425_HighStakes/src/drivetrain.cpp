#include "drivetrain.h"
#include "odom.h"
#include "pid.h"

// Initialize the left and right motor groups
MotorGroup left_motors({-8, -4, -10}, MotorGearset::blue);
MotorGroup right_motors({11, 12, 13}, MotorGearset::blue);

// Initialize the drivetrain with the specified settings
lemlib::Drivetrain drivetrain (
   &left_motors,
   &right_motors,
   12,       // track width          // this might be wrong
   2.75,              // wheel diameter       
   600,            // wheel rpm            
   2               // horizontal drift
);

lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);
