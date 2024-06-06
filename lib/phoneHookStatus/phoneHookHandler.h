#ifndef phoneHookHandler
#define phoneHookHandler
#include <Arduino.h>

class phoneHookStatus {
    public:
        phoneHookStatus(const char* line, byte SHK_pin, int LED_PIN);
        byte hookStatus();
        void printHookStatus();
    private:
        unsigned long debounceDelay;
        unsigned long lastDebounceTime;
        byte lastReading;
        byte SHK;
        byte hook;
        String line;
        int LED;
};
#endif