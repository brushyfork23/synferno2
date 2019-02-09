#include "MIDI.h"

void MIDI::begin() {
  // give MIDI-device a short time to "digest" MIDI messages
  Serial2.begin(31250);
  delay(100);

  
  this->clockCounter = 255; // no MIDI signal; we're "off the clock".
  this->microsPerTick = 500000 / CLOCK_TICKS_PER_BEAT; // 120 bpm
}

boolean MIDI::update() {
  // in case the midi drops out
  static Metro timeoutMIDI(1000UL);

  if (Serial2.available() > 0) {

    byte midiByte = Serial2.read();
//    byte midiChannel = midiByte & B00001111;
//    byte midiCommand = midiByte & B11110000;

    // We get 24 clock ticks per beat.
    if (midiByte == MIDI_CLOCK) {
      timeoutMIDI.reset();
      processTick();
      return ( true );
    }
  }

  if ( timeoutMIDI.check() ) clockCounter = 255; // loss of signal

  return ( false );
}

byte MIDI::getCounter() {
  return clockCounter;
}

void MIDI::resetCounter() {
  clockCounter = 0;
}

void MIDI::processTick() {
  // increment the clock
  clockCounter = (clockCounter + 1) % (CLOCK_TICKS_PER_BEAT * SCALE);

  // time the ticks
  static unsigned long lastTick = micros();
  unsigned long thisTick = micros();
  unsigned long deltaTick = thisTick - lastTick;
  lastTick = thisTick;

  // store a rolling window of micros-between-ticks deltas
  microsPetTickDeltas[windowIndex] = deltaTick;
  if (++windowIndex % CLOCK_TICKS_PER_BEAT == 0) {
    windowIndex = 0;
  }

  // sort the window
  qsort(microsPetTickDeltas, CLOCK_TICKS_PER_BEAT, sizeof(microsPetTickDeltas[0]), this->sort_desc);

  // smooth the median delta
  unsigned long medianDelta = microsPetTickDeltas[CLOCK_TICKS_PER_BEAT/2];
  const word smoothFactor = 20;
  microsPerTick = (microsPerTick*(smoothFactor-1) + medianDelta)/smoothFactor;

  // every quarter beat, update the BPM
  if (clockCounter % (CLOCK_TICKS_PER_BEAT / SCALE) == 0 && microsPerTick > 0) {
    this->bpm = MICROS_PER_MINUTE * 1.0 / CLOCK_TICKS_PER_BEAT / microsPerTick;
    return;
  }
}

float MIDI::getBPM() {
  return( this->bpm );
}

// qsort requires you to create a sort function
static unsigned long MIDI::sort_desc(const void *cmp1, const void *cmp2)
{
  // Need to cast the void * to unsigned long *
  unsigned long a = *((unsigned long *)cmp1);
  unsigned long b = *((unsigned long *)cmp2);
  // The comparison
  return b - a;
}