
// Compile for Sparkfun ESP32 Thing

// Sparkfun ESP32 Thing: https://cdn.sparkfun.com/assets/learn_tutorials/5/0/7/esp32-thing-graphical-datasheet-v02.png
// Adafruit Monochrome 1.3" 128x64 OLED graphic display SSD1306: https://www.adafruit.com/product/938
// MIDI Breakout Board: https://smile.amazon.com/gp/product/B00YDLVLVO
// IRF520 MOSFET Driver Module: https://smile.amazon.com/gp/product/B06XHH1TQM
// 12V / 5V DC Buck Converter: https://smile.amazon.com/gp/product/B01MEESLZ6
// 12V 10A Power Supply: https://smile.amazon.com/gp/product/B00Z9X4GLW

// 21 to OLED `Data`
// 22 to OLED `Clk`
// 16 to MIDI `tx`
// 17 to MIDI `rx`
// 13 to left solenoid MOSFET Driver Module `SIG`
// VUSB to Buck Converter `+5`
// 10k ohm resister between 39 and +3.3
// 10k ohm resister between 38 and +3.3
// 10k ohm resister between 37 and +3.3
// 10k ohm resister between 36 and +3.3
// 10k ohm resister between 35 and +3.3
// 10k ohm resister between 34 and +3.3


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

// Frequency buttons
#include "ButtonGroup.h"
#define NUM_FREQUENCY_BUTTONS 5
byte FREQUENCY_BUTTON_PINS[NUM_FREQUENCY_BUTTONS] = {35, 36, 37, 38, 39};
byte FREQUENCY_LED_PINS[NUM_FREQUENCY_BUTTONS] = {14, 27, 26, 25, 33};
ButtonGroup frequency;

// Web Portal
#include "Portal.h"

// Menu
#include <menu.h>
#include <Ticker.h>
Ticker updateEncoder;
//#define ENC_DECODER ENC_FLAKY
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
#define fontName u8g2_font_7x13_mf
#define fontX 7
#define fontY 16
#define offsetX 0
#define offsetY 3
#define U8_Width 128
#define U8_Height 64
#define USE_HWI2C
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);//, SCL, SDA);
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


