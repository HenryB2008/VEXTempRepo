from turn import Turn
import robot_sim
from direction import Direction
from pidgains import PidGains

# main starts

robot_sim.set_current_heading(150)

first_movement = Turn(30, 2)

first_movement.execute_logistic(Direction.REVERSE, PidGains(0.02, 0.00065, 0.000135), 0.1, 0.2)
