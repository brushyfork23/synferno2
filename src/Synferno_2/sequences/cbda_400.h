#ifndef Sequence_cbda_400_h
#define Sequence_cbda_400_h

#include "../sequence.h"

#define SEQUENCE_TITLE_CBDA_400 "CBDA 4"

class Sequence_cbda_400 : public Sequence {
  struct TickData trigger_all;
    
  public: 
    void populateTickData() {
      // init repeated tick values
      trigger_all.channels[0] = DURATION_LARGE;
      trigger_all.channels[1] = DURATION_LARGE;
      trigger_all.channels[2] = DURATION_LARGE;
      trigger_all.channels[3] = DURATION_LARGE;

      // LOW
      this->priorities[PRIORITY_LOW].ticks[0] = &trigger_all;
    }
};

extern Sequence_cbda_400 sequence_cbda_400;

#endif
