#ifndef Sequence_h
#define Sequence_h

#include "Arduino.h"
#include <Streaming.h>

#define MAX_TICKS 96 // 24 ticks per beat, 4 beats per stanza

#define PRIORITY_NO 0
#define PRIORITY_LOW 1
#define PRIORITY_MEDIUM 2
#define PRIORITY_HIGH 3
#define PRIORITY_HIGHEST 4
#define N_PRIORITIES 5

enum poof_duration : uint8_t {
  DURATION_NONE,
  DURATION_SMALL,
  DURATION_LARGE
};

struct TickTriggers {
  poof_duration poofSizeA;
  poof_duration poofSizeB;
  poof_duration poofSizeC;
  poof_duration poofSizeD;
};

struct ChannelData {
  uint8_t priority;
  poof_duration duration;
};

struct TickData {
  struct ChannelData channel[4];
};

class Sequence {
  public:
    char title[10];
    struct TickData* ticks[MAX_TICKS];

    void init();

    // given the minimum ticks required to trigger a large poof, computed from the current bpm and the duration size,
    // set the priority we are capable of rendering
    void updateViablePriority(uint8_t ticksRequiredForLargePoof);

    // Should we fire now?
    TickTriggers getTickTriggers(uint8_t tickIndex);

  private:
    virtual void populate() = 0;

    int curPriority = PRIORITY_NO;
    
    uint8_t minTicksForPriority[N_PRIORITIES];
};

#endif