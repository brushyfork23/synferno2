/*
Read in each of the 4 poofer channels from optocouplers
and send booleans to Processing.
*/

#define PIN_A 7
#define PIN_B 8
#define PIN_C 9
#define PIN_D 10

#include <Metro.h> // Include the Metro library

Metro serialMetro = Metro(1000 / 60);  // Instantiate an instance

void setup() {
  //start serial connection
  Serial.begin(9600);
  //configure pin 2 as an input and enable the internal pull-up resistor
  pinMode(PIN_A, INPUT_PULLUP);
  pinMode(PIN_B, INPUT_PULLUP);
  pinMode(PIN_C, INPUT_PULLUP);
  pinMode(PIN_D, INPUT_PULLUP);

}

void loop() {
  if (serialMetro.check()) {
    readAndPrint(PIN_A);
    readAndPrint(PIN_B);
    readAndPrint(PIN_C);
    readAndPrint(PIN_D);
    Serial.println();
  }
}

void readAndPrint(int pin) {
  int val = digitalRead(pin);
  if (val == HIGH) {
    Serial.print(0);
  } else {
    Serial.print(1);
  }
}
