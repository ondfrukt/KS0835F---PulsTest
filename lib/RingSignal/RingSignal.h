#ifndef RingSignal_h
#define RingSignal_h

#include "Arduino.h"

class RingSignal {
  public:
    RingSignal(int shkPin, int rmPin, int f_rPin);
    void generate();

  private:
    int SHK;
    int RM;
    int F_R;
};

#endif
