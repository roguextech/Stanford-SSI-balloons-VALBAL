/*
  Stanford Student Space Initiative
  Balloons | VALBAL | September 2017
  Davy Ragland | dragland@stanford.edu
  Claire Huang | chuang20@stanford.edu

  File: Hardware.cpp
  --------------------------
  Implimentation of Hardware.h
*/

#include "Hardware.h"

/**********************************  SETUP  ***********************************/
/*
 * Function: init
 * -------------------
 * This function initializes the PCB hardware.
 */
void Hardware::init() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  analogReference(INTERNAL);
  analogReadResolution(12);
  wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);
  wire.setDefaultTimeout(5000);
}

/********************************  FUNCTIONS  *********************************/
/*
 * Function: runLED
 * -------------------
 * This function turns the LED on or off.
 */
void Hardware::runLED(bool on) {
  digitalWrite(LED_PIN, !on);
}

/*
 * Function: EEPROMReadlong
 * -------------------
 * This function reads an int32_t from the given address.
 */
int32_t Hardware::EEPROMReadlong(uint8_t address) {
  int32_t four = EEPROM.read(address);
  int32_t three = EEPROM.read(address + 1);
  int32_t two = EEPROM.read(address + 2);
  int32_t one = EEPROM.read(address + 3);
  return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}

/*
 * Function: EEPROMWritelong
 * -------------------
 * This function writes an int32_t to the given address.
 */
void Hardware::EEPROMWritelong(uint8_t address, int32_t value) {
  uint8_t four = (value & 0xFF);
  uint8_t three = ((value >> 8) & 0xFF);
  uint8_t two = ((value >> 16) & 0xFF);
  uint8_t one = ((value >> 24) & 0xFF);
  EEPROM.write(address, four);
  EEPROM.write(address + 1, three);
  EEPROM.write(address + 2, two);
  EEPROM.write(address + 3, one);
}
