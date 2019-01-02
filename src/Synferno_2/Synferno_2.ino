
// Compile for Arduino Mega 2560

// Arduino Mega 2560: https://smile.amazon.com/Elegoo-EL-CB-003-ATmega2560-ATMEGA16U2-Arduino/dp/B01H4ZLZLQ
// WEMOS LOLIN D1 mini: https://wiki.wemos.cc/products:d1:d1_mini
// Blue 2.42" SSD1309 128x64 OLED: https://www.ebay.com/itm/253714699654
// Rotary Encoder w/ Click switch: https://www.ebay.com/itm/232396602079
// MIDI Breakout Board: https://smile.amazon.com/gp/product/B00YDLVLVO
// IRF520 MOSFET Driver Module: https://smile.amazon.com/gp/product/B06XHH1TQM
// 12V / 5V DC Buck Converter: https://smile.amazon.com/gp/product/B01MEESLZ6
// 12V 10A Power Supply: https://smile.amazon.com/gp/product/B00Z9X4GLW

// Arduino Mega
// A2 to OLED `CS`
// A8 to Rotary Encoder `A`
// A9 to Rotary Encoder `B`
// 6 to Pushbutton Zero `LED`
// 7 to Pushbutton Freq 0 `LED`
// 8 to Pushbutton Freq 1 `LED`
// 9 to Pushbutton Freq 2 `LED`
// 10 to Pushbutton Freq 3 `LED`
// 11 to Pushbutton Freq 4 `LED`
// 2 to Pushbutton Fire 0 `LED`
// 3 to Pushbutton Fire 1 `LED`
// 12 to Pushbutton Fire 2 `LED`
// 4 to Pushbutton Fire 3 `LED`
// 5 to Pushbutton Fire 4 `LED`
// 13 to Pushbutton Tap `LED`
// 16 to MIDI `rx`
// 17 to MIDI `tx`
// 18 to ESP8266 `RX`
// 19 to ESP8266 `TX`
// 20 to OLED `SDA`
// 21 to OLED `SCLK`
// 22 to OLED `DC`
// 23 to OLED `RES`
// 24 to Rotary Encoder `Btn`
// 25 to MOSFET Driver Module 0 `SIG`
// 26 to MOSFET Driver Module 1 `SIG`
// 27 to MOSFET Driver Module 2 `SIG`
// 28 to MOSFET Driver Module 3 `SIG`
// 29 to Pushbutton Freq 0 `signal`
// 30 to Pushbutton Freq 1 `signal`
// 31 to Pushbutton Freq 2 `signal`
// 32 to Pushbutton Freq 3 `signal`
// 33 to Pushbutton Freq 4 `signal`
// 34 to Pushbutton Fire 0 `signal`
// 35 to Pushbutton Fire 1 `signal`
// 36 to Pushbutton Fire 2 `signal`
// 37 to Pushbutton Fire 3 `signal`
// 38 to Pushbutton Fire 4 `signal`
// 39 to Pushbutton Zero `signal`
// 40 to Pushbutton Tap `signal`
// VCC to Buck Converter `+5`
// GND to GND

// WEMOS LOLIN D1 mini (ESP8266)
// TX to Mega 19 (`RX1`)
// RX to Mega 18 (`TX1`)
// 5V to Buck Converter `+5`
// GND to GND

// SSD1309 OLED
// CS to Mega A2
// DC to Mega 22
// RES to Mega 23
// SCLK to Mega 21
// SDA to Mega 20
// VDD to Buck Converter `+5`
// VSS to GND

// Click Encoder
// A to Mega A8
// B to Mega A9
// Btn to Mega 24
// + to Buck Converter `+5`
// GND to GND

// MOSFET Driver Module (0)
// SIG to Mega 25
// VCC to Buck Converter `+5`
// GND to GND

// MOSFET Driver Module (1)
// SIG to Mega 26
// VCC to Buck Converter `+5`
// GND to GND

// MOSFET Driver Module (2)
// SIG to Mega 27
// VCC to Buck Converter `+5`
// GND to GND

// MOSFET Driver Module (3)
// SIG to Mega 28
// VCC to Buck Converter `+5`
// GND to GND

// Midi breakout
// tx to Mega 16 (`RX2`)
// rx to Mega 17 (`TX2`)
// + to Buck Converter `+5`
// - to GND

#include <Streaming.h>
#include <Metro.h>

// MIDI
#include "MIDI.h"
MIDI midi;

