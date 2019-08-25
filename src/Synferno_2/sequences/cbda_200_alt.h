#ifndef Sequence_cbda_200_alt_h
#define Sequence_cbda_200_alt_h

#include "../sequence.h"

#define SEQUENCE_TITLE_CBDA_200_ALT "2x alt"

class Sequence_cbda_200_alt : public Sequence {
  struct TickData trigger_ad;
  struct TickData trigger_bc;
    
  public: 
    void populateTickData() {
      // init repeated tick values
      trigger_ad.channels[0] = DURATION_LONG;
      trigger_ad.channels[3] = DURATION_LONG;

      trigger_bc.channels[1] = DURATION_LONG;
      trigger_bc.channels[2] = DURATION_LONG;

      // LOW
      uint8_t p = PRIORITY_LOW;
      this->priorities[p].ticks[0] = &trigger_ad;
      this->priorities[p].ticks[48] = &trigger_bc;
    }
};

extern Sequence_cbda_200_alt sequence_cbda_200_alt;

#endif
