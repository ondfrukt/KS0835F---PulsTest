#include "RingSignal.h"

RingSignal::RingSignal(int shkPin, int rmPin, int f_rPin) {
  SHK = shkPin;
  RM = rmPin;
  F_R = f_rPin;
  pinMode(SHK, INPUT);
  pinMode(RM, OUTPUT);
  pinMode(F_R, OUTPUT);
}

void RingSignal::generate() {
  if (!digitalRead(SHK)) {
    Serial.println("Ringing phone...");
    digitalWrite(RM, HIGH);
    for (int i = 0; i < 10; i++) {
      digitalWrite(F_R, HIGH);
      delay(25);
      digitalWrite(F_R, LOW);
      delay(25);
    }
    digitalWrite(RM, LOW);
  }
}
