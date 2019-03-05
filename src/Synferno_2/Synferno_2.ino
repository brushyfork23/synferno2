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
// A10 to Rotary Encoder `B`
// 2 to Pushbutton Fire 0 `LED`
// 3 to Pushbutton Fire 1 `LED`
// 4 to Pushbutton Fire 3 `LED`
// 5 to Pushbutton Fire 4 `LED`
// 6 to Pushbutton Zero `LED`
// 7 to Pushbutton Freq 0 `LED`
// 8 to Pushbutton Freq 1 `LED`
// 9 to Pushbutton Freq 2 `LED`
// 10 to Pushbutton Freq 3 `LED`
// 11 to Pushbutton Freq 4 `LED`
// 12 to Pushbutton Tap `LED`
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
// SDA to Mega 20
// SCLK to Mega 21
// VDD to Buck Converter `+5`
// VSS to GND

// Click Encoder
// A to Mega A8
// B to Mega A10
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

// Required libraries
// ArduinoStreaming: https://github.com/geneReeves/ArduinoStreaming
// Metro: https://github.com/thomasfredericks/Metro-Arduino-Wiring
// Bounce2: https://github.com/thomasfredericks/Bounce2
// ArduinoMenu: https://github.com/neu-rah/ArduinoMenu
// > encoder: https://github.com/christophepersoz/encoder
// U8g2: https://github.com/olikraus/U8g2_Arduino

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
#define BRIGHTNESS_BRIGHT_RED 230
#define BRIGHTNESS_DIM_RED 20
#define BRIGHTNESS_BRIGHT_YELLOW 255
#define BRIGHTNESS_DIM_YELLOW 30
#define BTN_FIRE_0_PIN 34
#define BTN_FIRE_1_PIN 35
#define BTN_FIRE_2_PIN 36
#define BTN_FIRE_3_PIN 37
#define BTN_FIRE_4_PIN 38
#define BTN_ZERO_PIN 39
#define BTN_TAP_PIN 40
#define LED_FIRE_0_PIN 2
#define LED_FIRE_1_PIN 3
#define LED_FIRE_3_PIN 4
#define LED_FIRE_4_PIN 5
#define LED_ZERO_PIN 6
#define LED_TAP_PIN 12
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
#define FREQUENCY_SCALE 4
byte FREQUENCY_BUTTON_PINS[NUM_FREQUENCY_BUTTONS] = {29, 30, 31, 32, 33};
byte FREQUENCY_LED_PINS[NUM_FREQUENCY_BUTTONS] = {7, 8, 9, 10, 11};
ButtonGroup frequency;


/*
 * Begin Menu
 */
#include <menu.h>
#include <menuIO/U8x8Out.h>
#include <menuIO/keyIn.h>
#include <SPI.h>
using namespace Menu;
#define ENC_A    A8
#define ENC_B    A10
#define ENC_BTN  24
#define OLED_CS A2
#define OLED_DC 22
#define OLED_RST 23
#define USE_HWI2C
U8X8_SSD1309_128X64_NONAME0_4W_SW_SPI u8x8(SCL, SDA, OLED_CS, OLED_DC, OLED_RST);

#define MODE_MIDI 0
#define MODE_MANUAL 1
boolean hasConfigChange = false;
int duration=2; // Number of clock ticks per beat to fire
float bpm=120.0;
int offset=0; // Number of clock ticks early to trigger the next beat
int mode=MODE_MIDI;

TOGGLE(mode,modeMenu,"Mode     ",doNothing,noEvent,noStyle
  ,VALUE("Midi",MODE_MIDI,selectMidi,exitEvent)
  ,VALUE("Manual",MODE_MANUAL,selectManual,exitEvent)
);

MENU(mainMenu,"   SYNFERNO",doNothing,noEvent,noStyle
  ,FIELD(duration,"Duration","",1,23,1,0,configUpdate,exitEvent,noStyle)
  ,FIELD(offset,"Offset  ","",0,23,1,0,configUpdate,exitEvent,noStyle)
  ,FIELD(bpm,"BPM     ","",0.0,300.0,1.0,0.1,editBPM,exitEvent,noStyle)
  ,SUBMENU(modeMenu)
);

#define MAX_DEPTH 2

result selectMidi() {
  // Disable manual BPM setting
  mainMenu[2].enabled=disabledStatus;
  return configUpdate();
}

result selectManual() {
  // Enable manual BPM setting
  mainMenu[2].enabled=enabledStatus;
  manualBeat.resetCounter();
  if (bpm == 0.0) {
    bpm = 120.0;
  }
  return configUpdate();
}

result editBPM() {
  manualBeat.setBPM(bpm);
  return configUpdate();
}

result configUpdate() {
  hasConfigChange = true;
  return proceed;
}


