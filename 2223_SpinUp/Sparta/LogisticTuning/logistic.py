from math import e


class Logistic:

    def __init__(self, _start_time, _num_intervals, _theta_diff, _start_theta):
        self.time_increment = abs(_start_time) * 2 / _num_intervals
        self.max_val = _theta_diff
        self.cur_time = _start_time
        self.ideal_theta = 0
        self.start_theta = _start_theta

    @staticmethod
    def logistic_val(max_output, time):
        return max_output / (1 + pow(e, -time))

    def step(self):
        self.cur_time += self.time_increment
        self.ideal_theta = Logistic.logistic_val(self.max_val, self.cur_time)
        return self.start_theta + self.ideal_theta
