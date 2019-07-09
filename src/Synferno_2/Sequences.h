#ifndef Sequences_h
#define Sequences_h

#include "Arduino.h"

#include "sequences/cbda_400.h"
#include "sequences/cbda_200.h"
#include "sequences/cbda_100.h"
#include "sequences/cbda_050.h"
#include "sequences/cbda_025.h"
#include "sequences/a_b_c_d_100.h"
#include "sequences/d_c_b_a_100.h"
#include "sequences/dnb.h"

class Sequences {
  public:
    static void init();
};

#endif