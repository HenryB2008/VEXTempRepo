
#include "colorSort.h"


bool colorSortOn    = false;
int  allianceColor = 0;          // 0 = red alliance (reject blue rings), 1 = blue alliance (reject red)


// state flag
bool ringWaiting = false;

void colorSortTask(void* param) {
  while (true) {
    if(colorSortOn){
      
    intakeMotor1.move(-127);

      if (!ringWaiting) {

        if (allianceColor == 0 && (colorSensor.get_hue() > 180 && colorSensor.get_hue() < 255)  && colorSensor.get_proximity() > 254) {
          ringWaiting = true; 
        } else if (allianceColor == 1 &&   (colorSensor.get_hue() < 30 || colorSensor.get_hue() > 330) && colorSensor.get_proximity() > 254) {
          ringWaiting = true; 
        }
      }

      else {
        if (intakeDistance.get() < 50) {
          pros::delay(40);
          intakeMotor1.move(0); 
          pros::delay(250);
          intakeMotor1.move(-127);
          ringWaiting = false;
        }
      }


    }
    pros::delay(20);

  }
}

