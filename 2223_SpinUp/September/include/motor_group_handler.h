#ifndef MOTOUR_GROUP_HANDLER_H
#define MOTOUR_GROUP_HANDLER_H

#include "main.h"
#include "ports.h"
#include <vector>
#include <initializer_list>
#include <unordered_map>

using okapi::Motor;

// Better version of okapi MotorGroup

class MotorInfo {

private:

  std::string color;
  int maxRpm;
  okapi::AbstractMotor::gearset gearset;

  MotorInfo(const std::string& _color, int maxRpm, okapi::AbstractMotor::gearset _gearset):
    color(_color), maxRpm(_maxRpm), gearset(_gearset)
  {

  }

public:

  static const MotorInfo RED_MOTOR_INFO = MotorInfo("red", 100, okapi::AbstractMotor::gearset::red);
  static const MotorInfo GREEN_MOTOR_INFO = MotorInfo("green", 200, okapi::AbstractMotor::gearset::green);
  static const MotorInfo BLUE_MOTOR_INFO = MotorInfo("blue", 600, okapi::AbstractMotor::gearset::blue);

  const std::string& getColor() const{
    return color;
  }

  int getMaxRpm() const {
    return maxRpm;
  }

  okapi::AbstractMotor::gearset getGearset() const{
    return gearset;
  }

};

template<size_t N>

class MotorGroupHandler {

    private:

        std::vector<Motor> motors;

        double previousPower;

        MotorInfo info;

    public:

        MotorGroupHandler(const MotorInfo& _info, const std::array<int, N>& _ports):  info(_info), previousPower(0), motors(){
          motors.reserve(N);
          for(int i : _ports){
            motors.emplace_back(i);
          }
        }

        void moveAbsolute(double position, unsigned int maxVelocity){
          for(Motor m : motors){
            m.moveAbsolute(position, maxVelocity);
          }
        }

        void moveAbsolute(double position){
          moveAbsolute(info.maxRpm);
        }

        void moveRelative(double position, unsigned int maxVelocity){
          for(Motor m : motors){
            m.moveAbsolute(position, maxVelocity);
          }
        }

        void moveRelative(double position){
          moveRelative(info.maxRpm);
        }

        double getPosition(){
          double currentPositionSum = 0;
          for(Motor m: motors){
            currentPositionSum += m.getPosition();
          }
          return currentPositionSum/N;
        }

        void tarePosition(){
          for(Motor m: motors){
            m.tarePosition();
          }
        }

        void setBrakeMode(okapi::AbstractMotor::brakeMode mode){
          for(Motor m: motors){
            m.setBrakeMode(mode);
          }
        }

        void moveVelocity(int velocity){
          for(Motor m : motors){
            m.moveVelocity(velocity);
          }
        }

        void moveVelocity(){
          moveVelocity(info.maxRpm);
        }

        void moveVoltage(double power = 12000) {
            for(Motor m: motors){
                m.moveVoltage(power);
            }
        }

        void toggle(double power = 12000){
            if (previousPower != power) {
                moveVoltage(power);
                previousPower = power;
            } else {
                moveVoltage(0);
                previousPower = 0;
            }
        }

};

#endif
