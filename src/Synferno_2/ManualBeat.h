#ifndef ManualBeat_h
#define ManualBeat_h

#include <Arduino.h>

#include <Metro.h>

#define CLOCK_TICKS_PER_BEAT 24

#define SCALE 4 // the highest multiplier of clock ticks we are interested in counting to.
                // although there are 24 ticks per beat, if we want to trigger every four
                // beats then we'll need to count up to CLOCK_TICKS_PER_BEAT * SCALE

#define DEFAULT_BPM 120.0
#define MILLIS_PER_MINUTE 60000

class ManualBeat{
  public:
    void begin();

    boolean update();

    byte getCounter(); // 0 to (CLOCK_TICKS_PER_BEAT * SCALE) - 1 ticks

    void resetCounter(); // set counter back to 0

    void setBPM(unsigned int bpm);
    
  private:
    byte tickCounter;

    Metro clockTickEvery;
};

#endif