#include "button.h"

Button::Button() {
  But but;
  for(okapi::ControllerDigital x : buttonList) {
    but = {false, 0};
    std::pair<okapi::ControllerDigital , But> myBut (x,but);
    buttons.insert(myBut);
  }
}

//handle button counts and states
void Button::handleButtons(Controller controller) {
  for (auto& [key, value]: buttons) {
    if(controller.getDigital(key) && !value.state) {
      value.state = true;
      value.count++;
    }
    else if(!controller.getDigital(key) && value.state) {
      value.state = false;
    }
  }
}

//return counts
int Button::getCount(okapi::ControllerDigital id) {
  return buttons[id].count;
}

//return states
bool Button::getPressed(okapi::ControllerDigital id) {
  return buttons[id].state;
}
