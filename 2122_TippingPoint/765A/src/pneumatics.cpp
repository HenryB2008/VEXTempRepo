#include "pneumatics.h"

Pneumatics::Pneumatics(uint8_t port) : piston(port) {
    // turnOff();
}

void Pneumatics::turnOn() {
    printf("pleaseturnon");
    piston.set_value(4095);
}

void Pneumatics::turnOff() {
    printf("isthisrunning\n");
    piston.set_value(0);
    printf("off\n");
}

void Pneumatics::onThenOff(int delay) {
    turnOn();
    pros::delay(1000);
    printf("hi");
    turnOff();
}

void Pneumatics::offThenOn(uint32_t delay) {
    turnOff();
    pros::delay(delay);
    turnOn();
}
