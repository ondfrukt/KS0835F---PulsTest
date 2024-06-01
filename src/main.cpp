#include <Arduino.h>
#include "config.h"
#include <RingSignal.h>
#include <pulseHandler.h>
//#include "avr8-stub.h"

byte hookStatus = 1;  // track whether phone is on or off hook (0=off-hook 1=on-hook)
RingSignal ringSignal(SHK, RM, F_R);
String digits;

// Callback-funktion för när uppringningen startar
void myDialingStartedCallback(bool started) {
    if (started) {
        Serial.println("Dialing started!");
    } else {
        Serial.println("Dialing stopped!");
    }
}

// Callback-funktion för när en siffra tas emot

void myMaybeDialingStartedCallback() {
    Serial.println("Maybe dialing started!");
}

pulseHandler myPulseHandler(SHK, myDialingStartedCallback);


void digitReceivedCallback(char digit){

  Serial.print(digit);      // debug output show digits as they are received
  digits += digit;          // accumulate the digit

  auto dlen = digits.length();

  // convert 22 to * for pulse dialing alternate star-code
  if(dlen > 1 && digits.substring(0, 2) == "22") digits = String("*") + digits.substring(2);

  auto d0 = digits[0];
  auto d1 = digits[1];

  if(dlen == 1 && d0 == '0') return;

  if(d0 == '*'){
    if(d1 == '5' && dlen < 4) return; // need 4 digits for menu 5
    if(dlen < 3) return;              // need 3 digits for all other menus
 
  }

}




void setup() {
  //debug_init();
  Serial.begin(9600);
  // configure KS0835F pins
  pinMode(F_R, OUTPUT);
  pinMode(RM, OUTPUT);
  pinMode(SHK, INPUT);
  pinMode(led, OUTPUT);
  pinMode(ringButton, INPUT_PULLUP);  // button to ring the phone

  Serial.println();
  Serial.println("KS0835F SLIC Demo");
  Serial.print("Phone Script starts with hook ");
  if (!digitalRead(SHK)) {
    Serial.println("ON");
    hookStatus = 0;
    digitalWrite(led, LOW);
  } else {
    Serial.println("OFF");
    hookStatus = 1;
    digitalWrite(led, HIGH);
  }
  Serial.println();


  // Ange callback-funktioner för pulseHandler-instansen
  myPulseHandler.setDigitCallback(digitReceivedCallback);
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
 //   unsigned long elapsedTime = millis() - lastChangeTime;
    lastChangeTime = millis();
    if (hookStatus == 0) {
      digitalWrite(led, HIGH);
     } 
    if (hookStatus == 1){
      digitalWrite(led, LOW);
      }
    hookStatus = reading;
  }

  // generate a short ring signal if button is pressed
  if (!digitalRead(ringButton)) {
    ringSignal.generate();
  }
  myPulseHandler.run();
}