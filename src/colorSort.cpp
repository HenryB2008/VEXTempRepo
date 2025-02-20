#include "colorSort.h"

bool colorSortOn = true; 
int allianceColor = 2;   //0 = red (sorts out blue), 1 = blue (sorts out red)  //2 stops intake whenever ring is detected,

int power = -127; 


void colorSortTask(void* param) {
    while (true){
       if(colorSortOn){
            intakeMotor1.move(power);
            if(allianceColor == 0 && colorSensor.get_proximity() >= 140 && (colorSensor.get_hue() > 200 && colorSensor.get_hue() < 255)){
                pros::delay(115);
                intakeMotor1.move(127); 
                pros::delay(150);
                power = -127; 
                
            } else if(allianceColor == 1 && colorSensor.get_proximity() >= 140 && (colorSensor.get_hue() > 0 && colorSensor.get_hue() < 30)) {
                pros::delay(115);
                intakeMotor1.move(127);
                pros::delay(150);
                power = -127; 
            }
            else if(allianceColor == 2 && colorSensor.get_proximity() >= 140) {
                power = -127; 
                intakeMotor1.move(127);
                pros::delay(75);
                intakeMotor1.brake(); 

                colorSortOn = false; 
            } else if (allianceColor == 3 && colorSensor.get_proximity() >= 140) {
                power = -96; 
                intakeMotor1.move(-96);
                pros::delay(400);
                intakeMotor1.brake(); 
                colorSortOn = false; 
            }
       }

        pros::delay(20); // Save resources
    }

}
