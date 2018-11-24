#include "ButtonGroup.h"

void ButtonGroup::begin(byte pins[], byte numPins, byte minValue, byte maxValue, boolean toggle, boolean pressedValue) {

  this->numPins = numPins;

  this->buttons = new Bounce[numPins];
  for (int i = 0; i < numPins; i++) {
    this->buttons[i].attach( pins[i] , INPUT_PULLUP  );
    this->buttons[i].interval(25);
  }

  this->update();
}

boolean ButtonGroup::update() {
   // there's no good reason to sample more than 1/ms.  Nyquist frequency, etc.
  static Metro updateInterval(1UL);
  if( ! updateInterval.check() ) return( false );
  updateInterval.reset();

  byte newSelected = -1;
  // read each button
  for (int i = 0; i < this->numPins; i++)  {
    this->buttons[i].update();
    if (this->buttons[i].fell()) {
      // If multiple buttons had been pressed simultaniously, the highest index button will be used
      newSelected = i;
    }
  }

  if (newSelected != this->currentSelected) { // new selection was made
    this->currentSelected = newSelected;
    return true;
  } else if (this->currentSelected != -1 && this->toggle){ // current button was de-selected
    this->currentSelected = -1;
    return true;
  }
  return false; // no selection was made or re-press does not de-select due to toggle state.
}

byte ButtonGroup::getState() {
  return( this->currentState );
}

boolean ButtonGroup::hasSelection() {
  return this->getValue() >= 0;
}
