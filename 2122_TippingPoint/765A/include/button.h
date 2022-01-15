#ifndef _BUTTON_
#define _BUTTON_
#include "main.h"


//structure to store button state and count
struct But {
  bool state;
  int count;
};

//class to handle all controller buttons
class Button {
private:
  std::unordered_map<okapi::ControllerDigital, But> buttons;
public:
  Button();
  okapi::ControllerDigital buttonList[7] = {okapi::ControllerDigital::L1,okapi::ControllerDigital::Y, okapi::ControllerDigital::X, okapi::ControllerDigital::right, okapi::ControllerDigital::R1, okapi::ControllerDigital::L2, okapi::ControllerDigital::R2};
  void handleButtons(okapi::Controller controller);
  int getCount(okapi::ControllerDigital id);
  bool getPressed(okapi::ControllerDigital id);
  void init();
};

#endif
