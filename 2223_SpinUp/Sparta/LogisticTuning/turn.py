import logistic
from direction import Direction
import pidcontroller
import robot_sim
import matplotlib.pyplot as plt


class Turn:

    def __init__(self, _target_heading, _time):

        self.target_heading = _target_heading
        self.time = _time

    @staticmethod
    def constrain_angle_180(heading):

        new_heading = heading

        if -180 < new_heading <= 180:
            pass
        elif new_heading <= -180:
            while new_heading <= -180:
                new_heading += 360
        else:
            while new_heading > 180:
                new_heading -= 360

        return new_heading

    def execute_logistic(self, _direction, _gains, slew, integral_max):

        turn_controller = pidcontroller.PidController(_gains, slew, integral_max, 1)

        if _direction == Direction.REVERSE:
            self.target_heading += 180

        theta_diff = Turn.constrain_angle_180(self.target_heading - robot_sim.get_current_heading())

        logistic_controller = logistic.Logistic(
            -self.time * 2,
            self.time * 1000 / 10,
            theta_diff,
            robot_sim.get_current_heading()
        )

        i = 0

        print(f"Target Heading: {i}")

        iterations = []
        cur_thetas = []
        theta_diffs = []
        turn_errors = []
        turn_powers = []

        while abs(theta_diff) > 0.25 and i < self.time * 1000 / 10:
            theta_diff = Turn.constrain_angle_180(self.target_heading - robot_sim.get_current_heading())

            turn_error = logistic_controller.step() - robot_sim.get_current_heading()

            turn_power = turn_controller.step(turn_error)

            robot_sim.rotate_heading(turn_power)

            print(f"Iter: {i:4} Cur Theta: {robot_sim.get_current_heading():<16.10f} "
                  f"Theta_Diff: {theta_diff:<16.10f} Turn_Error: {turn_error:<16.10f} "
                  f"Turn_Power: {turn_power:<16.10f}")

            iterations.append(i)
            cur_thetas.append(robot_sim.get_current_heading())
            theta_diffs.append(theta_diff)
            turn_errors.append(turn_error)
            turn_powers.append(turn_power)

            i += 1

        figure, axis = plt.subplots(2, 2)

        axis[0, 0].plot(iterations, cur_thetas)
        axis[0, 0].set_title("Current Heading")

        axis[0, 1].plot(iterations, theta_diffs)
        axis[0, 1].set_title("Theta Difference")

        axis[1, 0].plot(iterations, turn_errors)
        axis[1, 0].set_title("Turn Error")

        axis[1, 1].plot(iterations, turn_powers)
        axis[1, 1].set_title("Turn Power")

        plt.show()
