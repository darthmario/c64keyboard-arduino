/*
   This is to test the connection to the C64 keyboard.  It uses a standard
   arduino Uno board.  There is no USB connection here, just a way to ensure
   That the keypad is reading the correct key based on the keypress and keyboard matrix

*/

#include <Key.h>
#include <Keypad.h>
#include "keyboard_definitions.h"

const byte ROWS = 8;
const byte COLS = 8;

char hexaKeys[ROWS][COLS] = {
  {KEY_1, KEY_LEFT_ARROW, KEY_LEFTCONTROL, KEY_EXECUTE, KEY_SPACEBAR, KEY_COMMODORE, KEY_Q, KEY_2},
  {KEY_3, KEY_W, KEY_A, KEY_LEFT_SHIFT, KEY_Z, KEY_S, KEY_E, KEY_4},
  {KEY_5, KEY_R, KEY_D, KEY_X, KEY_C, KEY_F, KEY_T, KEY_6},
  {KEY_7, KEY_Y, KEY_G, KEY_V, KEY_B, KEY_H, KEY_U, KEY_8},
  {KEY_9, KEY_I, KEY_J, KEY_N, KEY_M, KEY_K, KEY_O, KEY_0},
  {KEY_PLUS, KEY_P, KEY_L, KEY_COMMA, KEY_PERIOD, KEY_COLON, KEY_ATMARK, KEY_MINUS},
  {KEY_POUND, KEY_STAR, KEY_SEMICOLON, KEY_FORWARD_SLASH, KEY_RIGHT_SHIFT, KEY_EQUALS, KEY_UP_ARROW, KEY_HOME},
  {KEY_DELETE, KEY_RETURN, KEY_RIGHT_LEFT, KEY_DOWN_UP, KEY_F1, KEY_F3, KEY_F5, KEY_F7}
};

byte rowPins[ROWS] = {0, 4, 5, 6, 7, 8, 9, 10};
byte colPins[COLS] = {11, 12, 14, 15, 16, 17, 18, 19};
byte msg;
byte keymatrix;
byte keymatrixrow;
byte keymatrixcol;
byte customKey;
char keyreturn[4];
char keyreturn2[4];

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // Fills kpd.key[ ] array with up-to 10 active keys.
  // Returns true if there are ANY active keys.
  if (customKeypad.getKeys())
  {
    for (int i = 0; i < LIST_MAX; i++) // Scan the whole key list.
    {
      if ( customKeypad.key[i].stateChanged )   // Only find keys that have changed state.
      {
        switch (customKeypad.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
          case PRESSED:
            msg = 1;
            break;
          case HOLD:
            msg = 2;
            break;
          case RELEASED:
            msg = 3;
            break;
          case IDLE:
            msg = 4;
        }
        if (msg == 1 || msg == 3 ) {
          // Get USB keycode from the list
          keymatrix = customKeypad.key[i].kcode;
          keymatrixrow = floor(keymatrix / 8);
          keymatrixcol = keymatrix - (keymatrixrow * 8);
          customKey = hexaKeys[keymatrixrow][keymatrixcol];
          // we're going to force pressing 2 and shift to fake this
          if (customKey == KEY_ATMARK ) {
            sprintf(keyreturn, "%i%i", msg, KEY_RIGHT_SHIFT);
            Serial.println(keyreturn);
            sprintf(keyreturn2, "%i%i", msg, KEY_2);
            Serial.println(keyreturn2);
          } else if (customKey == KEY_COLON ) {
            sprintf(keyreturn, "%i%i", msg, KEY_RIGHT_SHIFT);
            Serial.println(keyreturn);
            sprintf(keyreturn2, "%i%i", msg, KEY_SEMICOLON);
            Serial.println(keyreturn2);
          } else {
            sprintf(keyreturn, "%i%i", msg, customKey);
            Serial.println(keyreturn);
          }

/* Mocking up what we need to track with the keyboard.
We need to track state of 
CLRL
LSHIFT
RSHIFT
Commodore Key

Keys that need special behavior
2
6
7
8
9
Home
DEL
:
;
CRSRup
crsrleft




        }
      }
    }
  }
}
