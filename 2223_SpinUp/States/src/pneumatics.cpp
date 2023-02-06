#include "pneumatics.h"

Pneumatics::Pneumatics(uint8_t port): piston(port){
}

void Pneumatics::on(){
    piston.set_value(1);
    state = ACTIVATED;
}

void Pneumatics::off(){
    piston.set_value(0);
    state = DEACTIVATED;
}

void Pneumatics::toggle(){
    if(state == DEACTIVATED){
        on();
    } else {
        off();
    }
}