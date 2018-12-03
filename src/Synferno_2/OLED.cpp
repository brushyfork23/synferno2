#include "OLED.h"

// 21 == SDA
// 22 == SCL
SSD1306  display(0x3D, 21, 22);

void OLED::begin() {
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_8);

  this->buffer.reserve(16);
  this->buffer = "*              *";
  
  this->write(0);
  this->write(7);
}

void OLED::write(byte row, byte col, boolean pad) {
  // right pad
  if( pad ) {
    while( this->buffer.length() < (16-col) ) this->buffer += " ";
  }
  
  display.drawString(col, row * 8, this->buffer);
  display.display();
}


