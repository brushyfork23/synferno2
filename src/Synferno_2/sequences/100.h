#ifndef Sequence_100_h
#define Sequence_100_h

#include "sequence.h"

class Sequence_100 : public Sequence {
  struct TickData tick0;
  struct TickData tick24;
  struct TickData tick48;
  struct TickData tick72;
    
  public: 
    void populate() {
        strcpy(this->title, "100");

        tick0.channel[0].priority = PRIORITY_LOW;
        tick0.channel[0].duration = DURATION_LARGE;
        tick0.channel[1].priority = PRIORITY_HIGH;
        tick0.channel[1].duration = DURATION_LARGE;
        tick0.channel[2].priority = PRIORITY_HIGHEST;
        tick0.channel[2].duration = DURATION_LARGE;
        tick0.channel[3].priority = PRIORITY_LOW;
        tick0.channel[3].duration = DURATION_LARGE;
        this->tick[0] = &tick0;
        
        tick24.channel[0].priority = PRIORITY_LOW;
        tick24.channel[0].duration = DURATION_LARGE;
        tick24.channel[1].priority = PRIORITY_HIGHEST;
        tick24.channel[1].duration = DURATION_LARGE;
        tick24.channel[2].priority = PRIORITY_HIGH;
        tick24.channel[2].duration = DURATION_LARGE;
        tick24.channel[3].priority = PRIORITY_LOW;
        tick24.channel[3].duration = DURATION_LARGE;
        this->tick[24] = &tick24;
        
        tick48.channel[0].priority = PRIORITY_HIGHEST;
        tick48.channel[0].duration = DURATION_LARGE;
        tick48.channel[1].priority = PRIORITY_LOW;
        tick48.channel[1].duration = DURATION_LARGE;
        tick48.channel[2].priority = PRIORITY_LOW;
        tick48.channel[2].duration = DURATION_LARGE;
        tick48.channel[3].priority = PRIORITY_HIGH;
        tick48.channel[3].duration = DURATION_LARGE;
        this->tick[48] = &tick48;
        
        tick72.channel[0].priority = PRIORITY_HIGH;
        tick72.channel[0].duration = DURATION_LARGE;
        tick72.channel[1].priority = PRIORITY_LOW;
        tick72.channel[1].duration = DURATION_LARGE;
        tick72.channel[2].priority = PRIORITY_LOW;
        tick72.channel[2].duration = DURATION_LARGE;
        tick72.channel[3].priority = PRIORITY_HIGHEST;
        tick72.channel[3].duration = DURATION_LARGE;
        this->tick[72] = &tick72;
    }
};

extern Sequence_100 sequence100;

#endif