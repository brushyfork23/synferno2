//TODO: add a menu option to set the minimum sequence priority we will render.
// It'd be like simulating degredation, but would be used for fuel saving.

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
// A8 to Rotary Encoder `CLK`
// A10 to Rotary Encoder `DT`
// 2 to Pushbutton Fire 0 `LED`
// 3 to Pushbutton Fire 1 `LED`
// 4 to Pushbutton Fire 2 `LED`
// 5 to Pushbutton Fire 3 `LED`
// 6 to Pushbutton Zero `LED`
// 7 to Pushbutton Freq 0 `LED`
// 8 to Pushbutton Freq 1 `LED`
// 9 to Pushbutton Freq 2 `LED`
// 10 to Pushbutton Freq 3 `LED`
// 11 to Pushbutton Freq 4 `LED`
// 12 to Pushbutton Tap `LED`
// 16 to MIDI `tx`
// 17 to MIDI `rx`
// 18 to ESP8266 `RX`
// 19 to ESP8266 `TX`
// 20 to OLED `SDA`
// 21 to OLED `SCLK`
// 22 to OLED `DC`
// 23 to OLED `RES`
// 24 to Rotary Encoder `SW`
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
// 36 to Pushbutton Fire All `signal`
// 37 to Pushbutton Fire 2 `signal`
// 38 to Pushbutton Fire 3 `signal`
// 39 to Pushbutton Zero `signal`
// 40 to Pushbutton Tap `signal`

// Is this actually necessary?
// The mega should be getting its power from the 12v through the barrel jack
// and all the 5v components should be powered from the buck converter.
// This would be taking the regulated +5 on the mega and piping it into
// the `+5` rail, and we probably don't want other components pulling off the mega for power.
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
// CLK to Mega A8
// DT to Mega A10
// SW to Mega 24
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
// ArduinoMenu_library: https://github.com/neu-rah/ArduinoMenu
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
#define BTN_FIRE_2_PIN 37
#define BTN_FIRE_3_PIN 38
#define BTN_FIRE_ALL_PIN 36
#define BTN_ZERO_PIN 39
#define BTN_TAP_PIN 40
#define LED_FIRE_0_PIN 2
#define LED_FIRE_1_PIN 3
#define LED_FIRE_2_PIN 4
#define LED_FIRE_3_PIN 5
#define LED_ZERO_PIN 6
#define LED_TAP_PIN 12
Button fireAllNow;
Button fireANow;
Button fireBNow;
Button fireCNow;
Button fireDNow;
Button zero;
Button tap;

// Sequence buttons
#include "ButtonGroup.h"
#define NUM_SEQUENCE_BUTTONS 5
#define SEQUENCE_SCALE 4
byte SEQUENCE_BUTTON_PINS[NUM_SEQUENCE_BUTTONS] = {29, 30, 31, 32, 33};
byte SEQUENCE_LED_PINS[NUM_SEQUENCE_BUTTONS] = {7, 8, 9, 10, 11};
ButtonGroup sequenceButtons;

// Sequences
#include "sequences.h";

// Fire Marshal
#include "FireMarshal.h"
FireMarshal fireMarshal;

/*
 * Begin Menu
 */
#include <menu.h>
#include <menuIO/U8x8Out.h>
#include <menuIO/keyIn.h>
#include <SPI.h>
using namespace Menu;
#define ENC_CLK    A8
#define ENC_DT    A10
#define ENC_BTN  24
#define OLED_CS A2
#define OLED_DC 22
#define OLED_RST 23
#define USE_HWI2C
U8X8_SSD1309_128X64_NONAME0_4W_SW_SPI u8x8(SCL, SDA, OLED_CS, OLED_DC, OLED_RST);

#define MODE_MIDI 0
#define MODE_MANUAL 1
boolean hasConfigChange = false;
int duration=7; // Number of clock ticks per beat to fire
float bpm=120.0;
int offset=0; // Number of clock ticks early to trigger the next beat
int mode=MODE_MIDI;


struct Sequence *seqAPtr = &sequence400;
struct Sequence *seqBPtr = &sequence200;
struct Sequence *seqCPtr = &sequence100;
struct Sequence *seqDPtr = &sequence050;
struct Sequence *seqEPtr = &sequence025;

