
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
// 2 to Rotary Encoder `A`
// 3 to Rotary Encoder `B`
// 6 to Pushbutton Zero `LED`
// 7 to Pushbutton Freq 0 `LED`
// 8 to Pushbutton Freq 1 `LED`
// 9 to Pushbutton Freq 2 `LED`
// 10 to Pushbutton Freq 3 `LED`
// 11 to Pushbutton Freq 4 `LED`
// 12 to Pushbutton Fire `LED`
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
// 39 to Pushbutton Zero `signal`
// 40 to Pushbutton Tap `signal`
// VCC to Buck Converter `+5`
// GND to GND

// WEMOS LOLIN D1 mini (ESP8266)
// TX to Mega 19
// RX to Mega 18
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
// A to Mega 2
// B to Mega 3
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
// tx to Mega 16
// rx to Mega 17
// + to Buck Converter `+5`
// - to GND



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

#include <Streaming.h>
#include <Metro.h>

// // OLED
// #include "OLED.h"
// OLED oled;

// MIDI
#include "MIDI.h"
MIDI midi;

// Solenoids
#include "Solenoid.h"
Solenoid fireLeft, fireRight;

// Fire button
#include "Button.h"
Button makeFireNow;
Button resetCounter;
Button tapCounter;

// Frequency buttons
#include "ButtonGroup.h"
#define NUM_FREQUENCY_BUTTONS 5
byte FREQUENCY_BUTTON_PINS[NUM_FREQUENCY_BUTTONS] = {29, 30, 31, 32, 33};
byte FREQUENCY_LED_PINS[NUM_FREQUENCY_BUTTONS] = {7, 8, 9, 10, 11};
ButtonGroup frequency;

// Web Portal
#include "Portal.h"

// Menu
#include <menu.h>
#include <Ticker.h>
Ticker updateEncoder;
#include <ClickEncoder.h>
#include <menuIO/clickEncoderIn.h>
#include <menuIO/u8g2Out.h>
#include <menuIO/chainStream.h>
#include <menuIO/serialOut.h>
#include <menuIO/serialIn.h>
#define encA    32
#define encB    4
#define encBtn  19
#include <Wire.h>
#define OLED_CS A2
#define OLED_DC 2
#define OLED_RST 4
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

int mode=0;
unsigned int midiDelay=0;
unsigned int offset=0;
int bpm=150;

void selectMidi() {
  midiDelay = 10;
}

void selectManual() {
  midiDelay = 20;
}

SELECT(mode,modeMenu,"Mode",doNothing,noEvent,noStyle
  ,VALUE("Midi Sync",0,selectMidi,enterEvent)
  ,VALUE("Manual",1,selectManual,enterEvent)
);

MENU(mainMenu,"SYNFERNO",doNothing,noEvent,wrapStyle
  ,FIELD(midiDelay,"Delay","",0,24,1,0,doNothing,noEvent,noStyle)
  ,FIELD(offset,"Offset","",0,24,1,0,doNothing,noEvent,noStyle)
  ,FIELD(bpm,"BPM","",0,300,1,0,doNothing,noEvent,noStyle)
  ,SUBMENU(modeMenu)
);

#define MAX_DEPTH 2

ClickEncoder clickEncoder(encA,encB,encBtn,4);
ClickEncoderStream encStream(clickEncoder,1);

serialIn serial(Serial);

MENU_INPUTS(in,&encStream,&serial);
void timerIsr() {clickEncoder.service();}

MENU_OUTPUTS(out,MAX_DEPTH
  ,U8G2_OUT(u8g2,colors,fontX,fontY,offsetX,offsetY,{0,0,U8_Width/fontX,U8_Height/fontY})
  ,NONE//,SERIAL_OUT(Serial)
);
  

NAVROOT(nav,mainMenu,MAX_DEPTH,in,out);

byte duration;

