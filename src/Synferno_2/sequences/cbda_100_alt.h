#ifndef Sequence_cbda_100_alt_h
#define Sequence_cbda_100_alt_h

#include "../sequence.h"

#define SEQUENCE_TITLE_CBDA_100_ALT "1x alt"

class Sequence_cbda_100_alt : public Sequence {
  struct TickData trigger_ad;
  struct TickData trigger_bc;
  struct TickData trigger_a;
  struct TickData trigger_b;
  struct TickData trigger_c;
  struct TickData trigger_d;
    
  public: 
    void populateTickData() {
      // init repeated tick values
      trigger_ad.channels[0] = DURATION_LONG;
      trigger_ad.channels[3] = DURATION_LONG;

      trigger_bc.channels[1] = DURATION_LONG;
      trigger_bc.channels[2] = DURATION_LONG;
      
      trigger_a.channels[0] = DURATION_LONG;
      trigger_b.channels[1] = DURATION_LONG;
      trigger_c.channels[2] = DURATION_LONG;
      trigger_d.channels[3] = DURATION_LONG;

      // HIGH
      uint8_t p = PRIORITY_MEDIUM;
      this->priorities[p].ticks[0] = &trigger_c;
      this->priorities[p].ticks[24] = &trigger_b;
      this->priorities[p].ticks[48] = &trigger_d;
      this->priorities[p].ticks[72] = &trigger_a;

      // MEDIUM
      p = PRIORITY_LOW;
      this->priorities[p].ticks[0] = &trigger_bc;
      this->priorities[p].ticks[24] = &trigger_ad;
      this->priorities[p].ticks[48] = &trigger_bc;
      this->priorities[p].ticks[72] = &trigger_ad;
    }
};

extern Sequence_cbda_100_alt sequence_cbda_100_alt;

#endif
