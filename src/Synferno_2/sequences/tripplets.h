#ifndef Sequence_tripplets_h
#define Sequence_tripplets_h

#include "../sequence.h"

#define SEQUENCE_TITLE_TRIPPLETS "Tripplets"

class Sequence_tripplets : public Sequence {
  struct TickData trigger_all;
    
  public: 
    void populateTickData() {
      // init repeated tick values
      trigger_all.channels[0] = DURATION_LONG;
      trigger_all.channels[1] = DURATION_LONG;
      trigger_all.channels[2] = DURATION_LONG;
      trigger_all.channels[3] = DURATION_LONG;

      // HIGH
      uint8_t p = PRIORITY_HIGH;
      this->priorities[p].ticks[0] = &trigger_all;
      this->priorities[p].ticks[31] = &trigger_all;
      this->priorities[p].ticks[63] = &trigger_all;
    }
};

extern Sequence_tripplets sequence_tripplets;

#endif
