#include "intake.h"

Intake::Intake(double port) : m(port), e(port)
{
  m.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
  e.reset();
}

void Intake::addPosition(int pos) {
  encPositions.push_back(pos);
}

void Intake::run(bool left, bool right, double speed) {
  if(left) {
    m.moveVelocity(speed);
  }
  if(right) {
    m.moveVelocity(-speed);
  }
  else if(!left && !right) {
    m.moveVelocity(0);
  }
}

void Intake::stepAbsolute(int count, double speed) {
  printf("count: %d\n", count % encPositions.size());
  if(prevCount != count) {
    double target = encPositions[count % encPositions.size()];
    m.moveAbsolute(target, speed);
  }
  prevCount = count;
}
/*
void Intake::step() {
  if(moving) {
    if(dir) {
      if(e.get()<target)
        run(200);
      else
        moving = false;
    }
    else {
      if(e.get()>target)
        run(-200);
      else
        moving = false;
    }
  }
  else {
    run(0);
  }
}

void Intake::setTarget(double enc) {
  if(target>enc) {
    dir = true;
  }
  else {
    dir = false;
  }
  target = enc;
  moving = true;
}
*/
