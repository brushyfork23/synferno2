#ifndef Button_h
#define Button_h

#include <Arduino.h>
#include <Metro.h>

class Button{
  public:
    void begin(byte pin, boolean pressedValue=LOW);

    boolean update();

    byte getState();
    
  private:
    byte pressedValue, currentState, pin;
};

#endif
