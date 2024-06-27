#include <Arduino.h>

// pins for KS0835F module interface
const byte L1_FR = 22;  // forward/reverse is toggled to produce ringing output, set low for other modes
const byte L1_RM = 19;  // set high while generating a ring output, low for other modes
const byte L1_SHK = 23; // switch hook input is high to indicate an off-hook condition, low for on-hook
const byte ringButton1 = 18;

const byte L2_FR = 25; //TEST
const byte L2_RM = 33;  //TEST
const byte L2_SHK = 32; //TEST
const byte ringButton2 = 13;  // button to generate a ring signal on the phone line

const int LED1 = 5;     // LED to indicate on/off hook
const int LED2 = 26;    // LED to indicate on/off hook
String digits;

bool debug1 = false;
bool debug2 = false;

#define LINE_1 "1"
#define LINE_2 "2"

const int numberOfLines = 2;
byte hookStatus[2] = {0, 0};


void myDialingStartedCallback(bool started);
void digitReceivedCallback(char digit);