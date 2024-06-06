#include "PhoneLineHandler.h"

// Konstruktor
LineHandler::LineHandler() {
  _lineNumber = 0;
  _shkPin = 0;
  _rmPin = 0;
  _frPin = 0;
  _hookStatus = false;
}
// Funktioner för att sätta och hämta data
void LineHandler::setLineNumber(int lineNumber) {
  _lineNumber = lineNumber;
}
int LineHandler::getLineNumber() {
  return _lineNumber;
}
void LineHandler::setSHK_Pin(int shkPin) {
  _shkPin = shkPin;
}
int LineHandler::getSHK_Pin() {
  return _shkPin;
}
void LineHandler::setRM_Pin(int rmPin) {
  _rmPin = rmPin;
}
int LineHandler::getRM_Pin() {
  return _rmPin;
}
void LineHandler::setFR_Pin(int frPin) {
  _frPin = frPin;
}
int LineHandler::getFR_Pin() {
  return _frPin;
}
void LineHandler::setHookStatus(bool hookStatus) {
  _hookStatus = hookStatus;
}
bool LineHandler::getHookStatus() {
  return _hookStatus;
}