// ManualBeat
#include "ManualBeat.h"
ManualBeat manualBeat;

// Solenoids
#include "Solenoid.h"
Solenoid fireA, fireB, fireC, fireD;

// Push buttons
#include "Button.h"
#include "Metro.h"
#define BRIGHTNESS_BRIGHT_RED 255
#define BRIGHTNESS_DIM_RED 20
#define BRIGHTNESS_BRIGHT_BLUE 245
#define BRIGHTNESS_DIM_BLUE 15
#define BTN_FIRE_0_PIN 34
#define BTN_FIRE_1_PIN 35
#define BTN_FIRE_2_PIN 36
#define BTN_FIRE_3_PIN 37
#define BTN_FIRE_4_PIN 38
#define BTN_ZERO_PIN 39
#define BTN_TAP_PIN 40
#define LED_FIRE_0_PIN 2
#define LED_FIRE_1_PIN 3
#define LED_FIRE_2_PIN 12
#define LED_FIRE_3_PIN 4
#define LED_FIRE_4_PIN 5
#define LED_ZERO_PIN 6
#define LED_TAP_PIN 13
Button fireAllNow;
Button fireANow;
Button fireBNow;
Button fireCNow;
Button fireDNow;
Button zero;
Button tap;

// Frequency buttons
#include "ButtonGroup.h"
#define NUM_FREQUENCY_BUTTONS 5
byte FREQUENCY_BUTTON_PINS[NUM_FREQUENCY_BUTTONS] = {29, 30, 31, 32, 33};
byte FREQUENCY_LED_PINS[NUM_FREQUENCY_BUTTONS] = {7, 8, 9, 10, 11};
ButtonGroup frequency;

/*
 * Begin Menu
 */
#include <menu.h>
#include <menuIO/u8g2Out.h>
#include <menuIO/encoderIn.h>
#include <menuIO/keyIn.h>
#include <menuIO/chainStream.h>
#include <SPI.h>
using namespace Menu;
#define ENC_A    A8
#define ENC_B    A9
#define ENC_BTN  24
#define OLED_CS A2
#define OLED_DC 22
#define OLED_RST 23
#define fontName u8g2_font_7x13_mf
#define fontX 7
#define fontY 16
#define offsetX 0
#define offsetY 3
#define U8_Width 128
#define U8_Height 64
#define USE_HWI2C
U8G2_SSD1309_128X64_NONAME0_1_4W_SW_SPI u8g2(U8G2_R0, SCL, SDA, OLED_CS, OLED_DC, OLED_RST);
// define menu colors --------------------------------------------------------
//each color is in the format:
//  {{disabled normal,disabled selected},{enabled normal,enabled selected, enabled editing}}
// this is a monochromatic color table
const colorDef<uint8_t> colors[] MEMMODE={
  {{0,0},{0,1,1}},//bgColor
  {{1,1},{1,0,0}},//fgColor
  {{1,1},{1,0,0}},//valColor
  {{1,1},{1,0,0}},//unitColor
  {{0,1},{0,0,1}},//cursorColor
  {{1,1},{1,0,0}},//titleColor
};

#define MODE_MIDI 0
#define MODE_MANUAL 1
boolean hasConfigChange = false;
int offset=0;
int duration=4;
int bpm=120;
int mode=MODE_MIDI;

SELECT(mode,modeMenu,"Mode",doNothing,noEvent,noStyle
  ,VALUE("Midi",MODE_MIDI,selectMidi,updateEvent)
  ,VALUE("Manual",MODE_MANUAL,selectManual,updateEvent)
);

MENU(mainMenu,"SYNFERNO",doNothing,noEvent,noStyle
  ,FIELD(offset,"Offset","",0,24,1,0,configUpdate,updateEvent,noStyle)
  ,FIELD(duration,"Duration","",0,24,1,0,configUpdate,updateEvent,noStyle)
  ,FIELD(bpm,"BPM","",0,300,1,0,editBPM,updateEvent,noStyle)
  ,SUBMENU(modeMenu)
);

#define MAX_DEPTH 2


void selectMidi() {
  configUpdate();
  // Disable manual BPM setting
  mainMenu[2].enabled=disabledStatus;
}

void selectManual() {
  configUpdate();
  // Enable manual BPM setting
  mainMenu[2].enabled=enabledStatus;
  manualBeat.resetCounter();
}

void editBPM() {
  configUpdate();
  manualBeat.setBPM(bpm);
}

void configUpdate() {
  hasConfigChange = true;
}

