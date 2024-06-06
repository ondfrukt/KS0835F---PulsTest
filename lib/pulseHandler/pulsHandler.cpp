#include "pulseHandler.h"

pulseHandler::pulseHandler(unsigned pinSHK) {
  PIN = pinSHK;
}

void pulseHandler::setDigitCallback(void (*callback)(char)) {
  digitReceivedCallback = callback;
}

void pulseHandler::start(){
  dialing = false;
  pulsing = false;
  pulses = 0;
  edge = 0;
  lastDebounceTime = millis();
  lastDebounceValue = digitalRead(PIN);
}

void pulseHandler::run(){
  bool newSHK = digitalRead(PIN);
  
  //Debug: Print current state
  // Serial.print("lastDebounceValue: "); Serial.print(lastDebounceValue);
  // Serial.print(" newSHK: "); Serial.print(newSHK);
  // Serial.print(" SHK: "); Serial.print(SHK);
  // Serial.print(" pulses: "); Serial.print(pulses);
  // Serial.print(" pulsing: "); Serial.print(pulsing);
  // Serial.print(" edge: "); Serial.println(edge);


  // debounce because SHK from SLIC is very noisy
  if(newSHK != lastDebounceValue) {
    lastDebounceValue = newSHK;
    lastDebounceTime = millis();
    return;
  }
  
  if((millis() - lastDebounceTime) < pulseGapMin) return;

  unsigned gap = edge ? millis() - edge : 0;
  //Serial.print("gap: "); Serial.println(gap);
  if(newSHK && SHK && gap <= pulseGapMax) return; // SHK high and unchanged, skip until long gap between digits
  if(!newSHK && !SHK) return;                     // SHK low and unchanged, skip always
  
  SHK = newSHK;

  // falling edge
  if(!SHK && !pulsing) {
    pulsing = true;
    edge = millis();
    return;
  }

  // rising edge
  if(SHK && pulsing){
    pulsing = false;
    pulses++;
    edge = millis();
    if(!dialing){ 
      // NOTE: callback on rising edge because falling edge occurs when user hangs up and causes a brief "pulse dialing" mode change
      dialing = true;
    }
    return;
  }

  // gap between digits
  if(SHK && !pulsing && gap > pulseGapMax){
    pulses = pulses - 1;  // Subtract 1 from pulses to get the correct digit
    char digit = String(pulses % 10)[0];  // Convert number to character
    pulsing = false;
    pulses = 0;
    edge = 0;
    digitReceivedCallback(digit);
    return;
  }
}
