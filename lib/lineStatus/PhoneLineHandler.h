#ifndef PhoneLineHandler
#define PhoneLineHandler
#include "Arduino.h"

#define ON_HOOK 0x01 // 00000001
#define DIALING 0x02 // 00000010
#define CALLING 0x04 // 00000100

class LineHandler {
  public:
    // Konstruktor
    LineHandler();

    // Funktioner för att sätta och hämta data
    void setLineNumber(int lineNumber);
    int getLineNumber();

    void setSHK_Pin(int shkPin);
    int getSHK_Pin();

    void setRM_Pin(int rmPin);
    int getRM_Pin();

    void setFR_Pin(int frPin);
    int getFR_Pin();

    void setHookStatus(bool hookStatus);
    bool getHookStatus();

  private:
    // Variabler för att lagra data
    int _lineNumber;
    int _shkPin;
    int _rmPin;
    int _frPin;
    bool _hookStatus;
};

#endif