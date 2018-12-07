// Compile for Arduino Nano

#include <Streaming.h>
#include <Metro.h>

// Potentiometers
#include "Potentiometer.h"
Potentiometer duration, offset;

#define MIDI_CLOCKS_PER_BEAT 24 // from

void setup() {
  Serial.begin(115200);

  // knobs
  duration.begin(POT_PIN1, 12, 0, 7000);
  offset.begin(POT_PIN2, MIDI_CLOCKS_PER_BEAT, 0, 7000);

}

void loop() {

  duration.update();
  offset.update();

  static Metro printEvery(50UL);
  if ( printEvery.check() ) {
//    Serial << F("Duration.") << F(" val: ") << duration.getValue() << F(" sec: ") << duration.getSector() << F(" val: ") << analogRead(POT_PIN1) << endl;
//    Serial << F("Offset.") << F(" val: ") << offset.getValue() << F(" sec: ") << offset.getSector() << F(" val: ") << analogRead(POT_PIN2) << endl;
//    Serial << F("Frequency.") << F(" val: ") << frequency.getValue() << F(" sec: ") << frequency.getSector() << F(" val: ") << analogRead(POT_PIN3) << endl;
//    Serial << F("Unused.") << F(" val: ") << options.getValue() << F(" sec: ") << options.getSector() << F(" val: ") << analogRead(POT_PIN4) << endl;

    printEvery.reset();

    Serial << duration.getSector() << "\t" << duration.getValue() << "\t" << offset.getSector() << "\t" << offset.getValue() << endl;
  }

}