encoderIn<ENC_A,ENC_B> encoder;//simple quad encoder driver
encoderInStream<ENC_A,ENC_B> encStream(encoder,4);// simple quad encoder fake Stream

//a keyboard with only one key as the encoder button
keyMap encBtn_map[]={{-ENC_BTN,defaultNavCodes[enterCmd].ch}};//negative pin numbers use internal pull-up, this is on when low
keyIn<1> encButton(encBtn_map);//1 is the number of keys

MENU_INPUTS(in,&encStream,&encButton);

MENU_OUTPUTS(out,MAX_DEPTH
  ,U8G2_OUT(u8g2,colors,fontX,fontY,offsetX,offsetY,{0,0,U8_Width/fontX,U8_Height/fontY})
  ,NONE
);
  
NAVROOT(nav,mainMenu,MAX_DEPTH,in,out);
/**
 * End MENU
 */


// Local variables
byte clocksPerTrigger = CLOCK_TICKS_PER_BEAT;
unsigned long microsBetweenTaps;

void setup() {
  Serial.begin(115200);
  while(!Serial);

  // fire up the Screen
  SPI.begin();
  u8g2.begin();
  u8g2.setFont(fontName);

  // configure Menu
  nav.showTitle=false;

  // fire up the rotary encoder
  encButton.begin();
  encoder.begin();

  // fire up MIDI
  midi.begin();

  // fire up the fire
  fireA.begin(SOLENOID_PIN0);
  fireB.begin(SOLENOID_PIN1);
  fireC.begin(SOLENOID_PIN2);
  fireD.begin(SOLENOID_PIN3);

  // buttons
  // make fire now
  fireAllNow.begin(BTN_FIRE_2_PIN);
  analogWrite(LED_FIRE_2_PIN, BRIGHTNESS_DIM_RED);
  pinMode(LED_FIRE_2_PIN, OUTPUT);
  fireANow.begin(BTN_FIRE_0_PIN);
  analogWrite(LED_FIRE_0_PIN, BRIGHTNESS_DIM_RED);
  pinMode(LED_FIRE_0_PIN, OUTPUT);
  fireBNow.begin(BTN_FIRE_1_PIN);
  analogWrite(LED_FIRE_1_PIN, BRIGHTNESS_DIM_RED);
  pinMode(LED_FIRE_1_PIN, OUTPUT);
  fireCNow.begin(BTN_FIRE_3_PIN);
  analogWrite(LED_FIRE_3_PIN, BRIGHTNESS_DIM_RED);
  pinMode(LED_FIRE_3_PIN, OUTPUT);
  fireDNow.begin(BTN_FIRE_4_PIN);
  analogWrite(LED_FIRE_4_PIN, BRIGHTNESS_DIM_RED);
  pinMode(LED_FIRE_4_PIN, OUTPUT);
  // reset midi counter to zero
  zero.begin(BTN_ZERO_PIN);
  analogWrite(LED_ZERO_PIN, BRIGHTNESS_DIM_BLUE);
  pinMode(LED_ZERO_PIN, OUTPUT);
  // tap bpm
  tap.begin(BTN_TAP_PIN);
  analogWrite(LED_TAP_PIN, BRIGHTNESS_DIM_BLUE);
  pinMode(LED_TAP_PIN, OUTPUT);
  // fire per beat frequency
  frequency.begin(NUM_FREQUENCY_BUTTONS, FREQUENCY_BUTTON_PINS, FREQUENCY_LED_PINS);

  // web portal
  // listen for boot character sequence
  Serial.println("Establishing connection with web server");
  Serial1.begin(115200);
  while(!Serial1);
  Serial.println("skipping.  implement web server later");
//   Serial.print("Connecting ...");
//   while (Serial1.available() <= 0) {
//     Serial.print(".");
//     delay(300);
//   }
//   String inString = "";
//   inString.reserve(10);
//   while (Serial1.available()) {
//     inString += Serial1.read();
//   }
//   Serial.print(inString);
//   Serial.println(" Success!");
//   // Send initial values
//   Serial1.print(offset);
//   Serial1.print(duration);
//   Serial1.print(bpm);
//   Serial1.print(mode);
}

