#ifndef _BUTTON_
#define _BUTTON_
#include "main.h"



struct But {
  bool state;
  int count;
};

class Button {
private:
  std::unordered_map<okapi::ControllerDigital, But> buttons;
public:
  Button();
  okapi::ControllerDigital buttonList[8] = {okapi::ControllerDigital::Y, okapi::ControllerDigital::right, okapi::ControllerDigital::X, okapi::ControllerDigital::L1, okapi::ControllerDigital::R1, okapi::ControllerDigital::L2, okapi::ControllerDigital::R2, okapi::ControllerDigital::Y};
  void handleButtons(okapi::Controller controller);
  int getCount(okapi::ControllerDigital id);
  bool getPressed(okapi::ControllerDigital id);
  void init();
};

#endif
