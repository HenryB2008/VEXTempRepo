#include "main.h"
#include "init.h"
#include "drivecode.h"
#include "autons\test.h"
#include "autons\redRingRush.h"

void initialize() {
	init();
}

void opcontrol() {
	colorSortOn = false; 
	driver(); 
}

void autonomous(){
	colorSortOn = true; 
	redRingRush(); 
}