/**
This class abstracts control of a group of buttons.
Provide an array of button pins and then call update() to be notified of a new press.
When the `toggle` flag is true, pressing a selected button will deselect it,
whereas if the flag is false a repress will cause no state change.
In the case of multiple simultanious presses, TODO
*/
#ifndef ButtonGroup_h
#define ButtonGroup_h

#include <Arduino.h>
#include <Bounce2.h>
#include <Metro.h>

class ButtonGroup{
  public:
    void begin(byte pins[], byte numPins, byte minValue=0, byte maxValue=NUM_BUTTONS-1, boolean toggle=true, boolean pressedValue=LOW);

    boolean update();

    byte getState();
    
  private:
    byte pressedValues[], currentStates[], pins[], selected;
    Bounce buttons[];
};

#endif
