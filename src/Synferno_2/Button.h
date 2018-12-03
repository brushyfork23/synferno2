#ifndef Button_h
#define Button_h

#include <Arduino.h>
#include <Metro.h>

// pins
#define POOF_BOTH_BUTTON_PIN 0
#define RESET_BUTTON_PIN 19

class Button{
  public:
    void begin(byte pin, boolean pressedValue=LOW);

    boolean update();

    byte getState();
    
  private:
    byte pressedValue, currentState, pin;
};

#endif
