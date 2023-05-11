#ifndef _MOTOR_HPP
#define _MOTOR_HPP
#include "mbed.h"

class Motor {
public:
  Motor();
  Motor(PinName pinName1, PinName pinName2, PinName pinName3, PinName pinName4);
  void Fwd(float time);
  void Rev(float time);
  void Stop(void);
  int Speed(float speedA, float speedB);
  void Period_in_ms(int msPeriod);

private:
  PwmOut pin1;
  PwmOut pin2;
  PwmOut pin3;
  PwmOut pin4;
};

// int motor(float speedA, float speedB);

#endif
