#ifndef _PATH_GEN_
#define _PATH_GEN_

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

struct point {
    double x, y, curve, vel, distance;
};

//experimental path generation class
class PurePursuitPathGen {
public:


    std::vector<point> initial_points;
    std::vector<point> final_points;
    double spacing;
    double a, b, tolerance, max_vel, max_accel;
    int k;

    void interpolate();
    void smooth();
    void calc_distances();
    void calc_curvature();
    void print_path();
    void write_to_file();
    void calc_velocities();
    std::vector<point> get_points();
    PurePursuitPathGen(double spacing, double a, double b, double tolerance, std::vector<std::pair<double, double>> points, double max_vel, double max_accel, int k);

};


#endif
