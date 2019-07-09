#ifndef Sequence_h
#define Sequence_h

#include "Arduino.h"

#define MAX_TICKS 96 // 24 ticks per beat, 4 beats per stanza

enum trigger_priority : uint8_t {
  PRIORITY_NO = 0,
  PRIORITY_LOW,
  PRIORITY_MEDIUM,
  PRIORITY_HIGH,
  PRIORITY_HIGHEST,

  N_PRIORITIES
};

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
  trigger_priority priority;
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
    uint8_t curPriority = PRIORITY_NO;
    uint8_t minTicksForPriority[N_PRIORITIES];
    
    virtual void populateTickData() = 0;
    void populateMinimumRequirementsForTriggers();

    
};

#endif