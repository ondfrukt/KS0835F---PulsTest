#include <Arduino.h>
#include "config.h"

// Target Hardware:  Uno, SLIC breakout board
// https://github.com/GadgetReboot/DTMF_Decoder
// https://github.com/GadgetReboot/KS0835F_Phone_SLIC
//
// KS0835F pin        Uno Pin
//   F_R                 7
//   RM                  8
//   SHK                 9
//
//  Ring push button     10
//
// When the ring button is pressed, if the phone is on-hook (required for ringing a phone),
// a 20 Hz ring signal is generated.

// pins for KS0835F module interface
const byte F_R = 7;   // forward/reverse is toggled to produce ringing output, set low for other modes
const byte  RM = 8;   // set high while generating a ring output, low for other modes
const byte SHK = 9;   // switch hook input is high to indicate an off-hook condition, low for on-hook
const byte ringButton = 10;  // button to generate a ring signal on the phone line
const byte LED = 6; // LED to indicate on/off hook

byte hookStatus = 1;  // track whether phone is on or off hook (0=off-hook 1=on-hook)
bool lastDebounceValue = 0;
unsigned long lastDebounceTime;








void PulsHandler(int SHK){
  bool newSHK = digitalRead(SHK);
  if(newSHK != lastDebounceValue)
    lastDebounceValue = newSHK;
    lastDebounceTime = millis();
}




void setup() {
  Serial.begin(9600);

  // configure KS0835F pins
  pinMode(F_R, OUTPUT);
  pinMode(RM, OUTPUT);
  pinMode(SHK, INPUT);
  pinMode(LED, OUTPUT);

  pinMode(ringButton, INPUT_PULLUP);  // button to ring the phone

  Serial.println();
  Serial.println("KS0835F SLIC and MT8870 DTMF Decoder Demo");
  
  if (!digitalRead(SHK)) {
    Serial.println("Phone is ON hook...");
    hookStatus = 0;
  } else {
    Serial.println("Phone is OFF hook...");
    hookStatus = 1;
  }
  Serial.println();

}

// generate a test ring signal
void generateRingSignal() {
  // check if phone is on-hook before ringing, then generate a short ring at 20 Hz
  // this should be implemented better, maybe with interrupts so that as soon as the
  // phone is picked up, ring generation stops but this is ok for testing
  if (!digitalRead(SHK)) {
    Serial.println("Ringing phone...");
    digitalWrite(RM, HIGH);         // enable ring mode
    for (int i = 0; i < 10; i++) {
      digitalWrite(F_R, HIGH);      // toggle fwd/rev pin to generate ring
      delay(25);  // 25 mS = half of 20 Hz period
      digitalWrite(F_R, LOW);
      delay(25);  // 25 mS = half of 20 Hz period
    }
    digitalWrite(RM, LOW);          // disable ring mode
  }
}

void loop() {

  // ensure module is configured so KS0835F control pins
  // are set for non ringing standby mode at the start of each loop
  digitalWrite(F_R, LOW);  // set forward/reverse pin low for all modes except ringing
  digitalWrite(RM, LOW);   // set ring mode pin low for all modes except ringing

  // check if phone hook status has changed (just picked up or placed back on-hook)
  byte reading = digitalRead(SHK);
  if (reading != hookStatus) {
    if (hookStatus == 0) {
      Serial.println("Phone is OFF hook...");
      digitalWrite(LED, HIGH);
    } 
    else {
      Serial.println("Phone is ON hook...");
      digitalWrite(LED, LOW);
    }
    hookStatus = reading;
    delay(20);  // crude and vile "debounce" delay because KS0835F hook signal needs debouncing
  }

  // generate a short ring signal if button is pressed
  if (!digitalRead(ringButton)) {
    generateRingSignal();
  }
}