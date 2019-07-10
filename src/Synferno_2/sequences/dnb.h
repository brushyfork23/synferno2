#ifndef Sequence_dnb_h
#define Sequence_dnb_h

#include "../sequence.h"

#define SEQUENCE_TITLE_DNB "DnB"

class Sequence_dnb : public Sequence {
  struct TickData trigger_all_large;
  struct TickData trigger_all_small;
  struct TickData trigger_ad;
  struct TickData trigger_bc_large;
  struct TickData trigger_bc_small;
  struct TickData trigger_a;
  struct TickData trigger_b;
  struct TickData trigger_c;
  struct TickData trigger_d;
    
  public: 
    void populateTickData() {
      // init repeated tick values
      trigger_ad.channels[0] = DURATION_SHORT;
      trigger_ad.channels[3] = DURATION_SHORT;

      trigger_bc_large.channels[1] = DURATION_LONG;
      trigger_bc_large.channels[2] = DURATION_LONG;

      trigger_bc_small.channels[1] = DURATION_SHORT;
      trigger_bc_small.channels[2] = DURATION_SHORT;
      
      trigger_a.channels[0] = DURATION_SHORT;
      trigger_b.channels[1] = DURATION_LONG;
      trigger_c.channels[2] = DURATION_SHORT;
      trigger_d.channels[3] = DURATION_SHORT;

      // HIGH
      uint8_t p = PRIORITY_MEDIUM;
      this->priorities[p].ticks[0] = &trigger_b;
      this->priorities[p].ticks[23] = &trigger_d;
      this->priorities[p].ticks[61] = &trigger_c;
      this->priorities[p].ticks[76] = &trigger_a;

      // MEDIUM
      p = PRIORITY_LOW;
      this->priorities[p].ticks[0] = &trigger_bc_large;
      this->priorities[p].ticks[23] = &trigger_ad;
      this->priorities[p].ticks[61] = &trigger_bc_small;
      this->priorities[p].ticks[76] = &trigger_ad;
    }
};

extern Sequence_dnb sequence_dnb;

#endif