void loop() {
  // 0. handle rotary encoder menu
  nav.doInput();
  if (nav.changed(0)) {
    u8g2.firstPage();
    do nav.doOutput(); while(u8g2.nextPage());
  }
  
  // 1. handle web portal
  // send updates
  if (hasConfigChange) {
    Serial.println("sending updated config to web server.");
    hasConfigChange = false;
    // Serial1.print(offset);
    // Serial1.print(duration);
    // Serial1.print(bpm);
    // Serial1.print(mode);
  }
  // fetch updates
  // while (Serial1.available()) {
  //   offset = Serial1.read();
  //   duration = Serial1.read();
  //   bpm = Serial1.read();
  //   mode = Serial1.read();
  // }
  
  // 2. update the inputs
  if (mode == MODE_MANUAL) {
    // handle tap button
    if (tap.update()) {
      Serial.println("tap button state change.");
      handleTap();
    }
  }
  if ( frequency.update() ) {
    Serial.println("at least one frequency button state change.");
    clocksPerTrigger = map(frequency.getValue(), 0, NUM_FREQUENCY_BUTTONS, CLOCK_TICKS_PER_BEAT/SCALE, CLOCK_TICKS_PER_BEAT*SCALE);
  }
  if (zero.update()) {
    Serial.println("zero button state change.");
    // reset button has just been pressed.  Reset the clock counters.
    resetClockCounter();
  }

  // 3. check beat for firing status
  // if there's no MIDI signal or manual beat and we're not manually firing, shut it down.
  if( getClockCounter()==255 && !fireAllNow.getState() ) {
    // shut it down
    if (!fireANow.getState()) {
      fireA.off();
    }
    if (!fireBNow.getState()) {
      fireB.off();
    }
    if (!fireCNow.getState()) {
      fireC.off();
    }
    if (!fireDNow.getState()) {
      fireD.off();
    }
  }
  // if we have a clock tick, a firing frequency, and we're not manually firing, do stuff.
  if( updateClockCounter() && !fireAllNow.getState()) {

    // we have a MIDI signal to follow, or a manual beat
    byte counter = getClockCounter();

    // how far back from the poof do we need to trigger the hardware?
    byte fireOnAt = (clocksPerTrigger - offset) % clocksPerTrigger;
    
    // and when do we need to turn it off?
    byte fireOffAt = (fireOnAt + duration) % clocksPerTrigger;

    // given the current counter and on/off times, should we shoot fire or not?
    fireAllPoofers( frequency.hasSelection() && timeForFire( counter, fireOnAt, fireOffAt ) );

    // report tick, noting we do this after the hardware-level update
    showBeat(getClockCounter() % CLOCK_TICKS_PER_BEAT);
  }

  // 4. override with the Make Fire Now buttons
  boolean fireAllNowStateChanged = fireAllNow.update();
  if (fireAllNowStateChanged) {
    togglePWMLED(fireAllNow.getState(), LED_FIRE_2_PIN, BRIGHTNESS_BRIGHT_RED, BRIGHTNESS_DIM_RED);
  }
  // if the Fire-All button isn't held, use the individual poofers' buttons to toggle them.
  if (fireANow.update()) {
    if (!fireAllNow.getState()) {
      Serial.println("manual fire A state toggle.");
      firePoofer(&fireA, fireANow.getState());
    }
  }
  if (fireBNow.update()) {
    if (!fireAllNow.getState()) {
      Serial.println("manual fire B state toggle.");
      firePoofer(&fireB, fireBNow.getState());
    }
  }
  if (fireCNow.update()) {
    if (!fireAllNow.getState()) {
      Serial.println("manual fire C state toggle.");
      firePoofer(&fireC, fireCNow.getState());
    }
  }
  if (fireDNow.update()) {
    if (!fireAllNow.getState()) {
      Serial.println("manual fire D state toggle.");
      firePoofer(&fireD, fireDNow.getState());
    }
  }

  // When the Fire-All button is pressed, poof all poofers.
  // When it's released, extinguish all those not individually held.
  if (fireAllNowStateChanged) {
    if (fireAllNow.getState()) {
      Serial.println("BOOOOSH!");
      // fire all poofers
      fireAllPoofers(true);
    } else {
      Serial.println("fire all toggled off.");
      if (!fireANow.getState()) {
        firePoofer(&fireA, false);
      }
      if (!fireBNow.getState()) {
        firePoofer(&fireB, false);
      }
      if (!fireCNow.getState()) {
        firePoofer(&fireC, false);
      }
      if (!fireDNow.getState()) {
        firePoofer(&fireD, false);
      }
    }
  }
  
  // 5. report changes in firing status (change in solenoid state)
  if ( fireA.update() ) {
    togglePWMLED(fireA.getState(), LED_FIRE_0_PIN, BRIGHTNESS_BRIGHT_RED, BRIGHTNESS_DIM_RED);
  }
  if ( fireB.update() ) {
    togglePWMLED(fireB.getState(), LED_FIRE_1_PIN, BRIGHTNESS_BRIGHT_RED, BRIGHTNESS_DIM_RED);
  }
  if ( fireC.update() ) {
    togglePWMLED(fireC.getState(), LED_FIRE_3_PIN, BRIGHTNESS_BRIGHT_RED, BRIGHTNESS_DIM_RED);
  }
  if ( fireD.update() ) {
    togglePWMLED(fireD.getState(), LED_FIRE_4_PIN, BRIGHTNESS_BRIGHT_RED, BRIGHTNESS_DIM_RED);
  }

  // MISC. code for debugging, reporting, etc. to the Serial line

  // We need CLOCK_TICKS_PER_BEAT updates per beat, so minimum updates per second is:
  static word updateFloor = CLOCK_TICKS_PER_BEAT * 200 / 60;

  // track updates per second.
  static unsigned long counter = 0;
  counter ++;
  static Metro updateInterval(1000UL);
  if ( updateInterval.check() ) {
    Serial << F("Updates per second: ") << counter << endl;
    if ( counter < updateFloor ) Serial << F("CAUTION: loop() < updateFloor!!") << endl;
    counter = 0;
    updateInterval.reset();
  }
}

