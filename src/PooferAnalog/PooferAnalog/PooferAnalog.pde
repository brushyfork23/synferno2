/**
 * Read a string from an Arduino serial line which describes the state
 * of each of the 4 poofer channels as a 0 or 1.
 * Illuminate a bar for each of the channels when they are lit, simulating a Poof.
 */


import processing.serial.*;

Serial myPort;  // Create object from Serial class
int lf = 10;    // Linefeed in ASCII
String inString = null;      // Data received from the serial port

void setup() 
{
  size(200, 200);
  
  printArray(Serial.list());
  String portName = Serial.list()[1];
  myPort = new Serial(this, portName, 9600);
  
  // Throw out the first reading, in case we started reading 
  // in the middle of a string from the sender.
  inString = myPort.readStringUntil(lf);
  inString = null;
}

void draw()
{
  if ( myPort.available() > 0) {  // If data is available,
    inString = myPort.readStringUntil(lf);
    println(inString);
    if (inString != null && inString.length() == 4) {
      // assume inString is a valid 4 character string of '0's and/or '1's
      background(255);             // Set background to white
      drawPoofer(inString.charAt(0) == '1', 0);
      drawPoofer(inString.charAt(1) == '1', 50);
      drawPoofer(inString.charAt(2) == '1', 100);
      drawPoofer(inString.charAt(3) == '1', 150);
    }
  }
}


void drawPoofer(boolean firing, int x) {
  if (firing) {
    fill(color(255,0,0));
  } else {
    fill(0);
  }
  rect(x, 0, 50, 200);
}
