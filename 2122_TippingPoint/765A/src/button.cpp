#include "button.h"

Button::Button() {
  But but;
  for(okapi::ControllerDigital x : buttonList) {
    but = {false, 0};
    std::pair<okapi::ControllerDigital , But> myBut (x,but);
    buttons.insert(myBut);
  }
}

void Button::handleButtons(Controller controller) {
  for (auto& [key, value]: buttons) {
    if(controller.getDigital(key) && !value.state) {
      value.state = true;
      value.count++;
      if(key == okapi::ControllerDigital::A && value.count % 3 == 2) {
        buttons[okapi::ControllerDigital::up].count = 2;
      }
      if(key == okapi::ControllerDigital::X && value.count %2 ==1) {
        buttons[okapi::ControllerDigital::up].count = 0;
      }
    }
    else if(!controller.getDigital(key) && value.state) {
      value.state = false;
    }
  }
}

int Button::getCount(okapi::ControllerDigital id) {
  return buttons[id].count;
}

bool Button::getPressed(okapi::ControllerDigital id) {
  return buttons[id].state;
}
