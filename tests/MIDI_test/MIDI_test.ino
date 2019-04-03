// Compile for Arduino Mega 2560

// Use CoolTerm from http://freeware.the-meiers.org/ to record Serial data

// Arduino Mega 2560: https://smile.amazon.com/Elegoo-EL-CB-003-ATmega2560-ATMEGA16U2-Arduino/dp/B01H4ZLZLQ
// MIDI Breakout Board: https://smile.amazon.com/gp/product/B00YDLVLVO

// Midi breakout
// tx to Mega 17 (`RX1`)
// rx to Mega 16 (`TX1`)
// + to Mega `5V`
// - to GND

#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  Serial2.begin(31250);
  delay(100);
  Serial.println("Listening...");
}

void loop() {
    if (Serial2.available() > 0) {
        byte midiByte = Serial2.read();
        Serial.print(midiByte, BIN);
        Serial.print(",");
        Serial.println(midiByte, HEX);
    }
}
