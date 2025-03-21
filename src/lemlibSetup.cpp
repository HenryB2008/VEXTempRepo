#include "lemlibSetup.h"

class CustomIMU : public pros::IMU {
  public:
  CustomIMU(int port, double scalar)
  : pros::IMU(port),
  m_port(port),
  m_scalar(scalar) {}                         
  virtual double get_rotation() const {
  return pros::c::imu_get_rotation(m_port) * m_scalar;
  }
  private:
  const int m_port;
  const double m_scalar;
  };
  
  // create custom IMU with a scalar of 1.1
  CustomIMU my_imu(17, 1.01); 




lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, 2, 1);  
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, 2, -2 );
lemlib::OdomSensors sensors(&vertical_tracking_wheel, // Vertical tracing wheel 1, set to null
                            nullptr, // Vertical tracking wheel 2, set to nullptr as we are using IMEs
                           &horizontal_tracking_wheel, // Horizontal tracking wheel 1
                            nullptr, // Horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &my_imu // Inertial sensor
);


// latetral PID controller
lemlib::ControllerSettings lateral_controller(7.25, // proportional gain (kP)6.2
                                              0, // integral gain (kI)
                                                13, // derivative gain (kD) 1.9
                                              5, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              2, // large error range, in inches
                                              400, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (s5lew)
);

// angular PID controller 5.3, 47 
lemlib::ControllerSettings angular_controller(5.3,  // proportional gain (kP) 12.5
                                            0,// integral gain (kI)
                                            47,               // derivative gain (kD) 30
                                             15, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              2.5, // large error range, in degrees
                                              400, // large error range timeout, in milliseconds
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