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

//S=RUN STOP
//$=puound
//^=UP Arrow (ascii up)
//}= UP DOWN (cursor movement)
//{=Left Right (cursor movement)
//<=ascii left
char hexaKeys[ROWS][COLS] = {
  {KEY_1, '<', KEY_LEFTCONTROL, 'S', KEY_SPACEBAR, KEY_COMMODORE, KEY_Q, KEY_2},
  {KEY_3, KEY_W, KEY_A, KEY_LEFT_SHIFT, KEY_Z, KEY_S, KEY_E, KEY_4},
  {KEY_5, KEY_R, KEY_D, KEY_X, KEY_C, KEY_F, KEY_T, KEY_6},
  {KEY_7, KEY_Y, KEY_G, KEY_V, KEY_B, KEY_H, KEY_U, KEY_8},
  {KEY_9, KEY_I, KEY_J, KEY_N, KEY_M, KEY_K, KEY_O, KEY_0},
  {KEY_PLUS, KEY_P, KEY_L, KEY_COMMA, KEY_PERIOD, KEY_COLON, KEY_ATMARK, KEY_MINUS},
  {'$', KEY_STAR, KEY_SEMICOLON, KEY_FORWARD_SLASH, KEY_RIGHT_SHIFT, KEY_EQUALS, '^', KEY_HOME},
  {KEY_DELETE, KEY_RETURN, '{', '}', KEY_F1, KEY_F3, KEY_F5, KEY_F7}
};

byte rowPins[ROWS] = {0, 4, 5, 6, 7, 8, 9, 10};
byte colPins[COLS] = {11, 12, 14, 15, 16, 17, 18, 19};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
String msg;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(2000000);
}

// we should probably rework this to be able to handle multiple keys and possibly events for
// press, release etc.  As well we'll have to modify the keys to get all the keys required for
// use of a normal pc.

void loop() {
  //byte customKey = customKeypad.getKey();
  String msg;

  /*if (customKey) {
    Serial.print(customKey);
    //Serial.write(customKey);
    }*/

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
            msg = "PRES";
            break;
          case HOLD:
            msg = "HOLD";
            break;
          case RELEASED:
            msg = "RELE";
            break;
          case IDLE:
            msg = "IDLE";
        }
        if (msg == "PRES" || msg == "RELE" ) {
          // Get USB keycode from the list
          byte keymatrix = customKeypad.key[i].kcode;
          byte keymatrixrow = floor(customKeypad.key[i].kcode / 8);
          byte keymatrixcol = customKeypad.key[i].kcode - (keymatrixrow * 8);
          byte customKey = hexaKeys[keymatrixrow][keymatrixcol];
          String keyreturn = "";
          keyreturn = String(msg + customKey);
          Serial.print(keyreturn);
          Serial.print(" or ");
          Serial.println(msg);
        }
      }
    }
  }
}
