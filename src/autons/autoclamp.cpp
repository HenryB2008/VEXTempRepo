/*
#include "ports.h"
pros::Distance mogoSensor(5);
bool autoMogo; 

void autoMogo(void* param) {
    while (autoMogo){
        if(mogoSensor.get() < 130){
            mogo.extend(); 
        } else {
            mogo.retract(); 
        }
        pros::delay(20); 
    }
}
*/