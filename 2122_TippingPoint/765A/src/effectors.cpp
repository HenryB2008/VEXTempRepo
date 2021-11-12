#include "effectors.h"

void Effectors::addPosition(int lift, int pos) {
  encPositions[lift].push_back(pos);
}

void Effectors::step(int buttons[4], double speeds[4]) {
  for(int i = 0; i < 3; i++) {
    buttons[i] = buttons[i] % encPositions[i][buttons[i] % encPositions[i].size()];
  }
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
  else {
    for(int i = 0; i < 3; i++) {
      if(buttons[i] != prevCounts[i]) {
        if(i == 0 && buttons[i] == 2) {
          goalFinal = true;
          motors[1].moveAbsolute(encPositions[1][2], speeds[1]);
        }
        if(i == 2 && buttons[i] == 1) {
          spikeUp = true;
          motors[i].moveAbsolute(encPositions[1][0], speeds[1]);
        }
        motors[i].moveAbsolute(encPositions[i][buttons[i]], speeds[i]);
    }
  }
  }
  for(int i = 0; i < 3; i++) {
    prevCounts[i] = buttons[i];
  }
}
