#ifndef pulser_h
#define pulser_h
#include "Arduino.h"

class pulseHandler {
  public:
    pulseHandler(unsigned pinSHK);
    void setDigitCallback(void (*digitReceivedCallback)(char));
    void start();
    void run();

  private:
    unsigned long lastPulseTime;
    unsigned long minPulseInterval;
    bool hookStatus;
    unsigned PIN;
    bool SHK;
    bool dialing;
    bool pulsing;
    byte pulses;
    bool lastDebounceValue;
    unsigned long lastDebounceTime;
    unsigned long edge;
    const unsigned pulseGapMin = 10;
    const unsigned pulseGapMax = 60;  //probably should be same as SHK debounceDelay in progressModes.h
    const unsigned pulsingMaxTime = 200;
    void (*digitReceivedCallback)(char);
};

#endif