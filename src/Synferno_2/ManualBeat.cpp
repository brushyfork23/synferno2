#include "ManualBeat.h"

void ManualBeat::begin() {
  tickCounter = 255;
  clockTickEvery.interval(MILLIS_PER_MINUTE / DEFAULT_BPM / CLOCK_TICKS_PER_BEAT);
}

boolean ManualBeat::update() {
    if ( clockTickEvery.check() ) {
        clockTickEvery.reset();

        // increment the clock
        tickCounter = (tickCounter + 1) % (CLOCK_TICKS_PER_BEAT * SCALE);
        return true;
    }
    return false;
}

byte ManualBeat::getCounter() {
  return tickCounter;
}

void ManualBeat::resetCounter() {
  tickCounter = 0;
}

void ManualBeat::setBPM(unsigned int bpm) {
    clockTickEvery.interval(MILLIS_PER_MINUTE / bpm / CLOCK_TICKS_PER_BEAT);
    clockTickEvery.reset();
}