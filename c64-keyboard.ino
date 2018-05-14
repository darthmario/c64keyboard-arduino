/*
 * This is to test the connection to the C64 keyboard.  It uses a standard 
 * arduino Uno board.  There is no USB connection here, just a way to ensure
 * That the keypad is reading the correct key based on the keypress and keyboard matrix
 * 
 */

#include <Key.h>
#include <Keypad.h>
#include "keyboard_definitions.h"

const byte ROWS = 8;
const byte COLS = 8;

char hexaKeys[ROWS][COLS] = {
  {KEY_1, '<', 'C', 'S', KEY_SPACEBAR, 'H', KEY_Q, KEY_2},
  {KEY_3, KEY_W, KEY_A, KEY_LEFT_SHIFT, KEY_Z, KEY_S, KEY_E, KEY_4},
  {KEY_5, KEY_R, KEY_D, KEY_X, KEY_C, KEY_F, KEY_T, KEY_6},
  {KEY_7, KEY_Y, KEY_G, KEY_V, KEY_B, KEY_H, KEY_U, KEY_8},
  {KEY_9, KEY_I, KEY_J, KEY_N, KEY_M, KEY_K, KEY_O, KEY_0},
  {'+', KEY_P, KEY_L, '\'', '.', ':', KEY_ATMARK, '-'},
  {'$', KEY_STAR, ';', '/', KEY_RIGHT_SHIFT, '=', '^', 'G'},
  {'D', 'R', '{', '}', KEY_F1, KEY_F3, KEY_F5, KEY_F7}
};

byte rowPins[ROWS] = {0, 4, 5, 6, 7, 8, 9, 10};
byte colPins[COLS] = {11, 12, 14, 15, 16, 17, 18, 19};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(2000000);
}

// we should probably rework this to be able to handle multiple keys and possibly events for 
// press, release etc.  As well we'll have to modify the keys to get all the keys required for 
// use of a normal pc.

void loop() {
  byte customKey = customKeypad.getKey();

  if (customKey) {
    //Serial.write(customKey);
    Serial.print(customKey);
  }
}