void setup() {
  Serial.begin(115200);
  while(!Serial);

  // fire up the Screen
  Wire.begin();
  u8g2.begin();
  u8g2.setFont(fontName);

  // configure Menu
  nav.showTitle=false;

  // fire up the rotary encoder
  updateEncoder.attach_ms(1, timerIsr);

  // fire up MIDI
  midi.begin();
  showMIDI(midi.getCounter());

  // fire up the fire
  fireLeft.begin(SOLENOID_PIN1);
  showFireLeft(fireLeft.getState());
  fireRight.begin(SOLENOID_PIN2);
  showFireRight(fireRight.getState());

  // knobs
  showDuration(duration);
  showOffset(offset);

  // buttons
  makeFireNow.begin(POOF_BOTH_BUTTON_PIN);
  showMakeFireNow(makeFireNow.getState());
  resetCounter.begin(RESET_BUTTON_PIN);

  frequency.begin(NUM_FREQUENCY_BUTTONS, FREQUENCY_BUTTON_PINS, FREQUENCY_LED_PINS);
  showFrequency(frequency.getValue());

  // web portal
  Serial.println("Launching access point and web portal...");
  portal.begin();
  Serial.print("IP address: ");
  Serial.println(portal.getIp());
  Serial.print("Hostname: ");
  Serial.println(portal.getHostname());
}

