#ifndef _PORTS_
#define _PORTS_


//motor ports
#define BOTTOM_RIGHT_MOTOR 2
#define BOTTOM_LEFT_MOTOR 12
#define TOP_RIGHT_MOTOR 6
#define TOP_LEFT_MOTOR 14

//tracking wheel ports
#define LEFT_TRACKING_WHEEL_TOP 'C'
#define LEFT_TRACKING_WHEEL_BOTTOM 'D'
#define RIGHT_TRACKING_WHEEL_TOP 'B'
#define RIGHT_TRACKING_WHEEL_BOTTOM 'A'
#define BACK_TRACKING_WHEEL_TOP 'E'
#define BACK_TRACKING_WHEEL_BOTTOM 'F'


//odom distances between wheels
#define ODOMTRACK 6.875_in
#define ODOMWHEELDIM 2.75_in
#define ODOMBACKDISTANCE 6.5_in


//These are lift macros for the index of the lift. Do not touch
#define GOAL_LIFT 0
#define FOUR_BAR 1
#define SPIKE 2
#define INTAKE 3

#define INTAKE_PORT 8
#define FOUR_BAR_FIRST -1
#define FOUR_BAR_SECOND 10
#define IMUPORT 16

#define PNEUM 'G'

#define TRACK 6.875

#endif
