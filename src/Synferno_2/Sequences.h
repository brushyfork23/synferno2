#ifndef Sequences_h
#define Sequences_h

#include "Arduino.h"

#include "sequences/cbda_200.h"
#include "sequences/cbda_200_alt.h"
#include "sequences/cbda_100.h"
#include "sequences/cbda_100_alt.h"
#include "sequences/cbda_050.h"
#include "sequences/cbda_025.h"
#include "sequences/dnb.h"
#include "sequences/tripplets.h"

class Sequences {
  public:
    static void init();
};

#endif