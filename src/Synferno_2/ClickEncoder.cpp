#include "ClickEncoder.h"

// ----------------------------------------------------------------------------
// Button configuration (values for 1ms timer service calls)
//
#define ENC_BUTTONINTERVAL    10  // check button every x milliseconds, also debouce time
#define ENC_HOLDTIME        1200  // report held button after 1.2s

// ----------------------------------------------------------------------------

ClickEncoder::ClickEncoder(uint8_t CLK, uint8_t DT, uint8_t BTN, bool active)
  : delta(0), lastClkState(true), lastBtnState(false),
    button(Open),
    pinCLK(CLK), pinDT(DT), pinBTN(BTN), pinsActive(active)
{
  uint8_t configType = (pinsActive == LOW) ? INPUT_PULLUP : INPUT;
  pinMode(pinCLK, configType);
  pinMode(pinDT, configType);
  pinMode(pinBTN, configType);
}

// ----------------------------------------------------------------------------
// call this every 1 millisecond via timer ISR
//
void ClickEncoder::service(void)
{
  unsigned long now = millis();

  bool thisClkState = digitalRead(pinCLK) == pinsActive; // is the data pin active?
  if (thisClkState && !lastClkState) { // did the data pin just become active?
    if (digitalRead(pinDT) == HIGH) {
      delta++;
    } else {
      delta--;
    }
  }
  lastClkState = thisClkState;

  // handle button
  //
#ifndef WITHOUT_BUTTON
  static uint16_t keyDownTicks = 0;
  static unsigned long lastButtonCheck = 0;

  if (pinBTN > 0 // only check button if a pin has been provided
      && (now - lastButtonCheck) >= ENC_BUTTONINTERVAL) // checking button is sufficient every 10-30ms
  { 
    lastButtonCheck = now;
    
    bool thisBtnState = digitalRead(pinBTN) == pinsActive;
    if (thisBtnState) { // button is depressed
      if (thisBtnState == lastBtnState) { // button continues to be held
        keyDownTicks++;
        if (keyDownTicks > (ENC_HOLDTIME / ENC_BUTTONINTERVAL)) {
          button = Held;
        }
      } else { // button has just been pressed
        button = Clicked;
      }
    } else { // key is up
      if (button == Held) {
        button = Released;
      }
      keyDownTicks = 0;
    }
    lastBtnState = thisBtnState;
  }
#endif // WITHOUT_BUTTON

}

// ----------------------------------------------------------------------------

int16_t ClickEncoder::getValue(void)
{
  int16_t val;
  
  cli();

  val = delta;
  delta = 0;

  sei();
  
  return val;
}

// ----------------------------------------------------------------------------

#ifndef WITHOUT_BUTTON
ClickEncoder::Button ClickEncoder::getButton(void)
{
  ClickEncoder::Button ret = button;
  if (button != ClickEncoder::Held) {
    button = ClickEncoder::Open; // reset
  }
  return ret;
}
#endif
