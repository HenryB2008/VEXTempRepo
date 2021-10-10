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
  okapi::ControllerDigital buttonList[2] = {okapi::ControllerDigital::A, okapi::ControllerDigital::up};
  void handleButtons(okapi::Controller controller);
  int getCount(okapi::ControllerDigital id);
  void init();
};

#endif
