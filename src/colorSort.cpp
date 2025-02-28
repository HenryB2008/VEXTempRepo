#include "colorSort.h"

bool colorSortOn = true; 
bool stopTransition = false; 
int allianceColor;   //0 = red (sorts out blue), 1 = blue (sorts out red)  //2 stops intake whenever ring is detected,

int power = -127; 


void colorSortTask(void* param) {
    while (true){
       if(colorSortOn){
            intakeMotor1.move(power);
            if(allianceColor == 0 && colorSensor.get_proximity() >= 140 && (colorSensor.get_hue() > 180 && colorSensor.get_hue() < 255)){
                intakeMotor1.move(-127);
                pros::delay(110);
                intakeMotor1.move(127);
                pros::delay(20);
                intakeMotor1.brake();
                pros::delay(250);
                power = -127; 
                
            } else if(allianceColor == 1 && colorSensor.get_proximity() >= 140 && (colorSensor.get_hue() < 30 || colorSensor.get_hue()> 350)) {
                intakeMotor1.move(-127);
                pros::delay(110);
                intakeMotor1.move(127);
                pros::delay(20);
                intakeMotor1.brake();
                pros::delay(250);
                power = -127; 
            }
       } 

        pros::delay(20); // Save resources
    }

}
