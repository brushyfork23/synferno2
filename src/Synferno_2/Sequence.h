#ifndef Sequence_h
#define Sequence_h

#define POOF_SIZE_LARGE 2

struct ChannelData {
  uint8_t priority;
  uint8_t duration;
};

struct TickData {
  struct ChannelData channel[4];
};

class Sequence {
  public:
    char title[10];
    struct TickData* tick[96];

    virtual void populate() = 0;
};

#endif