

class PidController:

    def __init__(self, _gains, _slew, _integral_max, _max_output):

        self.gains = _gains
        self.slew = _slew
        self.max_output = _max_output
        self.integral_max = _integral_max

        self.prev_error = 0
        self.prev_output = 0
        self.error_sum = 0

    @staticmethod
    def clamp(n, smallest, largest):

        return max(smallest, min(n, largest))

    def step(self, cur_error):

        self.error_sum += cur_error

        p_value = cur_error * self.gains.kp
        i_value = self.error_sum * self.gains.ki

        i_value = PidController.clamp(i_value, -self.integral_max, self.integral_max)

        d_value = (cur_error - self.prev_error) * self.gains.kd

        # print(f"P: {p_value:1.5f} I: {i_value:1.5f} D: {d_value:1.5f}")

        raw_output = p_value+i_value+d_value

        final_output = 0

        if raw_output > 0:

            final_output = PidController.clamp(raw_output, self.prev_output - self.slew,
                                               min(self.max_output, self.prev_output + self.slew))

        elif raw_output < 0:

            final_output = PidController.clamp(raw_output, max(-self.max_output, self.prev_output - self.slew),
                                               self.prev_output + self.slew)

        else:

            final_output = 0

        self.prev_error = cur_error

        self.prev_output = final_output

        return final_output
