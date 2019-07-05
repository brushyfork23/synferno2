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
        tick0.channel[0].priority = 3;
        tick0.channel[0].duration = POOF_SIZE_LARGE;
        tick0.channel[1].priority = 2;
        tick0.channel[1].duration = POOF_SIZE_LARGE;
        tick0.channel[2].priority = 1;
        tick0.channel[2].duration = POOF_SIZE_LARGE;
        tick0.channel[3].priority = 3;
        tick0.channel[3].duration = POOF_SIZE_LARGE;
        this->tick[0] = &tick0;
        
        tick24.channel[0].priority = 3;
        tick24.channel[0].duration = POOF_SIZE_LARGE;
        tick24.channel[1].priority = 1;
        tick24.channel[1].duration = POOF_SIZE_LARGE;
        tick24.channel[2].priority = 2;
        tick24.channel[2].duration = POOF_SIZE_LARGE;
        tick24.channel[3].priority = 3;
        tick24.channel[3].duration = POOF_SIZE_LARGE;
        this->tick[24] = &tick24;
        
        tick48.channel[0].priority = 1;
        tick48.channel[0].duration = POOF_SIZE_LARGE;
        tick48.channel[1].priority = 3;
        tick48.channel[1].duration = POOF_SIZE_LARGE;
        tick48.channel[2].priority = 3;
        tick48.channel[2].duration = POOF_SIZE_LARGE;
        tick48.channel[3].priority = 2;
        tick48.channel[3].duration = POOF_SIZE_LARGE;
        this->tick[48] = &tick48;
        
        tick72.channel[0].priority = 2;
        tick72.channel[0].duration = POOF_SIZE_LARGE;
        tick72.channel[1].priority = 3;
        tick72.channel[1].duration = POOF_SIZE_LARGE;
        tick72.channel[2].priority = 3;
        tick72.channel[2].duration = POOF_SIZE_LARGE;
        tick72.channel[3].priority = 1;
        tick72.channel[3].duration = POOF_SIZE_LARGE;
        this->tick[76] = &tick72;
    }
};

extern Sequence_100 sequence100;

#endif