#include <menuIO/clickEncoderIn.h>
ClickEncoder clickEncoder(ENC_A,ENC_B,ENC_BTN,2);
ClickEncoderStream encStream(clickEncoder,2);

MENU_OUTPUTS(out,MAX_DEPTH
  ,U8X8_OUT(u8x8,{0,0,16,8})
  ,NONE
);
  
NAVROOT(nav,mainMenu,MAX_DEPTH,encStream,out);
/**
 * End MENU
 */


// Local variables
long inNum = 0;
char inCommand;
byte clocksPerTrigger = CLOCK_TICKS_PER_BEAT;
boolean beatSaysFire = false;
boolean lastBeatSaysFire = false;
boolean beatFireA = false;
boolean beatFireB = false;
boolean beatFireC = false;
boolean beatFireD = false;
byte firingGroup = 0;
float suspendedAtBPM;
boolean suspendBeatReactions = false;

void setup() {
  Serial.begin(115200);
  while(!Serial);

  Serial1.begin(115200);
  while(!Serial1);

  // fire up the Screen
  SPI.begin();
  u8x8.begin();
  /*
  u8x8_font_artossans8_r
  u8x8_font_victoriamedium8_r
  u8x8_font_pxplusibmcgathin_f
  u8x8_font_pxplusibmcga_f
  u8x8_font_pressstart2p_f
  u8x8_font_pxplustandynewtv_f
  */
  u8x8.setFont(u8x8_font_artossans8_r);

  // configure Menu
  nav.showTitle=false;
  mainMenu[2].enabled=disabledStatus;

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
  analogWrite(LED_ZERO_PIN, BRIGHTNESS_DIM_YELLOW);
  pinMode(LED_ZERO_PIN, OUTPUT);
  // tap bpm
  tap.begin(BTN_TAP_PIN);
  analogWrite(LED_TAP_PIN, BRIGHTNESS_DIM_YELLOW);
  pinMode(LED_TAP_PIN, OUTPUT);
  manualBeat.setBPM(bpm);
  // fire per beat frequency
  frequency.begin(NUM_FREQUENCY_BUTTONS, FREQUENCY_BUTTON_PINS, FREQUENCY_LED_PINS);
}

void loop() {
  // 0. handle rotary encoder menu
  static Metro encoderUpdate(1UL);
  if (encoderUpdate.check()) {
    clickEncoder.service();
    encoderUpdate.reset();
  }
   static Metro navInterval(1UL);
   if (navInterval.check()) {
     navInterval.reset();
    nav.poll();
   }
  
  // 1. handle web portal
  // send updates
  if (hasConfigChange) {
    hasConfigChange = false;
    Serial1.print('O');
    Serial1.println(offset);
    Serial1.print('D');
    Serial1.println(duration);
    Serial1.print('B');
    Serial1.println(bpm);
    Serial1.print('M');
    Serial1.println(mode);
  }
  // fetch updates
  handleWebserverUpdates();
  
  // 2. handle tap button
  if (mode == MODE_MANUAL) {
    if (tap.update() && tap.getState()) {
      handleTap();
    }
  }

  // 3. handle frequency selection button group
  if ( frequency.update() && frequency.hasSelection() ) {
    switch (frequency.getValue()) {
      case 0:
        clocksPerTrigger = 96;
        break;
      case 1:
        clocksPerTrigger = 48;
        break;
      case 2:
        clocksPerTrigger = 24;
        break;
      case 3:
        clocksPerTrigger = 12;
        break;
      case 4:
        clocksPerTrigger = 6;
        break;
    }
    // const int frequencyMultiplier = CLOCK_TICKS_PER_BEAT / FREQUENCY_SCALE;
    // clocksPerTrigger = (NUM_FREQUENCY_BUTTONS - frequency.getValue()) * frequencyMultiplier;
  }
  
  // 4. handle zero button
  static Metro holdToSuspend(1700UL);
  // If the zero button is momentarily pressed, reset the clock counters. This marks the beginning of a stanza.
  if (zero.update()) {
    togglePWMLED(zero.getState(), LED_ZERO_PIN, BRIGHTNESS_BRIGHT_YELLOW, BRIGHTNESS_DIM_YELLOW);
    if (zero.getState()) {
      holdToSuspend.reset();
      suspendBeatReactions = false;
      resetClockCounter();
    }
  }
  // If the zero button is held, suspend beat reactions until a new BPM is detected
  // or the zero button is pressed again.
  if (zero.getState()) {
    if (holdToSuspend.check()) {
      // record the current BPM
      suspendedAtBPM = bpm;
      // set flag to suspend beat reactions
      suspendBeatReactions = true;
      // ensure beat does not trigger fire
      beatSaysFire = false;
      // turn off the Zero button's LED
      togglePWMLED(false, LED_ZERO_PIN, BRIGHTNESS_BRIGHT_YELLOW, BRIGHTNESS_DIM_YELLOW);
    }
  }

  // 5. handle beat
  // if we have no beat (manual or MIDI), shut it down.
  if (getClockCounter()==255) {
    beatSaysFire = false;
  }
  // if we have a clock tick, update the firing status and beat indicators.
  if( updateClockCounter() ) {
    handleBeat();
  }

  // 6. handle poofers
  // Turn the poofers on or off, depending on beat and buttons.
  // update the state of the fire-now buttons
  fireAllNow.update();
  fireANow.update();
  fireBNow.update();
  fireCNow.update();
  fireDNow.update();
  // if any of the relevant states of buttons or clicks indicate that
  // it's time to fire, ensure the poofer is lit.  Otherwise, ensure
  // that it is extinguished.
  if (fireAllNow.getState() || fireANow.getState() || beatFireA) {
    if (!fireA.getState()) {
      fireA.on();
    }
  } else {
    if (fireA.getState()) {
      fireA.off();
    }
  }
  if (fireAllNow.getState() || fireBNow.getState() || beatFireB) {
    if (!fireB.getState()) {
      fireB.on();
    }
  } else {
    if (fireB.getState()) {
      fireB.off();
    }
  }
  if (fireAllNow.getState() || fireCNow.getState() || beatFireC) {
    if (!fireC.getState()) {
      fireC.on();
    }
  } else {
    if (fireC.getState()) {
      fireC.off();
    }
  }
  if (fireAllNow.getState() || fireDNow.getState() || beatFireD) {
    if (!fireD.getState()) {
      fireD.on();
    }
  } else {
    if (fireD.getState()) {
      fireD.off();
    }
  }
  
  // 7. handle fire indicators
  // Report changes in firing status (change in solenoid state) by lighting the fire-now buttons.
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
    //Serial << F("Updates per second: ") << counter << endl;
    if ( counter < updateFloor ) Serial << F("CAUTION: loop() < updateFloor!!") << endl;
    counter = 0;
    updateInterval.reset();
  }
}

