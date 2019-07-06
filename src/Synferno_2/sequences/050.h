#ifndef Sequence_050_h
#define Sequence_050_h

#include "sequence.h"

class Sequence_050 : public Sequence {
  struct TickData tick0;
  struct TickData tick12;
  struct TickData tick24;
  struct TickData tick36;
  struct TickData tick48;
  struct TickData tick60;
  struct TickData tick72;
  struct TickData tick84;
    
  public: 
    void populate() {
        strcpy(this->title, "050");

        tick0.channel[0].priority = 3;
        tick0.channel[0].duration = DURATION_LARGE;
        tick0.channel[1].priority = 2;
        tick0.channel[1].duration = DURATION_LARGE;
        tick0.channel[2].priority = 1;
        tick0.channel[2].duration = DURATION_LARGE;
        tick0.channel[3].priority = 3;
        tick0.channel[3].duration = DURATION_LARGE;
        this->tick[0] = &tick0;
        
        tick12.channel[0].priority = 3;
        tick12.channel[0].duration = DURATION_LARGE;
        tick12.channel[1].priority = 1;
        tick12.channel[1].duration = DURATION_LARGE;
        tick12.channel[2].priority = 2;
        tick12.channel[2].duration = DURATION_LARGE;
        tick12.channel[3].priority = 3;
        tick12.channel[3].duration = DURATION_LARGE;
        this->tick[12] = &tick12;
        
        tick24.channel[0].priority = 1;
        tick24.channel[0].duration = DURATION_LARGE;
        tick24.channel[1].priority = 3;
        tick24.channel[1].duration = DURATION_LARGE;
        tick24.channel[2].priority = 3;
        tick24.channel[2].duration = DURATION_LARGE;
        tick24.channel[3].priority = 2;
        tick24.channel[3].duration = DURATION_LARGE;
        this->tick[24] = &tick24;
        
        tick36.channel[0].priority = 2;
        tick36.channel[0].duration = DURATION_LARGE;
        tick36.channel[1].priority = 3;
        tick36.channel[1].duration = DURATION_LARGE;
        tick36.channel[2].priority = 3;
        tick36.channel[2].duration = DURATION_LARGE;
        tick36.channel[3].priority = 1;
        tick36.channel[3].duration = DURATION_LARGE;
        this->tick[36] = &tick36;

        tick48.channel[0].priority = 3;
        tick48.channel[0].duration = DURATION_LARGE;
        tick48.channel[1].priority = 2;
        tick48.channel[1].duration = DURATION_LARGE;
        tick48.channel[2].priority = 1;
        tick48.channel[2].duration = DURATION_LARGE;
        tick48.channel[3].priority = 3;
        tick48.channel[3].duration = DURATION_LARGE;
        this->tick[48] = &tick48;
        
        tick60.channel[0].priority = 3;
        tick60.channel[0].duration = DURATION_LARGE;
        tick60.channel[1].priority = 1;
        tick60.channel[1].duration = DURATION_LARGE;
        tick60.channel[2].priority = 2;
        tick60.channel[2].duration = DURATION_LARGE;
        tick60.channel[3].priority = 3;
        tick60.channel[3].duration = DURATION_LARGE;
        this->tick[60] = &tick60;
        
        tick72.channel[0].priority = 1;
        tick72.channel[0].duration = DURATION_LARGE;
        tick72.channel[1].priority = 3;
        tick72.channel[1].duration = DURATION_LARGE;
        tick72.channel[2].priority = 3;
        tick72.channel[2].duration = DURATION_LARGE;
        tick72.channel[3].priority = 2;
        tick72.channel[3].duration = DURATION_LARGE;
        this->tick[72] = &tick72;
        
        tick84.channel[0].priority = 2;
        tick84.channel[0].duration = DURATION_LARGE;
        tick84.channel[1].priority = 3;
        tick84.channel[1].duration = DURATION_LARGE;
        tick84.channel[2].priority = 3;
        tick84.channel[2].duration = DURATION_LARGE;
        tick84.channel[3].priority = 1;
        tick84.channel[3].duration = DURATION_LARGE;
        this->tick[84] = &tick84;
    }
};

extern Sequence_050 sequence050;

#endif
