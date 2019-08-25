#ifndef Sequence_tripplets_h
#define Sequence_tripplets_h

#include "../sequence.h"

#define SEQUENCE_TITLE_TRIPPLETS "3x"

class Sequence_tripplets : public Sequence {
  struct TickData trigger_all;
  struct TickData trigger_b;
  struct TickData trigger_c;
  struct TickData trigger_ad;
    
  public: 
    void populateTickData() {
      // init repeated tick values
      trigger_all.channels[0] = DURATION_LONG;
      trigger_all.channels[1] = DURATION_LONG;
      trigger_all.channels[2] = DURATION_LONG;
      trigger_all.channels[3] = DURATION_LONG;

      trigger_b.channels[1] = DURATION_LONG;

      trigger_c.channels[2] = DURATION_LONG;

      trigger_ad.channels[0] = DURATION_LONG;
      trigger_ad.channels[3] = DURATION_LONG;

      // LOW
      uint8_t p = PRIORITY_LOW;
      this->priorities[p].ticks[0] = &trigger_all;
      this->priorities[p].ticks[31] = &trigger_all;
      this->priorities[p].ticks[63] = &trigger_all;

      // MEDIUM
      p = PRIORITY_MEDIUM;
      this->priorities[p].ticks[0] = &trigger_b;
      this->priorities[p].ticks[31] = &trigger_c;
      this->priorities[p].ticks[63] = &trigger_ad;
    }
};

extern Sequence_tripplets sequence_tripplets;

#endif