// helper function to work through the modulo-24 stuff.  PITA.
boolean timeForFire( byte clock, byte start, byte stop ) {
  // edge case
  if( start == stop ) return( false );

  // easy case.
  if( stop > start ) {
    if( clock >= start && clock < stop ) return( true );
    else return( false );
  }

  // so, start > stop
  // harder case, with the modulo-24 stuff.  Ugh.
  if( clock >= stop && clock < start ) return( false );
  else return( true );
  
}

// BOOOOSH!  Fire all the poofers!
void fireAllPoofers(boolean doFire) {
  if ( doFire ) {
    fireA.on();
    fireB.on();
    fireC.on();
    fireD.on();
  } else {
    fireA.off();
    fireB.off();
    fireC.off();
    fireD.off();
  }
}

// BOOOOSH!  Fire one of the poofers.
void firePoofer(Solenoid *poofer, boolean makeFire) {
  if (makeFire) {
    poofer->on();
  } else {
    poofer->off();
  }
}

// brighten or dim an LED based on a state
void togglePWMLED(boolean state, byte pin, byte bright, byte dim) {
  if (state) {
    analogWrite(pin, bright);
  } else {
    analogWrite(pin, dim);
  }
}

void showBeat(byte count) {
  static byte lastCount = 255;
  if ( lastCount != count ) {
    lastCount = count;
    if ( count == 0 ) {
      analogWrite(LED_TAP_PIN, BRIGHTNESS_BRIGHT_BLUE);
    }
    if ( count == 1 ) {
      analogWrite(LED_TAP_PIN, BRIGHTNESS_DIM_BLUE);
    }
  }
}

// Listen for manually programmed beat.
// Called every time the tap button is pressed, 
// after 4 presses use the rolling average time between taps to set the manual BPM.
// Sample in groupings spaced by X seconds of no-tap apart.
void handleTap() {
  //TODO: this
  // // If programming, take rolling average of taps
  // if (programming) {
  //   if (isNewSampleGroup) {
  //     lastTap = micros();
  //     microsBetweenTaps = 0;
  //   }
  //   // time the tap
  //   static unsigned long lastTap = micros();
  //   unsigned long thisTap = micros();
  //   unsigned long deltaTap = thisTap - lastTap;
  //   lastTap = thisTap;

  //   // apply exponential smoothing
  //   const word smoothTap = 100;
  //   microsBetweenTaps = (microsBetweenTaps*(smoothTap-1) + deltaTap)/smoothTap;
  // }
}

void resetClockCounter() {
  midi.resetCounter();
  manualBeat.resetCounter();
}

byte getClockCounter() {
  if (mode == MODE_MIDI) {
    return midi.getCounter();
  } else {
    return manualBeat.getCounter();
  }
}

boolean updateClockCounter() {
  boolean hasMidiUpdate = midi.update();
  boolean hasManualUpdate = manualBeat.update();
  if (mode == MODE_MIDI) {
    return hasMidiUpdate;
  } else {
    return hasManualUpdate;
  }
}