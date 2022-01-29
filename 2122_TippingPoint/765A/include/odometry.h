#ifndef _ODOMETRY_
#define _ODOMETRY_

#include "main.h"
#include "ports.h"

class IMUOdometry {
public:
  Odometry(ADIEncoder left, ADIEncoder right, ADIEncoder back, pros::IMU imu, double backdistance, double track);
  OdomState step();
private:
  pros::IMU imu;
  ADIEncoder left, right, back;
  int prevleft, prevright, prevback;
  OdomState prevState;

  

};

#endif