boolean updateClockCounter() {
  boolean hasMidiUpdate = midi.update();
  boolean hasManualUpdate = manualBeat.update();
  if (mode == MODE_MIDI) {
    bpm = midi.getBPM();
    return hasMidiUpdate;
  } else {
    return hasManualUpdate;
  }
}

// determine firing time and display beat information.
void handleBeat() {
  byte counter = getClockCounter();

  // ensure beat reactions are enabled
  if (suspendBeatReactions) {
    // when the BPM changes, resume operation
    if (suspendedAtBPM == bpm) {
      return;
    }
    suspendBeatReactions = false;
  }

  // report beat
  showBeat((counter + offset) % CLOCK_TICKS_PER_BEAT);

  // report stanza beginning
  if (!zero.getState()){
    showStanza(counter + offset);
  }

  // how far back from the beat do we need to trigger each poofer?
  byte fireAOnAt;
  byte fireBOnAt;
  byte fireCOnAt;
  byte fireDOnAt;
  byte modifiedClocksPerTrigger = clocksPerTrigger;
  // if the triggers are coming too often, spread them out
  if (!tooFastForPoofers(clocksPerTrigger)) {
    // 1 group
    fireAOnAt = (clocksPerTrigger - offset) % clocksPerTrigger;
    fireBOnAt = (clocksPerTrigger - offset) % clocksPerTrigger;
    fireCOnAt = (clocksPerTrigger - offset) % clocksPerTrigger;
    fireDOnAt = (clocksPerTrigger - offset) % clocksPerTrigger;
  } else if (!tooFastForPoofers(clocksPerTrigger*2)) {
    // 2 groups; double the ticks-per-trigger window and offset half of the poofers by 1/2 ticks
    modifiedClocksPerTrigger = clocksPerTrigger * 2;

    fireAOnAt = (modifiedClocksPerTrigger - offset + clocksPerTrigger) % modifiedClocksPerTrigger;
    fireBOnAt = (modifiedClocksPerTrigger - offset) % modifiedClocksPerTrigger;
    fireCOnAt = (modifiedClocksPerTrigger - offset) % modifiedClocksPerTrigger;
    fireDOnAt = (modifiedClocksPerTrigger - offset + clocksPerTrigger) % modifiedClocksPerTrigger;
  } else {
    // 4 groups; quadruple the ticks-per-trigger window and offset each of the poofers by 1/4 ticks
    modifiedClocksPerTrigger = clocksPerTrigger * 4;

    fireAOnAt = (modifiedClocksPerTrigger - offset + clocksPerTrigger) % modifiedClocksPerTrigger;
    fireBOnAt = (modifiedClocksPerTrigger - offset + (3 * clocksPerTrigger)) % modifiedClocksPerTrigger;
    fireCOnAt = (modifiedClocksPerTrigger - offset) % modifiedClocksPerTrigger;
    fireDOnAt = (modifiedClocksPerTrigger - offset + (2 * clocksPerTrigger)) % modifiedClocksPerTrigger;
  }
  
  // and when do we need to turn them off?
  byte fireAOffAt = (fireAOnAt + duration) % modifiedClocksPerTrigger;
  byte fireBOffAt = (fireBOnAt + duration) % modifiedClocksPerTrigger;
  byte fireCOffAt = (fireCOnAt + duration) % modifiedClocksPerTrigger;
  byte fireDOffAt = (fireDOnAt + duration) % modifiedClocksPerTrigger;
  
  // given the current counter and on/off times, should we shoot fire or not?
  beatFireA = frequency.hasSelection() && timeForFire( counter % modifiedClocksPerTrigger, fireAOnAt, fireAOffAt );
  beatFireB = frequency.hasSelection() && timeForFire( counter % modifiedClocksPerTrigger, fireBOnAt, fireBOffAt );
  beatFireC = frequency.hasSelection() && timeForFire( counter % modifiedClocksPerTrigger, fireCOnAt, fireCOffAt );
  beatFireD = frequency.hasSelection() && timeForFire( counter % modifiedClocksPerTrigger, fireDOnAt, fireDOffAt );
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

// Given the bpm and duration, will this small of a ticksPerTrigger result
// in more triggers than the poofers can handle.
boolean tooFastForPoofers(byte ticksPerTrigger) {
  int millisPerBeat = MILLIS_PER_MINUTE / bpm;
  int millisPerTick = millisPerBeat / CLOCK_TICKS_PER_BEAT;
  int durationMillis = millisPerTick * duration;
  return millisPerTick * ticksPerTrigger < durationMillis + 200UL;
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
      analogWrite(LED_TAP_PIN, BRIGHTNESS_BRIGHT_YELLOW);
    }
    if ( count == 2 ) {
      analogWrite(LED_TAP_PIN, BRIGHTNESS_DIM_YELLOW);
    }
  }
}

