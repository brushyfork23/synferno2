// Compile for Arduino Nano

#include <Streaming.h>
#include <Metro.h>

// OLED
#include <U8x8lib.h>
#include "OLED.h"
OLED oled;

// MIDI
#include <SoftwareSerial.h>
#include "MIDI.h"
MIDI midi;

// Solenoids
#include "Solenoid.h"
Solenoid fireLeft, fireRight;

// Potentiometers
#include "Potentiometer.h"
Potentiometer duration, offset, frequency;
#define FREQUENCY_SECTORS 5   // number of frequency options (keep odd so knob at 12:00 means default)
#define FREQUENCY_DEVIATION 4 // multiplier (for max) and divisor (for min) of beats per poof (must be 1 through 10)

// Fire button
#include "Button.h"
Button makeFireNow;

void setup() {
  Serial.begin(115200);

  // fire up the output led
  oled.begin();

  // fire up MIDI
  midi.begin();
  showMIDI(midi.getCounter());

  // fire up the fire
  fireLeft.begin(SOLENOID_PIN1);
  showFireLeft(fireLeft.getState());
  fireRight.begin(SOLENOID_PIN2);
  showFireRight(fireRight.getState());

  // knobs
  duration.begin(POT_PIN1, MIDI_CLOCKS_PER_BEAT);
  showDuration(duration.getSector());
  offset.begin(POT_PIN2, MIDI_CLOCKS_PER_BEAT);
  showOffset(offset.getSector());
  frequency.begin(POT_PIN3, FREQUENCY_SECTORS);
  showFrequency(frequency.getSector());

  // buttons
  makeFireNow.begin(BUTTON_PIN1);
  showMakeFireNow(makeFireNow.getState());
}

void loop() {
  // 1. update the inputs
  if ( duration.update() ) {
    // have a change in duration
    showDuration(duration.getSector());
  }
  if ( offset.update() ) {
    // have a change in offset
    showOffset(offset.getSector());
  }
  if ( frequency.update() ) {
    // have a change in frequency
    showFrequency(map(frequency.getSector(), 0, FREQUENCY_SECTORS-1, 0 - ((FREQUENCY_SECTORS -1) / 2), (FREQUENCY_SECTORS-1) / 2));
  }

  // 2. decode the MIDI situation
  // if there's no MIDI signal and we're not manually firing, shut it down.
  if( midi.getCounter()==255 && !makeFireNow.getState() ) {
    // shut it down
    fireLeft.off();
    fireRight.off();
  }  
  // if we have a MIDI update and we're not manually firing, do stuff.
  if( midi.update() && !makeFireNow.getState() ) {
    // we have a MIDI signal to follow
    byte counter = midi.getCounter();

    // use frequency knob to adjust how long we wait between poofs (scale MIDI clock signals per beat)
    byte clocksPerPoof = map(frequency.getSector(), 0, FREQUENCY_SECTORS-1, FREQUENCY_DEVIATION * MIDI_CLOCKS_PER_BEAT, MIDI_CLOCKS_PER_BEAT / FREQUENCY_DEVIATION);

    // how far back from the poof do we need to trigger the hardware?
    byte fireOnAt = (clocksPerPoof - offset.getSector()) % clocksPerPoof;
    if ( counter == fireOnAt ) {
      // turn on the fire
      fireLeft.on();
      fireRight.on();
    }

    // and when do we need to turn it off?
    byte fireOffAt = (fireOnAt + duration.getSector()) % clocksPerPoof;
    if ( counter == fireOffAt ) {
      // turn off the fire
      fireLeft.off();
      fireRight.off();
    }

    // report tick, noting we do this after the hardware-level update
    showMIDI(midi.getCounter());
  }


  // 3. override with the Make Fire Now button
  if ( makeFireNow.update() ) {
    // have a change in the make fire now button
    // do the thing
    manualFiring(makeFireNow.getState());

    // report manual, noting we do this after the hardware-level update
    showMakeFireNow(makeFireNow.getState());
  }

  // 4. report firing status

  if ( fireLeft.update() ) {
    // have a change in solenoid status
    showFireLeft(fireLeft.getState());
  }
  if ( fireRight.update() ) {
    // have a change in solenoid status
    showFireRight(fireRight.getState());
  }

  // MISC. code for debugging, reporting, etc. to the Serial line

  // We need MIDI_CLOCKS_PER_BEAT updates per beat, so minimum updates per second is:
  static word updateFloor = MIDI_CLOCKS_PER_BEAT * 200 / 60;

  // track updates per second.
  static unsigned long counter = 0;
  counter ++;
  static Metro updateInterval(1000UL);
  if ( updateInterval.check() ) {
    Serial << F("Updates per second: ") << counter << endl;
    if ( counter < updateFloor ) Serial << F("CAUTION: loop() < updateFloor!!") << endl;
    counter = 0;
    updateInterval.reset();
  }
}

