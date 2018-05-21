/*
 * This is to test the connection to the C64 keyboard.  It uses a standard 
 * arduino Uno board.  There is no USB connection here, just a way to ensure
 * That the keypad is reading the correct key based on the keypress and keyboard matrix
 * 
 */

#include <Key.h>
#include <Keypad.h>

const byte ROWS = 8;
const byte COLS = 8;

char hexaKeys[ROWS][COLS] = {
  {'1', '<', 'C', 'S', ' ', 'H', 'q', '2'},
  {'3', 'w', 'a', '[', 'z', 's', 'e', '4'},
  {'5', 'r', 'd', 'x', 'c', 'f', 't', '6'},
  {'7', 'y', 'g', 'v', 'b', 'h', 'u', '8'},
  {'9', 'i', 'j', 'n', 'm', 'k', 'o', '0'},
  {'+', 'p', 'l', '\'', '.', ':', '@', '-'},
  {'$', '*', ';', '/', ']', '=', '^', 'H'},
  {'D', 'R', '{', '}', '!', '#', '%', '&'}
};

byte rowPins[ROWS] = {0, 4, 5, 6, 7, 8, 9, 10};
byte colPins[COLS] = {11, 12, 14, 15, 16, 17, 18, 19};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(2000000);
}

void loop() {
  char customKey = customKeypad.getKey();

  if (customKey) {
    Serial.print(customKey);
  }
}
