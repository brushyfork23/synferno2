#include "ButtonGroup.h"

void ButtonGroup::begin(byte numPins, byte button_pins[], byte led_pins[], boolean toggle) {
  this->led_pins = led_pins;

  this->numPins = numPins;

  this->toggle = toggle;

  this->buttons = new Bounce[numPins];
  for (int i = 0; i < numPins; i++) {
    this->buttons[i].attach( button_pins[i] , INPUT_PULLUP  );
    this->buttons[i].interval(25);

    pinMode(led_pins[i], OUTPUT);
    // default to low illumination
    analogWrite(led_pins[i], BRIGHTNESS_DIM_WHITE);
  }

  this->update();
}

boolean ButtonGroup::update() {
   // there's no good reason to sample more than 1/ms.  Nyquist frequency, etc.
  static Metro updateInterval(1UL);
  if( ! updateInterval.check() ) return( false );
  updateInterval.reset();

  byte newSelected = 255;
  boolean hasStateChange = false;
  // read each button
  for (int i = 0; i < this->numPins; i++)  {
    this->buttons[i].update();
    if (this->buttons[i].fell()) {
      hasStateChange = true;
      // If multiple buttons had been pressed simultaniously, the highest index button will be used
      newSelected = i;
    }
  }

  if (!hasStateChange) {
    return false;
  }

  if (newSelected != this->currentSelected) { // new selection was made
    this->currentSelected = newSelected;
    this->writeLEDs();
    return true;
  } else if (this->currentSelected != 255 && this->toggle){ // current button was de-selected
    this->currentSelected = 255;
    this->writeLEDs();
    return true;
  }
  return false; // no selection was made or re-press does not de-select due to toggle state.
}

byte ButtonGroup::getValue() {
  return( this->currentSelected );
}

boolean ButtonGroup::hasSelection() {
  return this->getValue() != 255;
}

void ButtonGroup::writeLEDs() {
  for (int i = 0; i < this->numPins; i++) {
    if (i == this->currentSelected) {
      analogWrite(led_pins[i], BRIGHTNESS_BRIGHT_WHITE);
    } else {
      analogWrite(led_pins[i], BRIGHTNESS_DIM_WHITE);
    }
  }
}