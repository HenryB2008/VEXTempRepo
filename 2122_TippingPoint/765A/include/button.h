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
  okapi::ControllerDigital buttonList[9] = {okapi::ControllerDigital::L1,okapi::ControllerDigital::A, okapi::ControllerDigital::X, okapi::ControllerDigital::right, okapi::ControllerDigital::R1, okapi::ControllerDigital::L2, okapi::ControllerDigital::R2, okapi::ControllerDigital::B, okapi::ControllerDigital::left};
  void handleButtons(okapi::Controller controller);
  int getCount(okapi::ControllerDigital id);
  bool getPressed(okapi::ControllerDigital id);
  void init();
};

#endif