result selectMidi();
result selectManual();
result configUpdate() {
  hasConfigChange = true;
  return proceed;
}
result onBPMMenuUpdate() {
  manualBeat.setBPM(bpm);
  setBpm(bpm);
  return configUpdate();
}

result onDurationMenuUpdate() {
  fireMarshal.setDuration(duration);
  updateSequenceDegredation();
  return configUpdate();
}

TOGGLE(mode,modeMenu,"Mode     ",Menu::doNothing,Menu::noEvent,Menu::noStyle
  ,VALUE("Midi",MODE_MIDI,selectMidi,Menu::noEvent)
  ,VALUE("Manual",MODE_MANUAL,selectManual,Menu::noEvent)
);

SELECT(seqAPtr,bntAModeMenu,"Seq A   ",Menu::doNothing,Menu::noEvent,Menu::noStyle
  ,VALUE("400",&sequence400,configUpdate,Menu::noEvent)
  ,VALUE("200",&sequence200,configUpdate,Menu::noEvent)
  ,VALUE("100",&sequence100,configUpdate,Menu::noEvent)
  ,VALUE("050",&sequence050,configUpdate,Menu::noEvent)
  ,VALUE("025",&sequence025,configUpdate,Menu::noEvent)
);

SELECT(seqBPtr,bntBModeMenu,"Seq B   ",Menu::doNothing,Menu::noEvent,Menu::noStyle
  ,VALUE("400",&sequence400,configUpdate,Menu::noEvent)
  ,VALUE("200",&sequence200,configUpdate,Menu::noEvent)
  ,VALUE("100",&sequence100,configUpdate,Menu::noEvent)
  ,VALUE("050",&sequence050,configUpdate,Menu::noEvent)
  ,VALUE("025",&sequence025,configUpdate,Menu::noEvent)
);

SELECT(seqCPtr,bntCModeMenu,"Seq C   ",Menu::doNothing,Menu::noEvent,Menu::noStyle
  ,VALUE("400",&sequence400,configUpdate,Menu::noEvent)
  ,VALUE("200",&sequence200,configUpdate,Menu::noEvent)
  ,VALUE("100",&sequence100,configUpdate,Menu::noEvent)
  ,VALUE("050",&sequence050,configUpdate,Menu::noEvent)
  ,VALUE("025",&sequence025,configUpdate,Menu::noEvent)
);

SELECT(seqDPtr,bntDModeMenu,"Seq D   ",Menu::doNothing,Menu::noEvent,Menu::noStyle
  ,VALUE("400",&sequence400,configUpdate,Menu::noEvent)
  ,VALUE("200",&sequence200,configUpdate,Menu::noEvent)
  ,VALUE("100",&sequence100,configUpdate,Menu::noEvent)
  ,VALUE("050",&sequence050,configUpdate,Menu::noEvent)
  ,VALUE("025",&sequence025,configUpdate,Menu::noEvent)
);

SELECT(seqEPtr,bntEModeMenu,"Seq E   ",Menu::doNothing,Menu::noEvent,Menu::noStyle
  ,VALUE("400",&sequence400,configUpdate,Menu::noEvent)
  ,VALUE("200",&sequence200,configUpdate,Menu::noEvent)
  ,VALUE("100",&sequence100,configUpdate,Menu::noEvent)
  ,VALUE("050",&sequence050,configUpdate,Menu::noEvent)
  ,VALUE("025",&sequence025,configUpdate,Menu::noEvent)
);

MENU(mainMenu,"   SYNFERNO",Menu::doNothing,Menu::noEvent,Menu::noStyle
  ,FIELD(duration,"Duration","",1,23,1,0,onDurationMenuUpdate,Menu::exitEvent,Menu::noStyle)
  ,FIELD(offset,"Offset  ","",0,23,1,0,configUpdate,Menu::exitEvent,Menu::wrapStyle)
  ,FIELD(bpm,"BPM     ","",0.0,300.0,1.0,0.1,onBPMMenuUpdate,Menu::exitEvent,Menu::noStyle)
  ,SUBMENU(modeMenu)
  ,SUBMENU(bntAModeMenu)
  ,SUBMENU(bntBModeMenu)
  ,SUBMENU(bntCModeMenu)
  ,SUBMENU(bntDModeMenu)
  ,SUBMENU(bntEModeMenu)
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
    setBpm(120.0);
  }
  return configUpdate();
}

