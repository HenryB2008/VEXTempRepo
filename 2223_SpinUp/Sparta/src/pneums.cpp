#include "pneums.h"

Pneumatics::Pneumatics(uint8_t port): piston(port){
    // TODO: Put pneums.off()

    // remove from initialize
}

void Pneumatics::on(){
    piston.set_value(1);
    state = true;
}

void Pneumatics::off(){
    piston.set_value(0);
    state = false;
}

void Pneumatics::toggle(){
    if(state == false){
        on();
    } else {
        off();
    }
}

Pneumatics angleChanger = Pneumatics(PNEUM_SWITCHER);
Pneumatics endgame = Pneumatics(ENDGAME_PORT);