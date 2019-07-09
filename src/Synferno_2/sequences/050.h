#ifndef Sequence_050_h
#define Sequence_050_h

#include "../sequence.h"

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
    void populateTickData() {
        strcpy(this->title, "050");

        tick0.channel[0].priority = PRIORITY_LOW;
        tick0.channel[0].duration = DURATION_LARGE;
        tick0.channel[1].priority = PRIORITY_MEDIUM;
        tick0.channel[1].duration = DURATION_LARGE;
        tick0.channel[2].priority = PRIORITY_HIGH;
        tick0.channel[2].duration = DURATION_LARGE;
        tick0.channel[3].priority = PRIORITY_LOW;
        tick0.channel[3].duration = DURATION_LARGE;
        this->ticks[0] = &tick0;
        
        tick12.channel[0].priority = PRIORITY_MEDIUM;
        tick12.channel[0].duration = DURATION_LARGE;
        tick12.channel[1].priority = PRIORITY_LOW;
        tick12.channel[1].duration = DURATION_LARGE;
        tick12.channel[2].priority = PRIORITY_LOW;
        tick12.channel[2].duration = DURATION_LARGE;
        tick12.channel[3].priority = PRIORITY_HIGH;
        tick12.channel[3].duration = DURATION_LARGE;
        this->ticks[12] = &tick12;
        
        tick24.channel[0].priority = PRIORITY_LOW;
        tick24.channel[0].duration = DURATION_LARGE;
        tick24.channel[1].priority = PRIORITY_HIGH;
        tick24.channel[1].duration = DURATION_LARGE;
        tick24.channel[2].priority = PRIORITY_MEDIUM;
        tick24.channel[2].duration = DURATION_LARGE;
        tick24.channel[3].priority = PRIORITY_LOW;
        tick24.channel[3].duration = DURATION_LARGE;
        this->ticks[24] = &tick24;
        
        tick36.channel[0].priority = PRIORITY_HIGH;
        tick36.channel[0].duration = DURATION_LARGE;
        tick36.channel[1].priority = PRIORITY_LOW;
        tick36.channel[1].duration = DURATION_LARGE;
        tick36.channel[2].priority = PRIORITY_LOW;
        tick36.channel[2].duration = DURATION_LARGE;
        tick36.channel[3].priority = PRIORITY_MEDIUM;
        tick36.channel[3].duration = DURATION_LARGE;
        this->ticks[36] = &tick36;

        tick48.channel[0].priority = PRIORITY_LOW;
        tick48.channel[0].duration = DURATION_LARGE;
        tick48.channel[1].priority = PRIORITY_MEDIUM;
        tick48.channel[1].duration = DURATION_LARGE;
        tick48.channel[2].priority = PRIORITY_HIGH;
        tick48.channel[2].duration = DURATION_LARGE;
        tick48.channel[3].priority = PRIORITY_LOW;
        tick48.channel[3].duration = DURATION_LARGE;
        this->ticks[48] = &tick48;
        
        tick60.channel[0].priority = PRIORITY_MEDIUM;
        tick60.channel[0].duration = DURATION_LARGE;
        tick60.channel[1].priority = PRIORITY_LOW;
        tick60.channel[1].duration = DURATION_LARGE;
        tick60.channel[2].priority = PRIORITY_LOW;
        tick60.channel[2].duration = DURATION_LARGE;
        tick60.channel[3].priority = PRIORITY_HIGH;
        tick60.channel[3].duration = DURATION_LARGE;
        this->ticks[60] = &tick60;
        
        tick72.channel[0].priority = PRIORITY_LOW;
        tick72.channel[0].duration = DURATION_LARGE;
        tick72.channel[1].priority = PRIORITY_HIGH;
        tick72.channel[1].duration = DURATION_LARGE;
        tick72.channel[2].priority = PRIORITY_MEDIUM;
        tick72.channel[2].duration = DURATION_LARGE;
        tick72.channel[3].priority = PRIORITY_LOW;
        tick72.channel[3].duration = DURATION_LARGE;
        this->ticks[72] = &tick72;
        
        tick84.channel[0].priority = PRIORITY_HIGH;
        tick84.channel[0].duration = DURATION_LARGE;
        tick84.channel[1].priority = PRIORITY_LOW;
        tick84.channel[1].duration = DURATION_LARGE;
        tick84.channel[2].priority = PRIORITY_LOW;
        tick84.channel[2].duration = DURATION_LARGE;
        tick84.channel[3].priority = PRIORITY_MEDIUM;
        tick84.channel[3].duration = DURATION_LARGE;
        this->ticks[84] = &tick84;
    }
};

extern Sequence_050 sequence050;

#endif
