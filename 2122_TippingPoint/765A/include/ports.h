#ifndef _PORTS_
#define _PORTS_

#define INTAKEIN ControllerDigital::L1
#define INTAKEOUT ControllerDigital::R1

#define BACKUP ControllerDigital::up
#define BACKDOWN ControllerDigital::down

#define FRONTUP ControllerDigital::X
#define FRONTDOWN ControllerDigital::B

#define TOP_LEFT_MOTOR 3
#define TOP_RIGHT_MOTOR 11
#define BOTTOM_LEFT_MOTOR 1
#define BOTTOM_RIGHT_MOTOR 14

#define LEFT_TRACKING_WHEEL_TOP 'C'
#define LEFT_TRACKING_WHEEL_BOTTOM 'D'
#define RIGHT_TRACKING_WHEEL_TOP 'B'
#define RIGHT_TRACKING_WHEEL_BOTTOM 'A'

#define ODOMTRACK 14_in
#define ODOMWHEELDIM 2.75_in
#define ODOMBACKDISTANCE 1

#define GOAL_LIFT 0
#define FOUR_BAR 1

#endif
