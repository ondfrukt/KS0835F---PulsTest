#include <Arduino.h>
#include "config.h"
#include <RingSignal.h>

byte hookStatus = 1;  // track whether phone is on or off hook (0=off-hook 1=on-hook)

RingSignal ringSignal(SHK, RM, F_R);

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
  } else {
    Serial.println("OFF");
    hookStatus = 1;
  }
  Serial.println();
}

void loop() {
  
  // ensure module is configured so KS0835F control pins
  // are set for non ringing standby mode at the start of each loop
  digitalWrite(F_R, LOW);  // set forward/reverse pin low for all modes except ringing
  digitalWrite(RM, LOW);   // set ring mode pin low for all modes except ringing

  // check if phone hook status has changed (just picked up or placed back on-hook)
  byte reading = digitalRead(SHK);
  if (reading != hookStatus && !pulsing) {
    if (hookStatus == 0) {
      digitalWrite(LED, HIGH);
      
    } 
    else {
      digitalWrite(LED, LOW);
    }
    hookStatus = reading;
    delay(20);
  }

  // generate a short ring signal if button is pressed
  if (!digitalRead(ringButton)) {
    ringSignal.generate();
  }
}