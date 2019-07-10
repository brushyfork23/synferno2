#ifndef Sequence_cbda_200_h
#define Sequence_cbda_200_h

#include "../sequence.h"

#define SEQUENCE_TITLE_CBDA_200 "CBDA 2"

class Sequence_cbda_200 : public Sequence {
  struct TickData trigger_all;
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

      // MEDIUM
      uint8_t p = PRIORITY_MEDIUM;
      this->priorities[p].ticks[0] = &trigger_bc;
      this->priorities[p].ticks[48] = &trigger_ad;

      // LOW
      p = PRIORITY_LOW;
      this->priorities[p].ticks[0] = &trigger_all;
      this->priorities[p].ticks[48] = &trigger_all;
    }
};

extern Sequence_cbda_200 sequence_cbda_200;

#endif
