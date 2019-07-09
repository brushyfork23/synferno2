#include "sequences.h"

Sequence_400 sequence400;
Sequence_200 sequence200;
Sequence_100 sequence100;
Sequence_050 sequence050;
Sequence_025 sequence025;

static void Sequences::init() {
  sequence400.init();
  sequence200.init();
  sequence100.init();
  sequence050.init();
  sequence025.init();
}