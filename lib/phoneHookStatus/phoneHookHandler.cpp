#include "Arduino.h"
#include "phoneHookHandler.h"

phoneHookStatus::phoneHookStatus(const char* phoneLine, byte SHK_PIN, int LED_PIN){
  SHK = SHK_PIN;
  LED = LED_PIN;
  line = phoneLine;
  pinMode(SHK, INPUT);
  pinMode(LED, OUTPUT);
  hook = 0;
  lastReading = hook;

  // Separat debouncing-fördröjning för varje instans
  debounceDelay = 100; // Kan anpassas efter behov
  lastDebounceTime = millis();
}

byte phoneHookStatus::hookStatus() {
  byte reading = digitalRead(SHK); // Läs SHK

  if (reading != lastReading) {
    // Uppdatera senaste tidpunkten då statusen ändrades
    lastDebounceTime = millis();
  }

  // Kontrollera om tillräckligt med tid har passerat för att undvika debouncing-effekter
  if ((millis() - lastDebounceTime) > debounceDelay) {      
      
      // Uppdatera statusen om den är stabil under debouncing-fördröjningen
      if (reading != hook) {
        hook = reading;
        if (hook == LOW){
          digitalWrite(LED, LOW);  // Luren är av
        } else{
          digitalWrite(LED, HIGH); // Luren är på
        }
      }
    }
  lastReading = reading; // Uppdatera senaste läsningen
  return hook; // Returnera den debouncade statusen
}

void phoneHookStatus::printHookStatus() {
  Serial.print("hook"); Serial.print(line); Serial.print(" status: "); Serial.print(int(hook));
}
