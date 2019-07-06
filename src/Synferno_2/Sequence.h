#ifndef Sequence_h
#define Sequence_h

#define MAX_TICKS 96 // 24 ticks per beat, 4 beats per stanza

#define POOF_SIZE_LARGE 2

#define PRIORITY_NO 0
#define PRIORITY_LOW 1
#define PRIORITY_MEDIUM 2
#define PRIORITY_HIGH 3
#define PRIORITY_HIGHEST 4
#define N_PRIORITIES 5

struct SequenceFireDictations {
  boolean shouldFireA;
  boolean shouldFireB;
  boolean shouldFireC;
  boolean shouldFireD;
}

struct ChannelData {
  uint8_t priority;
  uint8_t duration;
};

struct TickData {
  struct ChannelData channel[4];
};

class Sequence {
  public:
    char title[10];
    struct TickData* tick[MAX_TICKS];

    void init() {
      // initialize tick data
      this->populate();
      
      // calculate the minimum ticks between each trigger required
      // to hit all triggers of priority higher-than-or-equal-to each priority level
      for (int p=PRIORITY_LOW; p<=PRIORITY_HIGHEST; p++) {
        int minTicks = 0;
        for (int c=0; c<4; c++) {
          int8_t lastTick = -1;
          int8_t firstTick = -1; // use this to check the difference between the last tick and the first tick
          for (int i=0; i<MAX_TICKS; i++) {
            // find the lowest tick difference 
            if (this->tick[i] && this->tick[i]->channel[c].priority >= p) { // this tick has a trigger with the right priority
              if (firstTick < 0) {
                firstTick = i;
              } else {
                uint8_t ticksSinceLast = i - lastTick;
                if (minTicksForPriority[p] > ticksSinceLast) {
                  minTicksForPriority[p] = ticksSinceLast;
                }
              }
              lastTick = i;
            }
          }
          // now that we've iterated over all ticks in this channel, additionally check the difference
          // between the final tick and the first tick
          uint8_t ticksFromLastToFirst = MAX_TICKS - 1 - lastTick + firstTick;
          if (minTicksForPriority[p] > ticksFromLastToFirst) {
            minTicksForPriority[p] = ticksFromLastToFirst;
          }
        }
      }
    }

    // return the maximum priority 
    uint8_t getPriority(uint8_t minTicksPerTrigger) {
      for 
    }

  private:
    virtual void populate() = 0;
    uint8_t minTicksForPriority[N_PRIORITIES];
};

#endif