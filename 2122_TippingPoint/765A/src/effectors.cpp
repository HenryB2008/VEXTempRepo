#include "effectors.h"

//reset encoders for effectors
Effectors::Effectors() {
  for(int i = 0; i < 1; i++) {
    motors[i].getEncoder().reset();
  }
}

//set all encoder positions for two bar
void Effectors::addPosition() {
  encPositions[0][0] = 1275; // Two bar upper position
  encPositions[0][1] = 2175; // Two bar lower position
  prevCounts[0] = 0;
  prevCounts[1] = 0;
  prevCounts[2] = 0;

}

//handle two bar in opcontrol
void Effectors::step(int buttons[3], double speeds[3]) {

  buttons[0] = buttons[0] % 2;
  buttons[1] = buttons[1] % 2;

    for(int i = 0; i < 1; i++) {
      //printf("Enc position: %f", motors[i].getPosition());
      if(buttons[i] != prevCounts[i]) {
        motors[i].moveAbsolute(encPositions[i][buttons[i]], speeds[i]);
    }

  }
  for(int i = 0; i < 1; i++) {
    prevCounts[i] = buttons[i];
  }
}

//move two bar to preset position
void Effectors::runOne(int lift, int pos) {
  motors[lift].moveAbsolute(encPositions[lift][pos], 200);
}

//move two bar to any position
void Effectors::runOneToPosition(int lift, int pos) {
  motors[lift].moveAbsolute(pos, 200);
}
