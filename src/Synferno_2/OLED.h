#ifndef OLED_h
#define OLED_h

#include <Wire.h>
#include "SSD1306.h"

class OLED{
  public:
    void begin();

    String buffer;
    void write(byte row, byte col=0, boolean pad=false);

  private:
  
};

#endif
