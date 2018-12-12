#include "Potentiometer.h"

void Potentiometer::begin(byte pin, byte sectors, word minimum, word maximum, byte smoothing) {

  this->pin = pin;
  this->smoothing = smoothing;
  this->minimum = minimum;
  this->maximum = maximum;
  this->sectors = sectors;

  pinMode(this->pin, INPUT);

  this->currentValue = analogRead(pin);
  if( sectors > 0 ) this->currentSector = map(this->currentValue, this->minimum, this->maximum, 0, (this->sectors - 1));

}

boolean Potentiometer::update() {
  // there's no good reason to sample more than 1/ms.  Nyquist frequency, etc.
  static Metro updateInterval(1UL);
  if( ! updateInterval.check() ) return( false );
  updateInterval.reset();

  // take a reading
  analogRead(pin); // toss first reading to ignore noise
  word newValue = analogRead(pin);

  // update with exponential smoothing
  if ( smoothing > 0 ) {
    newValue = (currentValue * (smoothing - 1) + newValue) / smoothing;
  }

  if ( sectors > 0 ) {
    // store current value
    this->currentValue = newValue;

    // collapse reading into sectors
    byte newSector = map(
        constrain(newValue, this->minimum, this->maximum), 
        this->minimum, this->maximum, 
        0, (this->sectors - 1)
    );

    // is there a change in sector?
    if ( newSector != this->currentSector ) {
      this->currentSector = newSector;
      return ( true );
    } else {
      return ( false );
    }
  } else {
    // is there a change in value?
    if ( newValue != this->currentValue ) {
      this->currentValue = newValue;
      return ( true );
    } else {
      return ( false );
    }
  }
}

word Potentiometer::getValue() {
  return ( this->currentValue );
}
byte Potentiometer::getSector() {
  return ( this->currentSector );
}


