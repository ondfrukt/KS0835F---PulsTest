#include <Arduino.h>
#ifndef PULSE_HANDLER_H
#define PULSE_HANDLER_H

class PulseHandler {
  private:
    bool dialing;
    bool pulsing;
    byte pulses;
    bool lastDebounceValue;
    unsigned long lastDebounceTime;
    unsigned long edge;
    const unsigned pulseGapMin = 10;
    const unsigned pulseGapMax = 100;

  public:
      PulseHandler() {
      void handlePulse(int SHK);
    }

    void handlePulse(int SHK) {
      bool newSHK = SHK;
      if(newSHK != lastDebounceValue)
        Serial.println("newSHK != lastDebounceValue");
        lastDebounceValue = newSHK;
        lastDebounceTime = millis();
        return;

      if((millis() - lastDebounceTime) < pulseGapMin) return;
      Serial.println("Test!");
      unsigned gap = edge ? millis() - edge : 0;
      Serial.println(gap);
      if(newSHK && SHK && gap <= pulseGapMax) return;         // SHK high and unchanged, skip until long gap between digits
      if(!newSHK && !SHK) return;                             // SHK low and unchanged, skip always
      SHK = newSHK;

      // falling edge
      if(!SHK && !pulsing) {
        pulsing = true;
        edge = millis();
        Serial.println("falling edge");
        return;
      }

      // rising edge
      if(SHK && pulsing){
        pulsing = false;
        pulses++;
        edge = millis();
        Serial.println("rising edge");
        if(!dialing){ 
          // NOTE: callback on rising edge because falling edge occurs when user hangs up and causes a brief "pulse dialing" mode change
          dialing = true;
        }
        return;
      }

      // gap between digits
      if(SHK && !pulsing && gap > pulseGapMax){
        char digit = String(pulses % 10)[0];
        pulsing = false;
        pulses = 0;
        edge = 0;
        Serial.println(digit);
        return;
      }
    }
};

#endif