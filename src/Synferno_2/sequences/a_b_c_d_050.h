#ifndef Sequence_a_b_c_d_050_h
#define Sequence_a_b_c_d_050_h

#include "../sequence.h"

#define SEQUENCE_TITLE_A_B_C_D_050 "A>B>C>D"

class Sequence_a_b_c_d_050 : public Sequence {
  struct TickData trigger_a;
  struct TickData trigger_b;
  struct TickData trigger_c;
  struct TickData trigger_d;
    
  public: 
    void populateTickData() {
      // init repeated tick values
      trigger_a.channels[0] = DURATION_LONG;
      trigger_b.channels[1] = DURATION_LONG;
      trigger_c.channels[2] = DURATION_LONG;
      trigger_d.channels[3] = DURATION_LONG;

      // LOW
      this->priorities[PRIORITY_LOW].ticks[0] = &trigger_a;

      this->priorities[PRIORITY_LOW].ticks[12] = &trigger_b;

      this->priorities[PRIORITY_LOW].ticks[24] = &trigger_c;

      this->priorities[PRIORITY_LOW].ticks[36] = &trigger_d;

      this->priorities[PRIORITY_LOW].ticks[48] = &trigger_a;

      this->priorities[PRIORITY_LOW].ticks[60] = &trigger_b;

      this->priorities[PRIORITY_LOW].ticks[72] = &trigger_c;

      this->priorities[PRIORITY_LOW].ticks[84] = &trigger_d;
    }
};

extern Sequence_a_b_c_d_050 sequence_a_b_c_d_050;

#endif
