#include <BleKeyboard.h>

BleKeyboard bleKeyboard("Steering Wheel", "Remedie Motorsports", 100);

struct PK {
  uint8_t pin; // Pin
  uint8_t key; // Key to send, see https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/
} pk[] = {
  { D2, 'Y' },
  { D3, 'N' },
  { D4, KEY_LEFT_ARROW },
  { D7, KEY_RIGHT_ARROW },
};

int pkSize = sizeof pk / sizeof pk[0];
uint8_t s = 0;

void setup() {
  Serial.begin(115200);

  for (int j = 0; j < pkSize; j++) {
    pinMode(pk[j].pin, INPUT_PULLDOWN);
  }
  
  bleKeyboard.begin();
}

void loop() {
  delay(10);

  for (int i = 0; i < pkSize; i++) {
    PK k = pk[i];
    int p = (s & (1 << i)) > 0;
    int p2 = digitalRead(k.pin);
    
    if (p != p2) {
      s ^= (1 << i);
  
      if (p2) {
        Serial.print("Button on pin ");
        Serial.print(k.pin);
        Serial.print(" pressed, sending ");
        Serial.println((char)k.key);
 
        if(bleKeyboard.isConnected()) {
          bleKeyboard.write(k.key);
        }
      }
    }
  }
}
