
// Compile for Sparkfun ESP32 Thing

#include <Streaming.h>
#include <Metro.h>

// OLED
#include <U8x8lib.h>
#include "OLED.h"
OLED oled;

// MIDI
#include "MIDI.h"
MIDI midi;

// Solenoids
#include "Solenoid.h"
Solenoid fireLeft, fireRight;

// Potentiometers
#include "Potentiometer.h"
Potentiometer duration, offset;

// Fire button
#include "Button.h"
Button makeFireNow;
Button resetCounter;

// Web Portal
#include "Portal.h"

byte midiDelay = 0;

void setup() {
  Serial.begin(115200);

  // fire up the output screen
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
  duration.begin(POT_PIN1, 12, 13, 340);
  showDuration(duration.getSector());

  offset.begin(POT_PIN2, MIDI_CLOCKS_PER_BEAT, 14, 545);
  showOffset(offset.getSector());

  // buttons
  makeFireNow.begin(BUTTON_PIN1);
  showMakeFireNow(makeFireNow.getState());
  resetCounter.begin(BUTTON_PIN2);

  // web portal
  Serial.println("Configuring access point...");
  portal.begin();
  Serial.print("IP address: ");
  Serial.println(portal.getIp());
  Serial.print("Hostname: ");
  Serial.println(portal.getHostname());
}

void loop() {
  // 1. handle web portal
  portal.update();

  // 2. update the inputs
  if ( duration.update() ) {
    // have a change in duration
    showDuration(duration.getSector());
  }
  if (portal.getOffset() != midiDelay) {
    // web portal has changed offset
    midiDelay = portal.getOffset();
  }
  if ( offset.update() ) {
    // console has changed offset.  Override web portal settings
    midiDelay = offset.getSector();
    portal.setOffset(midiDelay);
    showOffset(midiDelay);
  }  
  if (resetCounter.update() && resetCounter.getState()) {
    // reset button has just been pressed.  Reset the MIDI clock.
    Serial << F("reset counter") << endl;
    midi.resetCounter();
  }

  // 3. decode the MIDI situation
  // if there's no MIDI signal and we're not manually firing, shut it down.
  if( midi.getCounter()==255 && !makeFireNow.getState() ) {
    // shut it down
    fireLeft.off();
    fireRight.off();
  }  
  // if we have a MIDI update and we're not manually firing, do stuff.
  if( midi.update() && !makeFireNow.getState()) {

    // we have a MIDI signal to follow
    byte counter = midi.getCounter();

    // how far back from the poof do we need to trigger the hardware?
    byte fireOnAt = (MIDI_CLOCKS_PER_BEAT - midiDelay) % MIDI_CLOCKS_PER_BEAT;
    
    // and when do we need to turn it off?
    byte fireOffAt = (fireOnAt + duration.getSector()) % MIDI_CLOCKS_PER_BEAT;

    // given the current counter and on/off times, should we shoot fire or not?
    if( timeForFire( counter, fireOnAt, fireOffAt ) ) {
      // turn on the fire
      fireLeft.on();
      fireRight.on();
    } else {
      // turn off the the fire
      fireLeft.off();
      fireRight.off();
    }

    // report tick, noting we do this after the hardware-level update
    showMIDI(midi.getCounter());
  }

  // 4. override with the Make Fire Now button
  if ( makeFireNow.update() ) {
    // have a change in the make fire now button
    // do the thing
    manualFiring(makeFireNow.getState());

    // report manual, noting we do this after the hardware-level update
    showMakeFireNow(makeFireNow.getState());
  }

  // 5. report firing status

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

// helper function to work through the modulo-24 stuff.  PITA.
boolean timeForFire( byte clock, byte start, byte stop ) {
  // edge case
  if( start == stop ) return( false );

  // easy case.
  if( stop > start ) {
    if( clock >= start && clock < stop ) return( true );
    else return( false );
  }

  // so, start > stop
  // harder case, with the modulo-24 stuff.  Ugh.
  if( clock >= stop && clock < start ) return( false );
  else return( true );
  
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
  const byte thisRow = 5;

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

void showLabel(byte row) {
  oled.write(row, 0, true); // pad
}

void showCounter(byte row, byte col, int counter) {
  oled.buffer = String(counter);
  if ( oled.buffer.length() < 2 ) oled.buffer += " ";
  oled.write(row, col); // don't pad, place at a specific location
}
