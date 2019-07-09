#ifndef Sequence_cbda_050_h
#define Sequence_cbda_050_h

#include "../sequence.h"

#define SEQUENCE_TITLE_CBDA_050 "CBDA .5"

class Sequence_cbda_050 : public Sequence {
  struct TickData trigger_all;
  struct TickData trigger_ad;
  struct TickData trigger_bc;
  struct TickData trigger_a;
  struct TickData trigger_b;
  struct TickData trigger_c;
  struct TickData trigger_d;
    
  public: 
    void populateTickData() {
      // init repeated tick values
      trigger_all.channels[0] = DURATION_LARGE;
      trigger_all.channels[1] = DURATION_LARGE;
      trigger_all.channels[2] = DURATION_LARGE;
      trigger_all.channels[3] = DURATION_LARGE;

      trigger_ad.channels[0] = DURATION_LARGE;
      trigger_ad.channels[3] = DURATION_LARGE;

      trigger_bc.channels[1] = DURATION_LARGE;
      trigger_bc.channels[2] = DURATION_LARGE;
      
      trigger_a.channels[0] = DURATION_LARGE;
      trigger_b.channels[1] = DURATION_LARGE;
      trigger_c.channels[2] = DURATION_LARGE;
      trigger_d.channels[3] = DURATION_LARGE;

      // HIGH
      uint8_t p = PRIORITY_HIGH;
      this->priorities[p].ticks[0] = &trigger_c;
      this->priorities[p].ticks[12] = &trigger_b;
      this->priorities[p].ticks[24] = &trigger_d;
      this->priorities[p].ticks[36] = &trigger_a;
      this->priorities[p].ticks[48] = &trigger_c;
      this->priorities[p].ticks[60] = &trigger_b;
      this->priorities[p].ticks[72] = &trigger_d;
      this->priorities[p].ticks[84] = &trigger_a;

      // MEDIUM
      p = PRIORITY_MEDIUM;
      this->priorities[p].ticks[0] = &trigger_bc;
      this->priorities[p].ticks[12] = &trigger_ad;
      this->priorities[p].ticks[24] = &trigger_bc;
      this->priorities[p].ticks[36] = &trigger_ad;
      this->priorities[p].ticks[48] = &trigger_bc;
      this->priorities[p].ticks[60] = &trigger_ad;
      this->priorities[p].ticks[72] = &trigger_bc;
      this->priorities[p].ticks[84] = &trigger_ad;

      // LOW
      p = PRIORITY_LOW;
      this->priorities[p].ticks[0] = &trigger_all;
      this->priorities[p].ticks[12] = &trigger_all;
      this->priorities[p].ticks[24] = &trigger_all;
      this->priorities[p].ticks[36] = &trigger_all;
      this->priorities[p].ticks[48] = &trigger_all;
      this->priorities[p].ticks[60] = &trigger_all;
      this->priorities[p].ticks[72] = &trigger_all;
      this->priorities[p].ticks[84] = &trigger_all;
    }
};

extern Sequence_cbda_050 sequence_cbda_050;

#endif