void loop() {
  // 0. handle rotary encoder menu
  nav.doInput();
  // digitalWrite(LEDPIN, ledCtrl);
  if (nav.changed(0)) {//only draw if menu changed for gfx device
    //change checking leaves more time for other tasks
    u8g2.firstPage();
    do nav.doOutput(); while(u8g2.nextPage());
  }
  
  // 1. handle web portal
  portal.update();
  
  // 2. update the inputs
  if ( frequency.update() ) {
    midi.setClocksPerTrigger(map(frequency.getValue(), 0, NUM_FREQUENCY_BUTTONS, MIDI_CLOCKS_PER_BEAT/SCALE, MIDI_CLOCKS_PER_BEAT*SCALE));
    showFrequency(frequency.getValue());
  }
  if (portal.getOffset() != midiDelay) {
    // web portal has changed offset
    midiDelay = portal.getOffset();
    showOffset(midiDelay);
  }
  if (resetCounter.update() && resetCounter.getState()) {
    // reset button has just been pressed.  Reset the MIDI clock.
    midi.resetCounter();
  }

  if ( false ) {
    // have a change in duration
    showDuration(duration);
  }
  if ( false ) {
    // console has changed offset.  Override web portal settings
    midiDelay = offset;
    portal.setOffset(midiDelay);
    showOffset(midiDelay);
  }

  // 3. decode the MIDI situation
  // if there's no MIDI signal and we're not manually firing, shut it down.
  if( midi.getCounter()==255 && !makeFireNow.getState() ) {
    // shut it down
    fireLeft.off();
    fireRight.off();
  }  
  // if we have a MIDI update, a firing frequency, and we're not manually firing, do stuff.
  if( midi.update() && !makeFireNow.getState()) {

    // we have a MIDI signal to follow
    byte counter = midi.getCounter();

    byte midiClocksPerTrigger = midi.getClocksPerTrigger();

    // how far back from the poof do we need to trigger the hardware?
    byte fireOnAt = (midiClocksPerTrigger - midiDelay) % midiClocksPerTrigger;
    
    // and when do we need to turn it off?
    byte fireOffAt = (fireOnAt + duration) % midiClocksPerTrigger;

    // given the current counter and on/off times, should we shoot fire or not?
    if( frequency.hasSelection() && timeForFire( counter, fireOnAt, fireOffAt ) ) {
      // turn on the fire
      fireLeft.on();
      fireRight.on();
    } else {
      // turn off the the fire
      fireLeft.off();
      fireRight.off();
    }

    // report tick, noting we do this after the hardware-level update
    showMIDI(midi.getBeatCounter());
  }

  // 4. override with the Make Fire Now button
  if ( makeFireNow.update() ) {
    // have a change in the make fire now button
    // do the thing
    manualFiring(makeFireNow.getState());

    // report manual, noting we do this after the hardware-level update
    showMakeFireNow(makeFireNow.getState());
  }

  // 5. report firing status

  if ( fireLeft.update() ) {
    // have a change in solenoid status
    showFireLeft(fireLeft.getState());
  }
  if ( fireRight.update() ) {
    // have a change in solenoid status
    showFireRight(fireRight.getState());
  }

  // MISC. code for debugging, reporting, etc. to the Serial line

  // We need MIDI_CLOCKS_PER_BEAT updates per beat, so minimum updates per second is:
  static word updateFloor = MIDI_CLOCKS_PER_BEAT * 200 / 60;

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

// BOOOOSH!
void manualFiring(boolean doFire) {
  if ( doFire ) {
    fireLeft.on();
    fireRight.on();
  } else {
    fireLeft.off();
    fireRight.off();
  }
}

// the OLED display is hella-slow, so we want to be careful about how much we print there.
// much of this code is just being "smart" about updating the OLED.

void showFireLeft(boolean state) {
  // static boolean lastState = !state;
  // static boolean startup = true;
  // const byte thisRow = 7;

  // if ( startup ) {
  //   oled.buffer = "<. Synferno  .>";
  //   showLabel(thisRow);
  //   startup = false;
  // }
  // if ( lastState != state ) {
  //   lastState = state;
  //   if ( state ) {
  //     oled.buffer = "F";
  //   }
  //   else {
  //     oled.buffer = ".";
  //   }
  //   oled.write(thisRow, 1);
  // }
}

void showFireRight(boolean state) {
  // static boolean lastState = !state;
  // static boolean startup = true;
  // const byte thisRow = 7;

  // if ( startup ) {
  //   oled.buffer = "<. Synferno  .>";
  //   showLabel(thisRow);
  //   startup = false;
  // }
  // if ( lastState != state ) {
  //   lastState = state;
  //   if ( state ) {
  //     oled.buffer = "F";
  //   }
  //   else {
  //     oled.buffer = ".";
  //   }
  //   oled.write(thisRow, 13);
  // }
}

void showMakeFireNow(boolean state) {
  // static boolean lastState = !state;
  // static boolean startup = true;
  // const byte thisRow = 5;

  // if ( startup ) {
  //   oled.buffer = "MFN:  ";
  //   showLabel(thisRow);
  //   startup = false;
  // }
  // if ( lastState != state ) {
  //   lastState = state;
  //   if ( state ) {
  //     oled.buffer = "X";
  //   }
  //   else {
  //     oled.buffer = ".";
  //   }
  //   oled.write(thisRow, 6);
  // }
}

void showMIDI(byte count) {
  // static byte lastCount = 255;
  // static boolean startup = true;
  // const byte thisRow = 0;

  // if ( startup ) {
  //   oled.buffer = "MIDI: ";
  //   showLabel(thisRow);
  //   startup = false;
  // }

  // if ( lastCount != count ) {
  //   lastCount = count;
  //   if ( count == 0 ) {
  //     oled.buffer = "X";
  //     oled.write(thisRow, 6); // don't pad, place at a specific location
  //   }
  //   if ( count == 3 ) {
  //     oled.buffer = ".";
  //     oled.write(thisRow, 6); // don't pad, place at a specific location
  //   }
  // }
}

void showDuration(byte count) {
  // static byte lastCount = 255;
  // static boolean startup = true;
  // const byte thisRow = 1;

  // if ( startup ) {
  //   oled.buffer = "Dur:  ";
  //   showLabel(thisRow);
  //   startup = false;
  // }
  // if ( lastCount != count ) {
  //   lastCount = count;
  //   showCounter(thisRow, 6, count);
  // }
}

void showOffset(byte count) {
  // static byte lastCount = 255;
  // static boolean startup = true;
  // const byte thisRow = 2;

  // if ( startup ) {
  //   oled.buffer = "Off:  ";
  //   showLabel(thisRow);
  //   startup = false;
  // }
  // if ( lastCount != count ) {
  //   lastCount = count;
  //   showCounter(thisRow, 6, count);
  // }
}

void showFrequency(int step) {
  // static int lastStep = 0;
  // static boolean startup = true;
  // const byte thisRow = 3;

  // if ( startup ) {
  //   oled.buffer = "Freq: ";
  //   showLabel(thisRow);
  //   startup = false;
  // }
  // if ( lastStep != step ) {
  //   lastStep = step;
  //   showCounter(thisRow, 6, step);
  // }
}

void showOptions(byte count) {
  // static byte lastCount = 255;
  // static boolean startup = true;
  // const byte thisRow = 4;

  // if ( startup ) {
  //   oled.buffer = "Opts:  ";
  //   showLabel(thisRow);
  //   startup = false;
  // }
  // if ( lastCount != count ) {
  //   lastCount = count;
  //   showCounter(thisRow, 6, count);
  // }
}

void showLabel(byte row) {
  // oled.write(row, 0, true); // pad
}

void showCounter(byte row, byte col, int counter) {
  // oled.buffer = String(counter);
  // if ( oled.buffer.length() < 2 ) oled.buffer += " ";
  // oled.write(row, col); // don't pad, place at a specific location
}


