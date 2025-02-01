#include "main.h"
#include "init.h"
#include "drivecode.h"
#include "autons.h"

void initialize() {
	init();
}



void autonomous() {
	qualAutoBlue(); 
}
void opcontrol() {
	driver(); 
}