#include <Arduino.h>
#include "config.h"
#include <RingSignal.h>
#include <pulseHandler.h>

byte hookStatus = 1;  // track whether phone is on or off hook (0=off-hook 1=on-hook)

RingSignal ringSignal(SHK, RM, F_R);


// Callback-funktion för när uppringningen startar
void myDialingStartedCallback(bool started) {
    if (started) {
        Serial.println("Dialing started!");
    } else {
        Serial.println("Dialing stopped!");
    }
}

// Callback-funktion för när en siffra tas emot
void myDigitReceivedCallback(char digit) {
    Serial.print("Received digit: ");
    Serial.println(digit);
}

void myMaybeDialingStartedCallback() {
    Serial.println("Maybe dialing started!");
}

pulseHandler myPulseHandler(SHK, myDialingStartedCallback);


void setup() {
  Serial.begin(9600);
  // configure KS0835F pins
  pinMode(F_R, OUTPUT);
  pinMode(RM, OUTPUT);
  pinMode(SHK, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(ringButton, INPUT_PULLUP);  // button to ring the phone

  Serial.println();
  Serial.println("KS0835F SLIC Demo");
  Serial.print("Phone Script starts with hook ");
  if (!digitalRead(SHK)) {
    Serial.println("ON");
    hookStatus = 0;
    digitalWrite(LED, LOW);
  } else {
    Serial.println("OFF");
    hookStatus = 1;
    digitalWrite(LED, HIGH);
  }
  Serial.println();


  // Ange callback-funktioner för pulseHandler-instansen
  myPulseHandler.setDigitCallback(myDigitReceivedCallback);
  myPulseHandler.setMaybeCallback(myMaybeDialingStartedCallback);

  // Starta pulseHandler
  myPulseHandler.start();



}

void loop() {
  
  // ensure module is configured so KS0835F control pins
  // are set for non ringing standby mode at the start of each loop
  digitalWrite(F_R, LOW);  // set forward/reverse pin low for all modes except ringing
  digitalWrite(RM, LOW);   // set ring mode pin low for all modes except ringing

  

  // check if phone hook status has changed (just picked up or placed back on-hook)
  byte reading = digitalRead(SHK);
  //Serial.println(reading);
  if (reading != hookStatus) {
    unsigned long elapsedTime = millis() - lastChangeTime;
    lastChangeTime = millis();
    if (hookStatus == 0) {
      digitalWrite(LED, HIGH);
     } 
    if (hookStatus == 1){
      digitalWrite(LED, LOW);
      }
    hookStatus = reading;
  }
  else
  if (hookStatus){
    myPulseHandler.run();
  }

  // generate a short ring signal if button is pressed
  if (!digitalRead(ringButton)) {
    ringSignal.generate();
  }
}