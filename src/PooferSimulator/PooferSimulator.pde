/**
 * Read a string from an Arduino serial line which describes the state
 * of each of the 4 poofer channels as a 0 or 1.
 * Illuminate a bar for each of the channels when they are lit, simulating a Poof.
 */


import processing.serial.*;
import processing.sound.*;

Serial inPort;  // Create object from Serial class
int lf = 10;    // Linefeed in ASCII
String inString = null;      // Data received from the serial port
boolean[] states = new boolean[4];
SoundFile[] poofSounds = new SoundFile[4];

void setup() 
{
  fullScreen();
  
  // List all the available serial ports
  printArray(Serial.list());
  // Open a port
  inPort = new Serial(this, Serial.list()[2], 9600);
  inPort.clear();
  // Throw out the first reading, in case we started reading 
  // in the middle of a string from the sender.
  inString = inPort.readStringUntil(lf);
  inString = null;
  
  poofSounds[0] = new SoundFile(this, "poofer.wav");
  poofSounds[1] = new SoundFile(this, "poofer.wav");
  poofSounds[2] = new SoundFile(this, "poofer.wav");
  poofSounds[3] = new SoundFile(this, "poofer.wav");
}

void draw()
{
  if ( inPort.available() > 0) {  // If data is available,
    inString = inPort.readStringUntil(lf);
    
    if (inString != null && inString.length() == 6) {      
      // assume inString is a valid 4 character string of '0's and/or '1's
      background(255);             // Set background to white
      
      tickPoofer(inString.charAt(0) == '1', 0);
      tickPoofer(inString.charAt(1) == '1', 1);
      tickPoofer(inString.charAt(2) == '1', 2);
      tickPoofer(inString.charAt(3) == '1', 3);
      inPort.clear();
    }
  }
}


void tickPoofer(boolean firing, int x) {
  // update state
  boolean changed = (states[x] != firing);
  states[x] = firing;
  
  // lowest possible effort: fill a red bar
  if (firing) {
    fill(color(255,50,50));
  } else {
    fill(0);
  }
  rect(x * width / 4, 0, width/4, height);
  
  // start a poof sound, or play the poofer ending if poofer state changed
  if (changed) {
    if (firing) {
      poofSounds[x].cue(0);
      poofSounds[x].play();
    } else {
      poofSounds[x].jump(3.8);
    }
  }
}
