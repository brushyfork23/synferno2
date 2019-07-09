#ifndef Sequence_400_h
#define Sequence_400_h

#include "../sequence.h"

class Sequence_400 : public Sequence {
  struct TickData tick0;
    
  public: 
    void populateTickData() {
        strcpy(this->title, "400");

        tick0.channel[0].priority = PRIORITY_HIGH;
        tick0.channel[0].duration = DURATION_LARGE;
        tick0.channel[1].priority = PRIORITY_HIGH;
        tick0.channel[1].duration = DURATION_LARGE;
        tick0.channel[2].priority = PRIORITY_HIGH;
        tick0.channel[2].duration = DURATION_LARGE;
        tick0.channel[3].priority = PRIORITY_HIGH;
        tick0.channel[3].duration = DURATION_LARGE;
        this->ticks[0] = &tick0;
    }
};

extern Sequence_400 sequence400;

#endif