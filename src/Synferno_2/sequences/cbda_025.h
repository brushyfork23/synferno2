#ifndef Sequence_cbda_025_h
#define Sequence_cbda_025_h

#include "../sequence.h"

#define SEQUENCE_TITLE_CBDA_025 ".25x"

class Sequence_cbda_025 : public Sequence {
  struct TickData trigger_all;
  struct TickData trigger_a;
  struct TickData trigger_b;
  struct TickData trigger_c;
  struct TickData trigger_d;
  struct TickData trigger_ad;
  struct TickData trigger_bc;
    
  public: 
    void populateTickData() {
      // init repeated tick values
      trigger_all.channels[0] = DURATION_LONG;
      trigger_all.channels[1] = DURATION_LONG;
      trigger_all.channels[2] = DURATION_LONG;
      trigger_all.channels[3] = DURATION_LONG;

      trigger_ad.channels[0] = DURATION_LONG;
      trigger_ad.channels[3] = DURATION_LONG;

      trigger_bc.channels[1] = DURATION_LONG;
      trigger_bc.channels[2] = DURATION_LONG;
      
      trigger_a.channels[0] = DURATION_LONG;
      trigger_b.channels[1] = DURATION_LONG;
      trigger_c.channels[2] = DURATION_LONG;
      trigger_d.channels[3] = DURATION_LONG;


      // HIGH
      uint8_t p = PRIORITY_HIGH;
      this->priorities[p].ticks[0] = &trigger_c;
      this->priorities[p].ticks[6] = &trigger_b;
      this->priorities[p].ticks[12] = &trigger_d;
      this->priorities[p].ticks[18] = &trigger_a;
      this->priorities[p].ticks[24] = &trigger_c;
      this->priorities[p].ticks[30] = &trigger_b;
      this->priorities[p].ticks[36] = &trigger_d;
      this->priorities[p].ticks[42] = &trigger_a;
      this->priorities[p].ticks[48] = &trigger_c;
      this->priorities[p].ticks[54] = &trigger_b;
      this->priorities[p].ticks[60] = &trigger_d;
      this->priorities[p].ticks[66] = &trigger_a;
      this->priorities[p].ticks[72] = &trigger_c;
      this->priorities[p].ticks[78] = &trigger_b;
      this->priorities[p].ticks[84] = &trigger_d;
      this->priorities[p].ticks[90] = &trigger_a;

      // MEDIUM
      p = PRIORITY_MEDIUM;
      this->priorities[p].ticks[0] = &trigger_ad;
      this->priorities[p].ticks[6] = &trigger_bc;
      this->priorities[p].ticks[12] = &trigger_ad;
      this->priorities[p].ticks[18] = &trigger_bc;
      this->priorities[p].ticks[24] = &trigger_ad;
      this->priorities[p].ticks[30] = &trigger_bc;
      this->priorities[p].ticks[36] = &trigger_bc;
      this->priorities[p].ticks[42] = &trigger_ad;
      this->priorities[p].ticks[48] = &trigger_bc;
      this->priorities[p].ticks[54] = &trigger_ad;
      this->priorities[p].ticks[60] = &trigger_bc;
      this->priorities[p].ticks[66] = &trigger_ad;
      this->priorities[p].ticks[72] = &trigger_bc;
      this->priorities[p].ticks[78] = &trigger_ad;
      this->priorities[p].ticks[84] = &trigger_bc;
      this->priorities[p].ticks[90] = &trigger_ad;

      // LOW
      p = PRIORITY_LOW;
      this->priorities[p].ticks[0] = &trigger_all;
      this->priorities[p].ticks[6] = &trigger_all;
      this->priorities[p].ticks[12] = &trigger_all;
      this->priorities[p].ticks[18] = &trigger_all;
      this->priorities[p].ticks[24] = &trigger_all;
      this->priorities[p].ticks[30] = &trigger_all;
      this->priorities[p].ticks[36] = &trigger_all;
      this->priorities[p].ticks[42] = &trigger_all;
      this->priorities[p].ticks[48] = &trigger_all;
      this->priorities[p].ticks[54] = &trigger_all;
      this->priorities[p].ticks[60] = &trigger_all;
      this->priorities[p].ticks[66] = &trigger_all;
      this->priorities[p].ticks[72] = &trigger_all;
      this->priorities[p].ticks[78] = &trigger_all;
      this->priorities[p].ticks[84] = &trigger_all;
      this->priorities[p].ticks[90] = &trigger_all;
    }
};

extern Sequence_cbda_025 sequence_cbda_025;

#endif
