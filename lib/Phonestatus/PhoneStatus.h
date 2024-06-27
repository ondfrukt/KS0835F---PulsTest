// PhoneStatus.h
#ifndef PHONESTATUS_H
#define PHONESTATUS_H

#include <Arduino.h>

class PhoneStatus {
  public:
    // Status codes
    static const byte RINGING = 0x01;
    static const byte BUSY = 0x02;
    static const byte WAITING = 0x04;
    static const byte DISCONNECTED = 0x08;

    PhoneStatus(); // Constructor
    void setPhoneStatus(int phone, byte status); // Sets the status of a phone
    byte getPhoneStatus(int phone); // Gets the status of a phone
    void printPhoneStatus(int phone); // Prints the status of a phone

  private:
    unsigned int phoneStatus; // Variable to hold all phone statuses (16 bits)
};

#endif
