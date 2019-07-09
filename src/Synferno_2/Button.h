#ifndef Button_h
#define Button_h

#include <Arduino.h>
#include <Metro.h>

class Button{
  public:
    void begin(byte pin, boolean pressedValue=LOW);

    boolean update();

    boolean getState();
    
  private:
    byte pressedValue, pin;
    boolean currentState;
};

#endif
