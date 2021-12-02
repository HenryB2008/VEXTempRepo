#include "effectors.h"

Effectors::Effectors() {
  for(int i = 0; i < 3; i++) {
    motors[i].getEncoder().reset();
  }
}

void Effectors::addPosition() {
  encPositions[0][0] = 1800;
  encPositions[0][1] = 4400;
  encPositions[1][0] = 0;
  encPositions[1][1] = 2400;
  prevCounts[0] = 0;
  prevCounts[1] = 0;
  prevCounts[2] = 0;

}

void Effectors::step(int buttons[3], double speeds[3]) {

  buttons[0] = buttons[0] % 2;
  buttons[1] = buttons[1] % 2;

    for(int i = 0; i < 2; i++) {
      //printf("%d ", buttons[i]);
      printf("Enc position: %f", motors[i].getPosition());
      if(buttons[i] != prevCounts[i]) {
        motors[i].moveAbsolute(encPositions[i][buttons[i]], speeds[i]);
        if(i == 1) {
          motors[i+1].moveAbsolute(encPositions[i][buttons[i]], speeds[i]);
        }
    }

  }
  for(int i = 0; i < 2; i++) {
    prevCounts[i] = buttons[i];
  }
}

void Effectors::runOne(int lift, int pos) {
  motors[lift].moveAbsolute(encPositions[lift][pos], 200);
}
