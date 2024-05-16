#include <Arduino.h>

// pins for KS0835F module interface
const byte F_R = 7;   // forward/reverse is toggled to produce ringing output, set low for other modes
const byte  RM = 8;   // set high while generating a ring output, low for other modes
const byte SHK = 9;   // switch hook input is high to indicate an off-hook condition, low for on-hook
const byte ringButton = 10;  // button to generate a ring signal on the phone line
const byte LED = 6; // LED to indicate on/off hook


unsigned long edge;
unsigned long lastDebounceTime;
bool lastDebounceValue;
bool pulsing;
byte pulses;