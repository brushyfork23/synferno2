#include "sequences.h"

Sequence_cbda_400 sequence_cbda_400;
Sequence_cbda_200 sequence_cbda_200;
Sequence_cbda_100 sequence_cbda_100;
Sequence_cbda_050 sequence_cbda_050;
Sequence_cbda_025 sequence_cbda_025;
Sequence_a_b_c_d_050 sequence_a_b_c_d_050;
Sequence_d_c_b_a_050 sequence_d_c_b_a_050;
Sequence_dnb sequence_dnb;
Sequence_tripplets sequence_tripplets;

static void Sequences::init() {
  sequence_cbda_400.init();
  sequence_cbda_200.init();
  sequence_cbda_100.init();
  sequence_cbda_050.init();
  sequence_cbda_025.init();
  sequence_a_b_c_d_050.init();
  sequence_d_c_b_a_050.init();
  sequence_dnb.init();
  sequence_tripplets.init();
}