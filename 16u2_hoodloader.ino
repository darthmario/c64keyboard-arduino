/*
 * This requires your arduino to be using the Hoodloader2 bootloader so you 
 * can program the 16u2 to act as a hid device.
 * 
 * This will listen to messages coming over serial from the MCU and then pass them via usb.
 * 
 * This should be loaded onto the HoodLoader16u2 device and not the Uno. 
 */


#include "Keyboard.h"
#include "HID.h"

void setup() {
  // Start the Serial1 which is connected with the IO MCU.
  // Make sure both baud rates are the same
  // you can go up to 2000000 for very fast data transmission.
  Serial1.begin(115200);

  // Sends a clean report to the host. This is important on any Arduino type.
  Keyboard.begin();

  // Start the USB Serial for debugging
  Serial.begin(115200);
}

void loop() {
  // Check if any Serial data from the IO MCU was received
  char c = Serial1.read();

  // If it's a character, print it!
  //if (c >= 'a' && c <= 'z') {
    Serial.print(F("USB: "));
    Serial.print(c);
    Keyboard.print(c);
  //}
}
