#ifndef MIDI_h
#define MIDI_h

#include <Arduino.h>

#include <Metro.h>

// Relevant MIDI messages
#define MIDI_CLOCK 248
#define MIDI_START 250
#define MIDI_CONTINUE 251
#define MIDI_STOP 252

#define CLOCK_TICKS_PER_BEAT 24

#define SCALE 4 // the highest multiplier of clock ticks we are interested in counting to.
                // although there are 24 ticks per beat, if we want to trigger every four
                // beats then we'll need to count up to CLOCK_TICKS_PER_BEAT * SCALE

#define MICROS_PER_MINUTE 60000000UL

class MIDI{
  public:
    void begin();

    boolean update(); // process MIDI messages.

    byte getCounter(); // 0 to (CLOCK_TICKS_PER_BEAT * SCALE) - 1 ticks

    void resetCounter(); // set counter back to 0

    float getBPM();
    
  private:
    byte clockCounter, windowIndex;
    float bpm;

    unsigned long microsPerTick;
    unsigned long microsPetTickDeltas[CLOCK_TICKS_PER_BEAT];
    
    void processTick();
    static unsigned long sort_desc(const void *cmp1, const void *cmp2);
};

#endif
