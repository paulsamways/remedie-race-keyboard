#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

int keyMap[3][2] = {
  { D2,   D3,  }, // Pin
  { 0,    0,   }, // Previous state (high/low)
  { 'Y',  'N', }  // Key to send, see https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/
};

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 2; i++) {
    pinMode(keyMap[0][i], INPUT);
  }
  
  bleKeyboard.begin();
}

void loop() {
  delay(10);

  for (int i = 0; i < 2; i++) {

    int p = keyMap[0][i];
    int previousState = keyMap[1][i];
    int keyCode = keyMap[2][i];
    
    int newState = digitalRead(p);
    
    if (previousState != newState) {
      keyMap[1][i] = newState;
  
      if (newState == 1) {
        Serial.print("Button on pin ");
        Serial.print(p);
        Serial.print(" pressed, sending ");
        Serial.println((char)keyCode);
 
        if(bleKeyboard.isConnected()) {
          bleKeyboard.write(keyCode);
        }
      }
    }
  }
}
