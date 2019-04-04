// ----------------------------------------------------------------------------
// Rotary Encoder Driver
// Supports Click and Hold
//
// 2019
// Modified by Michael Black to work with a specific set of hardware
//
// (c) 2010 karl@pitrich.com
// (c) 2014 karl@pitrich.com
// 
// Timer-based rotary encoder logic by Peter Dannegger
// http://www.mikrocontroller.net/articles/Drehgeber
// ----------------------------------------------------------------------------

#ifndef __have__ClickEncoder_h__
#define __have__ClickEncoder_h__

// ----------------------------------------------------------------------------

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "Arduino.h"

// ----------------------------------------------------------------------------

class ClickEncoder
{
public:
  typedef enum Button_e {
    Open = 0,
    
    Held,
    Released,
    
    Clicked
    
  } Button;

public:
  ClickEncoder(uint8_t A, uint8_t B, uint8_t BTN = -1, bool active = LOW);

  void service(void);  
  int16_t getValue(void);

#ifndef WITHOUT_BUTTON
public:
  Button getButton(void);
#endif

private:
  const uint8_t pinCLK;
  const uint8_t pinDT;
  const uint8_t pinBTN;
  const bool pinsActive;
  volatile int16_t delta;
  volatile bool lastClkState;
  bool lastBtnState;
#ifndef WITHOUT_BUTTON
  volatile Button button;
#endif
};

// ----------------------------------------------------------------------------

#endif // __have__ClickEncoder_h__
