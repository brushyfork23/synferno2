#ifndef Sequence_h
#define Sequence_h

#include "Arduino.h"

#define MAX_TICKS 96 // 24 ticks per beat, 4 beats per stanza

enum trigger_priority : uint8_t {
  PRIORITY_LOW = 0,
  PRIORITY_MEDIUM,
  PRIORITY_HIGH,

  N_PRIORITIES
};

enum poof_duration : uint8_t {
  DURATION_NONE = 0,
  DURATION_SHORT,
  DURATION_LONG
};

struct PriorityTriggers {
  struct TickData* ticks[MAX_TICKS];
};

struct TickData {
  poof_duration channels[4];
};



struct TickTriggers {
  poof_duration poofSizeA;
  poof_duration poofSizeB;
  poof_duration poofSizeC;
  poof_duration poofSizeD;
};

class Sequence {
  public:
    struct PriorityTriggers priorities[N_PRIORITIES];

    void init();

    // given the minimum ticks required to trigger a large poof, computed from the current bpm and the duration size,
    // set the priority we are capable of rendering
    void updateViablePriority(uint8_t ticksPerLongPoof, uint8_t ticksPerShortPoof);

    // Should we fire now?  Get the triggers for the given tick, clamping them within a priority range.
    TickTriggers getTickTriggers(uint8_t tickIndex, trigger_priority min, trigger_priority max);

  private:
    uint8_t minViablePriority = PRIORITY_LOW;
    trigger_priority priorityRangeMin = PRIORITY_LOW, priorityRangeMax = PRIORITY_HIGH;
    uint8_t ticksRequiredForAllLongPoofs[N_PRIORITIES];
    uint8_t ticksRequiredForAllShortPoofs[N_PRIORITIES];
    
    virtual void populateTickData() = 0;
    void populateMinimumRequirementsForTriggers();

    
};

#endif