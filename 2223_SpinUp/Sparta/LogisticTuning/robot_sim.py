import math

current_heading = 0

# measured in inches
wheel_circumference = math.pi * 4

# 280 rpm -> inches per second
max_arc_movement = (280 * wheel_circumference / 3600)

# wheel radius inches
wheel_radius = 14.298 / 2


def get_current_heading():
    return current_heading


def set_current_heading(x):
    global current_heading

    current_heading = x


def rotate_heading(power):
    # rotate robot based of wheel velocity

    # convert 1 second interval to 10_ms interval
    # 10_ms = 0.01 s

    global current_heading

    # converting from degrees to radians

    # 30 is just a number to account for differences between the bot and simulation

    current_heading += 30 * (max_arc_movement * power * 0.01 / wheel_radius) * (180 / math.pi)
