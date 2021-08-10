#define SKETCH "electricFence.ino"
#include <BlockNot.h>
#include <Ticker.h>
#include <dlay.h>                     //Future, change to blockNot.h

#define LEDOFF 1
#define LEDON 0

Ticker redTicker;                    //Ticker object to blink the warning LED
dlay  hvTimer;

const int warningLedPin = D1;
const int hvPin = D2;

void redTick() {
  int state = digitalRead(warningLedPin);            //get the current state of warningLedPin
  digitalWrite(warningLedPin, !state);               //set pin to the opposite state
}

void hv(){
  //Send a short pulse to the hvPin
  digitalWrite(hvPin, 1);
  delay(100);
  digitalWrite(hvPin, 0);
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

  redTicker.attach(0.5, redTick);        //start redTick() with a fast blink while we connect

  hvTimer.setTime(1000);                  //Time between pulses
  hvTimer.start();
}


//---------- loop() ----------
void loop() {
  if (hvTimer.ding()){
    hv();
  }
}
