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
  okapi::ControllerDigital buttonList[5] = {okapi::ControllerDigital::A, okapi::ControllerDigital::up, okapi::ControllerDigital::X, okapi::ControllerDigital::L1, okapi::ControllerDigital::R1};
  void handleButtons(okapi::Controller controller);
  int getCount(okapi::ControllerDigital id);
  bool getPressed(okapi::ControllerDigital id);
  void init();
};

#endif
