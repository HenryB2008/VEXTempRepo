#ifndef ROUTES_H
#define ROUTES_H

void push(int fspd, int fdur, int bspd, int bdur, bool start_back);
void far_driver(lemlib::Chassis* chassis);
void close_driver(lemlib::Chassis* chassis);
void own_secondary(lemlib::Chassis* chassis);
void skills(lemlib::Chassis* chassis);
void awp(lemlib::Chassis* chassis);
void elims(lemlib::Chassis* chassis);

#endif