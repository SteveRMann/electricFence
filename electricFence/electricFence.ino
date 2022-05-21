#define SKETCH "electricFence.ino"
#include <Ticker.h>
#include <dlay.h>                     //Future, change to blockNot.h

#define LEDOFF 0
#define LEDON 1

Ticker redTicker;                    //Ticker object to blink the warning LED
dlay  hvTimer;

const int warningLedPin = D1;
const int hvPin = D2;
const int pulseWidth = 10;
const int pulsePeriod = 800;        //Time between pulses

void redTick() {
  int state = digitalRead(warningLedPin);            //get the current state of warningLedPin
  digitalWrite(warningLedPin, !state);               //set pin to the opposite state
}

void hv() {
  //Send a short pulse to the hvPin
  hvTimer.stop();                             //Stop the timer
  digitalWrite(hvPin, 1);
  delay(pulseWidth);
  digitalWrite(hvPin, 0);
  hvTimer.setTime(pulsePeriod);               //Reset the timer
  hvTimer.start();
  Serial.println(F("Zap"));
}

//---------- setup() ----------
void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println(); Serial.println();
  Serial.println(F(SKETCH));
  Serial.println();

  pinMode(warningLedPin, OUTPUT);
  pinMode(hvPin, OUTPUT);
  digitalWrite(hvPin, 0);

  redTicker.attach(0.4, redTick);        //start redTick()

  hvTimer.setTime(pulsePeriod);          //Time between pulses
  hvTimer.start();
}


//---------- loop() ----------
void loop() {
  if (hvTimer.ding()) {
    hv();
  }
}
