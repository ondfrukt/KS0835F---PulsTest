// PhoneStatus.cpp
#include "PhoneStatus.h"

// Constructor
PhoneStatus::PhoneStatus() {
    phoneStatus = 0; // Initialize all statuses to off (16 bits)
}

// Sets the status of a specific phone
void PhoneStatus::setPhoneStatus(int phone, byte status) {
    if (phone < 0 || phone > 7) return; // Validate phone number (0 to 7)
    phoneStatus &= ~(0x03 << (phone * 2)); // Clear the bits for the phone
    phoneStatus |= (status << (phone * 2)); // Set new status bits
}

// Gets the status of a specific phone
byte PhoneStatus::getPhoneStatus(int phone) {
    if (phone < 0 || phone > 7) return 0; // Validate phone number (0 to 7)
    return (phoneStatus >> (phone * 2)) & 0x03;
}

// Prints the status of a specific phone
void PhoneStatus::printPhoneStatus(int phone) {
    byte status = getPhoneStatus(phone);
    
    Serial.print("Phone ");
    Serial.print(phone + 1);
    Serial.print(" status: ");
    
    switch (status) {
        case RINGING:
            Serial.println("Ringing");
            break;
        case BUSY:
            Serial.println("Busy");
            break;
        case WAITING:
            Serial.println("Waiting");
            break;
        case DISCONNECTED:
            Serial.println("Disconnected");
            break;
        default:
            Serial.println("Unknown");
    }
}
