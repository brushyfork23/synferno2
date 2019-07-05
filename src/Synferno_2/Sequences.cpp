#include "sequences.h"

Sequence_100 sequence100;
Sequence_050 sequence050;

static void Sequences::init() {  
  sequence100.populate();
  sequence050.populate();
}