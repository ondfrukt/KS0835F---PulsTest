#include <Arduino.h>
#include "config.h"
#include <RingSignal.h>
#include <pulseHandler.h>
#include <phoneHookHandler.h>

RingSignal ringLine[numberOfLines] = {
  RingSignal(L1_SHK, L1_RM, L1_FR),
  RingSignal(L2_SHK, L2_RM, L2_FR)};

pulseHandler pulser[numberOfLines] = {
  pulseHandler(L1_SHK),
  pulseHandler(L2_SHK)};

phoneHookStatus HookStatus[numberOfLines] = {
  phoneHookStatus(LINE_1, L1_SHK, LED1),
  phoneHookStatus(LINE_2, L2_SHK, LED2)};

void setup() {
  //debug_init();
  Serial.begin(9600);
  // configure KS0835F pins
  pinMode(L1_FR, OUTPUT);
  pinMode(L1_RM, OUTPUT);
  pinMode(L1_SHK, INPUT);
  pinMode(ringButton1, INPUT_PULLUP);  // button to ring the phone 1

  pinMode(L2_FR, OUTPUT);
  pinMode(L2_RM, OUTPUT);
  pinMode(L2_SHK, INPUT);
  pinMode(ringButton2, INPUT_PULLUP);  // button to ring the phone 2

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  
  Serial.println();
  Serial.println("KS0835F SLIC Demo");

  for (int i = 0; i < numberOfLines; i++){
    pulser[i].setDigitCallback(digitReceivedCallback);
    pulser[i].start();
    Serial.println("pulser Started");
  }
}

void loop() {
  digitalWrite(L1_FR, LOW);  // set forward/reverse pin low for all modes except ringing
  digitalWrite(L1_RM, LOW);   // set ring mode pin low for all modes except ringing
  
  // generate a short ring signal if button is pressed
  if (!digitalRead(ringButton1)) {
    ringLine[0].generate();
  }
  if (!digitalRead(ringButton2)) {
    ringLine[1].generate();
  }
  
  for (int i = 0; i < numberOfLines; i++) {

      if (HookStatus[i].hookStatus() == 1) {
        pulser[i].run();
      }
  }

  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == '1') {
      debug1 = debug1 ^ true; // toggle debug value
    }else if (command == '2') {
      debug2 = debug2 ^ true;
    }
  }
  if (debug1 == true){
    Serial.print("L1_SHK: "); Serial.print(digitalRead(L1_SHK)); 
    Serial.print(" | L2_SHK: "); Serial.println(digitalRead(L2_SHK));
  }
  if (debug2 == true){
    HookStatus[0].printHookStatus();
    Serial.print(" | ");
    HookStatus[1].printHookStatus();
    Serial.println();
  }
  delay(10);
}

// Callback-funktion för när uppringningen startar
void myDialingStartedCallback(bool started) {
    if (started) {
        Serial.println("Dialing started!");
    } else {
        Serial.println("Dialing stopped!");
    }
}

void digitReceivedCallback(char digit){
  Serial.print(digit);    // debug output show digits as they are received
  digits += digit;          // accumulate the digit
  auto dlen = digits.length();
}