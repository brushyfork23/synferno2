#ifndef Sequence_200_h
#define Sequence_200_h

#include "../sequence.h"

class Sequence_200 : public Sequence {
  struct TickData tick0;
  struct TickData tick48;
    
  public: 
    void populateTickData() {
        strcpy(this->title, "200");

        tick0.channel[0].priority = PRIORITY_LOW;
        tick0.channel[0].duration = DURATION_LARGE;
        tick0.channel[1].priority = PRIORITY_MEDIUM;
        tick0.channel[1].duration = DURATION_LARGE;
        tick0.channel[2].priority = PRIORITY_MEDIUM;
        tick0.channel[2].duration = DURATION_LARGE;
        tick0.channel[3].priority = PRIORITY_LOW;
        tick0.channel[3].duration = DURATION_LARGE;
        this->ticks[0] = &tick0;
        
        tick48.channel[0].priority = PRIORITY_MEDIUM;
        tick48.channel[0].duration = DURATION_LARGE;
        tick48.channel[1].priority = PRIORITY_LOW;
        tick48.channel[1].duration = DURATION_LARGE;
        tick48.channel[2].priority = PRIORITY_LOW;
        tick48.channel[2].duration = DURATION_LARGE;
        tick48.channel[3].priority = PRIORITY_MEDIUM;
        tick48.channel[3].duration = DURATION_LARGE;
        this->ticks[48] = &tick48;
    }
};

extern Sequence_200 sequence200;

#endif