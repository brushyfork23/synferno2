#ifndef Sequence_025_h
#define Sequence_025_h

#include "../sequence.h"

class Sequence_025 : public Sequence {
  struct TickData tick0;
  struct TickData tick6;
  struct TickData tick12;
  struct TickData tick18;
  struct TickData tick24;
  struct TickData tick30;
  struct TickData tick36;
  struct TickData tick42;
  struct TickData tick48;
  struct TickData tick54;
  struct TickData tick60;
  struct TickData tick66;
  struct TickData tick72;
  struct TickData tick78;
  struct TickData tick84;
  struct TickData tick90;
    
  public: 
    void populateTickData() {
        strcpy(this->title, "025");

        tick0.channel[0].priority = PRIORITY_LOW;
        tick0.channel[0].duration = DURATION_LARGE;
        tick0.channel[1].priority = PRIORITY_MEDIUM;
        tick0.channel[1].duration = DURATION_LARGE;
        tick0.channel[2].priority = PRIORITY_HIGH;
        tick0.channel[2].duration = DURATION_LARGE;
        tick0.channel[3].priority = PRIORITY_LOW;
        tick0.channel[3].duration = DURATION_LARGE;
        this->ticks[0] = &tick0;
        
        tick6.channel[0].priority = PRIORITY_MEDIUM;
        tick6.channel[0].duration = DURATION_LARGE;
        tick6.channel[1].priority = PRIORITY_LOW;
        tick6.channel[1].duration = DURATION_LARGE;
        tick6.channel[2].priority = PRIORITY_LOW;
        tick6.channel[2].duration = DURATION_LARGE;
        tick6.channel[3].priority = PRIORITY_HIGH;
        tick6.channel[3].duration = DURATION_LARGE;
        this->ticks[6] = &tick6;
        
        tick12.channel[0].priority = PRIORITY_LOW;
        tick12.channel[0].duration = DURATION_LARGE;
        tick12.channel[1].priority = PRIORITY_HIGH;
        tick12.channel[1].duration = DURATION_LARGE;
        tick12.channel[2].priority = PRIORITY_MEDIUM;
        tick12.channel[2].duration = DURATION_LARGE;
        tick12.channel[3].priority = PRIORITY_LOW;
        tick12.channel[3].duration = DURATION_LARGE;
        this->ticks[12] = &tick12;
        
        tick18.channel[0].priority = PRIORITY_HIGH;
        tick18.channel[0].duration = DURATION_LARGE;
        tick18.channel[1].priority = PRIORITY_LOW;
        tick18.channel[1].duration = DURATION_LARGE;
        tick18.channel[2].priority = PRIORITY_LOW;
        tick18.channel[2].duration = DURATION_LARGE;
        tick18.channel[3].priority = PRIORITY_MEDIUM;
        tick18.channel[3].duration = DURATION_LARGE;
        this->ticks[18] = &tick18;

        tick24.channel[0].priority = PRIORITY_LOW;
        tick24.channel[0].duration = DURATION_LARGE;
        tick24.channel[1].priority = PRIORITY_MEDIUM;
        tick24.channel[1].duration = DURATION_LARGE;
        tick24.channel[2].priority = PRIORITY_HIGH;
        tick24.channel[2].duration = DURATION_LARGE;
        tick24.channel[3].priority = PRIORITY_LOW;
        tick24.channel[3].duration = DURATION_LARGE;
        this->ticks[24] = &tick24;
        
        tick30.channel[0].priority = PRIORITY_MEDIUM;
        tick30.channel[0].duration = DURATION_LARGE;
        tick30.channel[1].priority = PRIORITY_LOW;
        tick30.channel[1].duration = DURATION_LARGE;
        tick30.channel[2].priority = PRIORITY_LOW;
        tick30.channel[2].duration = DURATION_LARGE;
        tick30.channel[3].priority = PRIORITY_HIGH;
        tick30.channel[3].duration = DURATION_LARGE;
        this->ticks[30] = &tick30;
        
        tick36.channel[0].priority = PRIORITY_LOW;
        tick36.channel[0].duration = DURATION_LARGE;
        tick36.channel[1].priority = PRIORITY_HIGH;
        tick36.channel[1].duration = DURATION_LARGE;
        tick36.channel[2].priority = PRIORITY_MEDIUM;
        tick36.channel[2].duration = DURATION_LARGE;
        tick36.channel[3].priority = PRIORITY_LOW;
        tick36.channel[3].duration = DURATION_LARGE;
        this->ticks[36] = &tick36;
        
        tick42.channel[0].priority = PRIORITY_HIGH;
        tick42.channel[0].duration = DURATION_LARGE;
        tick42.channel[1].priority = PRIORITY_LOW;
        tick42.channel[1].duration = DURATION_LARGE;
        tick42.channel[2].priority = PRIORITY_LOW;
        tick42.channel[2].duration = DURATION_LARGE;
        tick42.channel[3].priority = PRIORITY_MEDIUM;
        tick42.channel[3].duration = DURATION_LARGE;
        this->ticks[42] = &tick42;

        tick48.channel[0].priority = PRIORITY_LOW;
        tick48.channel[0].duration = DURATION_LARGE;
        tick48.channel[1].priority = PRIORITY_MEDIUM;
        tick48.channel[1].duration = DURATION_LARGE;
        tick48.channel[2].priority = PRIORITY_HIGH;
        tick48.channel[2].duration = DURATION_LARGE;
        tick48.channel[3].priority = PRIORITY_LOW;
        tick48.channel[3].duration = DURATION_LARGE;
        this->ticks[48] = &tick48;
        
        tick54.channel[0].priority = PRIORITY_MEDIUM;
        tick54.channel[0].duration = DURATION_LARGE;
        tick54.channel[1].priority = PRIORITY_LOW;
        tick54.channel[1].duration = DURATION_LARGE;
        tick54.channel[2].priority = PRIORITY_LOW;
        tick54.channel[2].duration = DURATION_LARGE;
        tick54.channel[3].priority = PRIORITY_HIGH;
        tick54.channel[3].duration = DURATION_LARGE;
        this->ticks[54] = &tick54;
        
        tick60.channel[0].priority = PRIORITY_LOW;
        tick60.channel[0].duration = DURATION_LARGE;
        tick60.channel[1].priority = PRIORITY_HIGH;
        tick60.channel[1].duration = DURATION_LARGE;
        tick60.channel[2].priority = PRIORITY_MEDIUM;
        tick60.channel[2].duration = DURATION_LARGE;
        tick60.channel[3].priority = PRIORITY_LOW;
        tick60.channel[3].duration = DURATION_LARGE;
        this->ticks[60] = &tick60;
        
        tick66.channel[0].priority = PRIORITY_HIGH;
        tick66.channel[0].duration = DURATION_LARGE;
        tick66.channel[1].priority = PRIORITY_LOW;
        tick66.channel[1].duration = DURATION_LARGE;
        tick66.channel[2].priority = PRIORITY_LOW;
        tick66.channel[2].duration = DURATION_LARGE;
        tick66.channel[3].priority = PRIORITY_MEDIUM;
        tick66.channel[3].duration = DURATION_LARGE;
        this->ticks[66] = &tick66;

        tick72.channel[0].priority = PRIORITY_LOW;
        tick72.channel[0].duration = DURATION_LARGE;
        tick72.channel[1].priority = PRIORITY_MEDIUM;
        tick72.channel[1].duration = DURATION_LARGE;
        tick72.channel[2].priority = PRIORITY_HIGH;
        tick72.channel[2].duration = DURATION_LARGE;
        tick72.channel[3].priority = PRIORITY_LOW;
        tick72.channel[3].duration = DURATION_LARGE;
        this->ticks[72] = &tick72;
        
        tick78.channel[0].priority = PRIORITY_MEDIUM;
        tick78.channel[0].duration = DURATION_LARGE;
        tick78.channel[1].priority = PRIORITY_LOW;
        tick78.channel[1].duration = DURATION_LARGE;
        tick78.channel[2].priority = PRIORITY_LOW;
        tick78.channel[2].duration = DURATION_LARGE;
        tick78.channel[3].priority = PRIORITY_HIGH;
        tick78.channel[3].duration = DURATION_LARGE;
        this->ticks[78] = &tick78;
        
        tick84.channel[0].priority = PRIORITY_LOW;
        tick84.channel[0].duration = DURATION_LARGE;
        tick84.channel[1].priority = PRIORITY_HIGH;
        tick84.channel[1].duration = DURATION_LARGE;
        tick84.channel[2].priority = PRIORITY_MEDIUM;
        tick84.channel[2].duration = DURATION_LARGE;
        tick84.channel[3].priority = PRIORITY_LOW;
        tick84.channel[3].duration = DURATION_LARGE;
        this->ticks[84] = &tick84;
        
        tick90.channel[0].priority = PRIORITY_HIGH;
        tick90.channel[0].duration = DURATION_LARGE;
        tick90.channel[1].priority = PRIORITY_LOW;
        tick90.channel[1].duration = DURATION_LARGE;
        tick90.channel[2].priority = PRIORITY_LOW;
        tick90.channel[2].duration = DURATION_LARGE;
        tick90.channel[3].priority = PRIORITY_MEDIUM;
        tick90.channel[3].duration = DURATION_LARGE;
        this->ticks[90] = &tick90;
    }
};

extern Sequence_025 sequence025;

#endif
