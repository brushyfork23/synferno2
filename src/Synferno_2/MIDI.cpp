#include "MIDI.h"
#include <Streaming.h> // TODO: can this be removed?

void MIDI::begin() {
  // give MIDI-device a short time to "digest" MIDI messages
  //MIDISerial.begin(31250);
  Serial1.begin(31250);
  delay(100);

  clockCounter = 255; // no MIDI signal; we're "off the clock".
  tickDuration = 20833; // us, 120 bpm
  beatDuration = 500; // ms, 120 bpm
  clocksPerTrigger = MIDI_CLOCKS_PER_BEAT;
}

boolean MIDI::update() {
  // in case the midi drops out
  static Metro timeoutMIDI(1000UL);

  if (Serial1.available() > 0) {

    byte midiByte = Serial1.read();
//    byte midiChannel = midiByte & B00001111;
//    byte midiCommand = midiByte & B11110000;

    // We get 24 clock ticks per beat.
    if (midiByte == MIDI_CLOCK) {
      timeoutMIDI.reset();
      processTick();
      return ( true );
    }
  }

  if ( SIMULATE_MIDI ) {
    const float beatEvery = 60.0 * 1000.0 / MIDI_CLOCKS_PER_BEAT / SIMULATE_BPM; // ms/tick
    static Metro clockEvery(beatEvery);
    if ( clockEvery.check() ) {
      clockEvery.reset();

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

byte MIDI::getBeatCounter() {
  return clockCounter % MIDI_CLOCKS_PER_BEAT;
}

void MIDI::resetCounter() {
  clockCounter = 0;
}

void MIDI::setClocksPerTrigger(byte ticks) {
  this->clocksPerTrigger = ticks;
}

byte MIDI::getClocksPerTrigger() {
  return this->clocksPerTrigger;
}

void MIDI::processTick() {
  // increment the clock
  clockCounter = (clockCounter + 1) % (MIDI_CLOCKS_PER_BEAT * SCALE);

  // time the ticks
  static unsigned long lastTick = micros();
  unsigned long thisTick = micros();
  unsigned long deltaTick = thisTick - lastTick;
  lastTick = thisTick;

  // apply exponential smoothing, in case we miss a tick
  const word smoothTick = 100;
  tickDuration = (tickDuration*(smoothTick-1) + deltaTick)/smoothTick;

  // time the beats
  if( clockCounter % MIDI_CLOCKS_PER_BEAT == 0 ) {
    // time the beats
    static unsigned long lastBeat = millis();
    unsigned long thisBeat = millis();
    unsigned long deltaBeat = thisBeat - lastBeat;
    lastBeat = thisBeat;
    
    // apply exponential smoothing, in case we miss a tick
    const word smoothBeat = 20;
    beatDuration = (beatDuration*(smoothBeat-1) + deltaBeat)/smoothBeat;

  }
}

unsigned long MIDI::tickLength() {
  // length of ticks, uS
  return( this->tickDuration );
}
unsigned long MIDI::beatLength() {
  // length of 24 ticks (one beat), ms
  return( this->beatDuration );
}

