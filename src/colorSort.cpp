#include "colorSort.h"

bool colorSortOn = true; 
int allianceColor;   //0 = red (sorts out blue), 1 = blue (sorts out red)  //2 stops intake whenever ring is detected, //3 stops intake whenever red ring is detected //4 stops intake whenver blue ring is detected
int power = -127; 

void colorSortTask(void* param) {
     while(true){
        if(colorSortOn) {
            intakeMotor1.move(-127);
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

                } else if(allianceColor == 2 && colorSensor.get_proximity() >= 140)  {
                    intakeMotor1.brake(); 
                    power = -127; 
                    colorSortOn = false;    


                } else if(allianceColor == 3 && colorSensor.get_proximity() >= 140 && (colorSensor.get_hue() < 30 || colorSensor.get_hue()> 350)){

                    intakeMotor1.move(32);
                    pros::delay(100);
                    intakeMotor1.brake(); 

                    power = -127;
                    colorSortOn = false; 
                } else if (allianceColor == 4 && colorSensor.get_proximity() >= 140 && (colorSensor.get_hue() > 180 && colorSensor.get_hue()< 255)){
                    intakeMotor1.move(32);
                    pros::delay(100);
                    intakeMotor1.brake(); 
                }
        }
        pros::delay(10); // Save resources
    }
}
