#include "sequences.h"

Sequence_cbda_200 sequence_cbda_200;
Sequence_cbda_200_alt sequence_cbda_200_alt;
Sequence_cbda_100 sequence_cbda_100;
Sequence_cbda_100_alt sequence_cbda_100_alt;
Sequence_cbda_050 sequence_cbda_050;
Sequence_cbda_025 sequence_cbda_025;
Sequence_dnb sequence_dnb;
Sequence_tripplets sequence_tripplets;

static void Sequences::init() {
  sequence_cbda_200_alt.init();
  sequence_cbda_200.init();
  sequence_cbda_100.init();
  sequence_cbda_100_alt.init();
  sequence_cbda_050.init();
  sequence_cbda_025.init();
  sequence_dnb.init();
  sequence_tripplets.init();
}