#include "pneumatics.h"

Pneumatics::Pneumatics(uint8_t port) : piston(port) {
    // turnOff();
}

void Pneumatics::handle(int count) {
  if(count%2 == 0 && count!= prevCount) {
    turnOff();
  }
  if(count%2 == 1 && count!= prevCount) {
    turnOn();
  }
}

void Pneumatics::turnOn() {
    printf("pleaseturnon");
    piston.set_value(4095);
    state = true;
}

void Pneumatics::turnOff() {
    printf("isthisrunning\n");
    piston.set_value(0);
    printf("off\n");
    state = false;
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
