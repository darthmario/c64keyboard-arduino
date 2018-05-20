/*
  Copyright (c) 2014-2015 NicoHood
  See the readme for credit to other people.

  Serial HID-Bridge USB
  Select HoodLoader16u2 as board.

  After upload make sure the 16u2 sketch runs, not the HoodLoader2 bootloader.
  This example will type any serial data via keyboard.
*/

#include <HID-Project.h>
#include <HID-Settings.h>
const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data

boolean newData = false;


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
  // based on http://forum.arduino.cc/index.php?topic=396450.0
  recvWithEndMarker();
  showNewData();
}

void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  while (Serial1.available() > 0 && newData == false) {
    rc = Serial1.read();
    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    }
    else {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = true;
    }
  }
}

void showNewData() {
  if (newData == true) {
    Serial.print("This just in ... ");
    Serial.println(receivedChars);
    char *receivedCharsPtr = receivedChars + 1;
    byte *recievedKeycode = receivedCharsPtr +0;
    Keyboard.write(KeyboardKeycode(40));
    Serial.println(receivedCharsPtr);
    if (receivedChars[0] == 1) {
      char *receivedCharsPtr = receivedChars + 1;
      Serial.println("keypress");
      // keypress
    }
    if (receivedChars[0] == 3){
      Serial.println("release");
      // key release
    }
    newData = false;
  }
}


