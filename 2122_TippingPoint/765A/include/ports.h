#ifndef _PORTS_
#define _PORTS_


//motor ports
#define TOP_RIGHT_MOTOR 1
#define RIGHT_MIDDLE_MOTOR -8
#define BOTTOM_RIGHT_MOTOR 9
#define TOP_LEFT_MOTOR 5
#define LEFT_MIDDLE_MOTOR -2
#define BOTTOM_LEFT_MOTOR 6


//tracking wheel ports
#define LEFT_TRACKING_WHEEL_TOP 'A'
#define LEFT_TRACKING_WHEEL_BOTTOM 'B'
#define RIGHT_TRACKING_WHEEL_TOP 'C'
#define RIGHT_TRACKING_WHEEL_BOTTOM 'D'
#define BACK_TRACKING_WHEEL_TOP 'E'
#define BACK_TRACKING_WHEEL_BOTTOM 'F'


//odom distances between wheels
#define ODOMTRACK 6.9235_in
#define ODOMWHEELDIM 2.81665_in
#define ODOMBACKDISTANCE 6.5_in

//wheel track for pure pursuit
#define WHEELDIM 4_in
#define WHEELTRACK 13.125_in

//These are lift macros for the index of the lift. Do not touch
#define GOAL_LIFT 0
#define FOUR_BAR 1
#define SPIKE 2
#define INTAKE 3

#define INTAKE_PORT 20
#define FOUR_BAR_FIRST 19
#define IMUPORT 16

#define FRONT_PNEUM 'H'
#define BACK_CLAMP 'G'
#define BACK_TILT 'F'


#endif
