//these pins can not be changed 2/3 are special pins
int encoderPin1 = 32;
int encoderPin2 = 4;
int encoderSwitchPin = 0; //push button switch

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

long lastRead = 0;

int lastMSB = 0;
int lastLSB = 0;
long val = 0;

void setup() {
Serial.begin (115200);

pinMode(encoderPin1, INPUT_PULLUP);
pinMode(encoderPin2, INPUT_PULLUP);

pinMode(encoderSwitchPin, INPUT_PULLUP);

//call updateEncoder() when any high/low changed seen
//on interrupt 0 (pin 2), or interrupt 1 (pin 3)
attachInterrupt(encoderPin1, updateEncoder, CHANGE);
attachInterrupt(encoderPin2, updateEncoder, CHANGE);
lastRead = millis();

}

void loop(){

 if (millis() > (lastRead + 30UL) &&  
  (abs(encoderValue - lastencoderValue) >= 4)
  ) {
  if (encoderValue > lastencoderValue) {
    val++;
  } else {
    val--;
  }
  lastRead = millis();
  lastencoderValue = encoderValue;
  Serial.println(val);
 }
  //delay(1000); //just here to slow down the output, and show it will work even during a delay
}

void updateEncoder(){
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit
  
  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum = (lastEncoded << 2) | encoded; //adding it to the previous encoded value
  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;
  lastEncoded = encoded; //store this value for next time
}