// BOOOOSH!
void manualFiring(boolean doFire) {
  if ( doFire ) {
    fireLeft.on();
    fireRight.on();
  } else {
    fireLeft.off();
    fireRight.off();
  }
}

// the OLED display is hella-slow, so we want to be careful about how much we print there.
// much of this code is just being "smart" about updating the OLED.

void showFireLeft(boolean state) {
  static boolean lastState = !state;
  static boolean startup = true;
  const byte thisRow = 7;

  if ( startup ) {
    oled.buffer = "<. Synferno  .>";
    showLabel(thisRow);
    startup = false;
  }
  if ( lastState != state ) {
    lastState = state;
    if ( state ) {
      oled.buffer = "F";
    }
    else {
      oled.buffer = ".";
    }
    oled.write(thisRow, 1);
  }
}

void showFireRight(boolean state) {
  static boolean lastState = !state;
  static boolean startup = true;
  const byte thisRow = 7;

  if ( startup ) {
    oled.buffer = "<. Synferno  .>";
    showLabel(thisRow);
    startup = false;
  }
  if ( lastState != state ) {
    lastState = state;
    if ( state ) {
      oled.buffer = "F";
    }
    else {
      oled.buffer = ".";
    }
    oled.write(thisRow, 13);
  }
}

void showMakeFireNow(boolean state) {
  static boolean lastState = !state;
  static boolean startup = true;
  const byte thisRow = 4;

  if ( startup ) {
    oled.buffer = "MFN:  ";
    showLabel(thisRow);
    startup = false;
  }
  if ( lastState != state ) {
    lastState = state;
    if ( state ) {
      oled.buffer = "X";
    }
    else {
      oled.buffer = ".";
    }
    oled.write(thisRow, 6);
  }
}

void showMIDI(byte count) {
  static byte lastCount = 255;
  static boolean startup = true;
  const byte thisRow = 0;

  if ( startup ) {
    oled.buffer = "MIDI: ";
    showLabel(thisRow);
    startup = false;
  }

  if ( lastCount != count ) {
    lastCount = count;
    if ( count == 0 ) {
      oled.buffer = "X";
      oled.write(thisRow, 6); // don't pad, place at a specific location
    }
    if ( count == 3 ) {
      oled.buffer = ".";
      oled.write(thisRow, 6); // don't pad, place at a specific location
    }
  }
}

void showDuration(byte count) {
  static byte lastCount = 255;
  static boolean startup = true;
  const byte thisRow = 1;

  if ( startup ) {
    oled.buffer = "Dur:  ";
    showLabel(thisRow);
    startup = false;
  }
  if ( lastCount != count ) {
    lastCount = count;
    showCounter(thisRow, 6, count);
  }
}

void showOffset(byte count) {
  static byte lastCount = 255;
  static boolean startup = true;
  const byte thisRow = 2;

  if ( startup ) {
    oled.buffer = "Off:  ";
    showLabel(thisRow);
    startup = false;
  }
  if ( lastCount != count ) {
    lastCount = count;
    showCounter(thisRow, 6, count);
  }
}

void showFrequency(int step) {
  static int lastStep = 0;
  static boolean startup = true;
  const byte thisRow = 3;

  if ( startup ) {
    oled.buffer = "Freq: ";
    showLabel(thisRow);
    startup = false;
  }
  if ( lastStep != step ) {
    lastStep = step;
    showCounter(thisRow, 6, step);
  }
}

void showLabel(byte row) {
  oled.write(row, 0, true); // pad
}

void showCounter(byte row, byte col, int counter) {
  oled.buffer = String(counter);
  if ( oled.buffer.length() < 2 ) oled.buffer += " ";
  oled.write(row, col); // don't pad, place at a specific location
}