void showStanza(byte count) {
  static byte lastCount = 255;
  if ( lastCount != count ) {
    lastCount = count;
    if ( count == 0 ) {
      analogWrite(LED_ZERO_PIN, BRIGHTNESS_BRIGHT_YELLOW);
    }
    if ( count == 2 ) {
      analogWrite(LED_ZERO_PIN, BRIGHTNESS_DIM_YELLOW);
    }
  }
}

// Listen for manually programmed beat.
// Called every time the tap button is pressed, 
// after 4 presses use the rolling average time between taps to set the manual BPM.
// Sample in groupings spaced by X seconds of no-tap apart.
#define MICROS_PER_MINUTE 60000000UL
#define TAP_PROGRAMMING_EXPIRY_WINDOW_MICROS 1700000UL
#define TAPS_BEFORE_WRITE 4
unsigned long microsPerBeat;
void handleTap() {
  // time the tap
  static unsigned long lastTap = micros();
  unsigned long thisTap = micros();
  unsigned long deltaTap = thisTap - lastTap;
  lastTap = thisTap;
  static int taps = 0;
  if (deltaTap > TAP_PROGRAMMING_EXPIRY_WINDOW_MICROS) {
    taps = 0;
  }

  if (taps++ == 0) {
    return;
  }
  
  // smooth delta between taps
  const word smoothDelta = 3;
  microsPerBeat = (microsPerBeat*(smoothDelta-1) + deltaTap)/smoothDelta;

  if (taps >= TAPS_BEFORE_WRITE) {
    bpm = MICROS_PER_MINUTE * 1.0 / microsPerBeat;
    manualBeat.setBPM(bpm);
  }
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

void handleWebserverUpdates() {
  while (Serial1.available() > 0) {
    int inChar = Serial1.read();
    Serial << (char)inChar;
     if (isDigit(inChar)) {
      inNum = inNum * 10 + (inChar - '0');
    } else if ((char)inChar != '\n') {
      inCommand = (char)inChar;
    }

    if ((char)inChar == '\n') {
      switch (inCommand) {
        case 'O':
          offset = inNum;
          Serial << F("offset: ") << inNum << endl;
          break;
        case 'D':
          duration = inNum;
          Serial << F("duration: ") << inNum << endl;
          break;
        case 'B':
          bpm = inNum;
          Serial << F("bpm: ") << inNum << endl;
          break;
        case 'M':
          mode = inNum;
          Serial << F("mode: ") << inNum << endl;
          break;
        default:
          Serial << F("inCommand: ") << inCommand << F("_") << (int)inCommand << endl;
          break;
      }
      Serial << F("clearing inNum") << endl;
      inNum = 0;
      inCommand = '\0';
    }
  }
}