//#include <menuIO/clickEncoderIn.h>
#include "clickEncoderIn.h"
ClickEncoder clickEncoder(ENC_CLK, ENC_DT, ENC_BTN, LOW);
ClickEncoderStream encStream(clickEncoder,1);

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
struct Sequence *activeSequence;

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

  // load up the sequences
  Sequences::init();

  // this sequence is not actually active, but this way updates to the "current sequence" don't attempt to set null values
  activeSequence = seqAPtr;

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
  fireAllNow.begin(BTN_FIRE_ALL_PIN);
  fireANow.begin(BTN_FIRE_0_PIN);
  analogWrite(LED_FIRE_0_PIN, BRIGHTNESS_DIM_RED);
  pinMode(LED_FIRE_0_PIN, OUTPUT);
  fireBNow.begin(BTN_FIRE_1_PIN);
  analogWrite(LED_FIRE_1_PIN, BRIGHTNESS_DIM_RED);
  pinMode(LED_FIRE_1_PIN, OUTPUT);
  fireCNow.begin(BTN_FIRE_2_PIN);
  analogWrite(LED_FIRE_2_PIN, BRIGHTNESS_DIM_RED);
  pinMode(LED_FIRE_2_PIN, OUTPUT);
  fireDNow.begin(BTN_FIRE_3_PIN);
  analogWrite(LED_FIRE_3_PIN, BRIGHTNESS_DIM_RED);
  pinMode(LED_FIRE_3_PIN, OUTPUT);
  // reset midi counter to zero
  zero.begin(BTN_ZERO_PIN);
  analogWrite(LED_ZERO_PIN, BRIGHTNESS_DIM_YELLOW);
  pinMode(LED_ZERO_PIN, OUTPUT);
  // tap bpm
  tap.begin(BTN_TAP_PIN);
  analogWrite(LED_TAP_PIN, BRIGHTNESS_DIM_YELLOW);
  pinMode(LED_TAP_PIN, OUTPUT);
  manualBeat.setBPM(bpm);
  // sequences of poofs
  sequenceButtons.begin(NUM_SEQUENCE_BUTTONS, SEQUENCE_BUTTON_PINS, SEQUENCE_LED_PINS);

  // fire up the fire marshal
  fireMarshal.setDuration(duration);
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

  // 3. handle sequence selection button group
  if ( sequenceButtons.update() && sequenceButtons.hasSelection() ) {
    switch (sequenceButtons.getValue()) {
      case 0:
        activeSequence = seqAPtr;
        break;
      case 1:
        activeSequence = seqBPtr;
        break;
      case 2:
        activeSequence = seqCPtr;
        break;
      case 3:
        activeSequence = seqDPtr;
        break;
      case 4:
        activeSequence = seqEPtr;
        break;
    }
    updateSequenceDegredation();
  }
  
  // 4. handle zero button
  // If the zero button is momentarily pressed, reset the clock counters. This marks the beginning of a bar.
  if (zero.update()) {
    togglePWMLED(zero.getState(), LED_ZERO_PIN, BRIGHTNESS_BRIGHT_YELLOW, BRIGHTNESS_DIM_YELLOW);
    if (zero.getState()) {
      resetClockCounter();
    }
  }

  // 5. handle beat
  // if we have no beat (manual or MIDI), shut it down.
  if (getClockCounter()==255) {
    fireMarshal.setSequenceTriggers(DURATION_NONE, DURATION_NONE, DURATION_NONE, DURATION_NONE);
  }
  // if we have a clock tick, update the firing status and beat indicators.
  if( updateClockCounter() ) {
    handleBeat();
  }

  // 6. Handle poofers.
  // provide the fire marshal with the most up-to-date button and counter states
  fireAllNow.update();
  fireANow.update();
  fireBNow.update();
  fireCNow.update();
  fireDNow.update();
  fireMarshal.setManualAll(fireAllNow.getState());
  fireMarshal.setManualA(fireANow.getState());
  fireMarshal.setManualB(fireBNow.getState());
  fireMarshal.setManualC(fireCNow.getState());
  fireMarshal.setManualD(fireDNow.getState());
  // process all the states and determine firing status
  fireMarshal.update();
  // actually turn the poofers on or off, based on the determination of the fire marshal
  if (fireMarshal.getFireStateA()) {
    if (!fireA.getState()) {
        fireA.on();
    }
  } else {
      if (fireA.getState()) {
          fireA.off();
      }
  }
  if (fireMarshal.getFireStateB()) {
      if (!fireB.getState()) {
          fireB.on();
      }
  } else {
      if (fireB.getState()) {
          fireB.off();
      }
  }
  if (fireMarshal.getFireStateC()) {
      if (!fireC.getState()) {
          fireC.on();
      }
  } else {
      if (fireC.getState()) {
          fireC.off();
      }
  }
  if (fireMarshal.getFireStateD()) {
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
    togglePWMLED(fireC.getState(), LED_FIRE_2_PIN, BRIGHTNESS_BRIGHT_RED, BRIGHTNESS_DIM_RED);
  }
  if ( fireD.update() ) {
    togglePWMLED(fireD.getState(), LED_FIRE_3_PIN, BRIGHTNESS_BRIGHT_RED, BRIGHTNESS_DIM_RED);
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
    setBpm(midi.getBPM());
    return hasMidiUpdate;
  } else {
    return hasManualUpdate;
  }
}

