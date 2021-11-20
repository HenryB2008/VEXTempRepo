#include "effectors.h"

Effectors::Effectors() {

}

void Effectors::addPosition() {
  encPositions[0][0] = 0;
  encPositions[0][1] = 600;
  encPositions[0][2] = 1200;
  encPositions[1][0] = 0;
  encPositions[1][1] = 2300;
  prevCounts[0] = 0;
  prevCounts[1] = 0;
  prevCounts[2] = 0;
}

void Effectors::step(int buttons[3], double speeds[3]) {
  
  buttons[0] = buttons[0] % 3;
  buttons[1] = buttons[1] % 2;
  /*
  if(goalFinal) {
    if(motors[1].getPosition()>0.5*encPositions[1][1]) {
      motors[0].moveAbsolute(encPositions[0][2], speeds[0]);
      goalFinal = false;
    }
  }
  else if(spikeUp) {
    if(abs(motors[1].getPosition()-encPositions[1][0]) < 200 ) {
      motors[2].moveAbsolute(encPositions[2][1], speeds[1]);
      spikeUp = false;
    }
  }
  */

    for(int i = 0; i < 2; i++) {
      printf("%d ", buttons[i]);
      if(buttons[i] != prevCounts[i]) {
        /*
        if(i == 0 && buttons[i] == 2) {
          goalFinal = true;
          motors[1].moveAbsolute(encPositions[1][2], speeds[1]);
        }
        if(i == 2 && buttons[i] == 1) {
          spikeUp = true;
          motors[i].moveAbsolute(encPositions[1][0], speeds[1]);
        }
        */
        motors[i].moveAbsolute(encPositions[i][buttons[i]], speeds[i]);
        if(i == 1) {
          motors[i+1].moveAbsolute(encPositions[i][buttons[i]], speeds[i]);
        }
    }
    
  }
  
  printf("\n");
  for(int i = 0; i < 2; i++) {
    prevCounts[i] = buttons[i];
  }
  
}