void setBpm(float val) {
  // set the new global value
  bpm = val;
  if (bpm > 0) {
    // update sequence priority support level
    updateSequenceDegredation();
  }
}

// determine what priority level we can support for the given bpm, duration, and sequence.
void updateSequenceDegredation() {
  activeSequence->updateViablePriority(minimumTicksBetweenLargePoofTrigger());
}

// determine firing time and display beat information.
void handleBeat() {
  byte counter = getClockCounter();

  // report beat
  showBeat((counter + offset) % CLOCK_TICKS_PER_BEAT);

  // report bar beginning
  if (!zero.getState()){
    showBar( (counter + offset) % (CLOCK_TICKS_PER_BEAT * SCALE));
  }

  // how far back from the beat do we need to trigger each poofer?
  if (!sequenceButtons.hasSelection()) {
    fireMarshal.setSequenceTriggers(DURATION_NONE, DURATION_NONE, DURATION_NONE, DURATION_NONE);
  } else { 
    TickTriggers triggers = activeSequence->getTickTriggers(counter + offset);
    // Serial << F("tick triggers: A ") << triggers.poofSizeA << F(" B ") << triggers.poofSizeB << F(" C ") << triggers.poofSizeC << F(" D ") << triggers.poofSizeD << endl;
    fireMarshal.setSequenceTriggers(triggers.poofSizeA, triggers.poofSizeB, triggers.poofSizeC, triggers.poofSizeD);
  }

  fireMarshal.tickBeatCounter();
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

/*
  Compute the number of ticks required to perform a large poof.

  The minimum ticks between triggers is
  ceil(millisPerTrigger / millisPerTick)

  millisPerTrigger is (duration * millisPerTick) + lockout window

  Fully expanded, minimum ticks between triggers would be:
  duration * ((MILLIS_PER_MINUTE / bpm) / CLOCK_TICKS_PER_BEAT) + 200UL
                                /
        ((MILLIS_PER_MINUTE / bpm) / CLOCK_TICKS_PER_BEAT)
  
 */
uint8_t minimumTicksBetweenLargePoofTrigger() {
  int millisPerBeat = MILLIS_PER_MINUTE / bpm;
  int millisPerTick = millisPerBeat / CLOCK_TICKS_PER_BEAT;

  return ceil(duration + (200UL / millisPerTick));
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

void showBar(byte count) {
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
#define TAP_PROGRAMMING_EXPIRY_WINDOW_MICROS 1700000UL // start over after inactivity
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
    setBpm(MICROS_PER_MINUTE * 1.0 / microsPerBeat);
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
  return;
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
          setBpm(inNum);
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