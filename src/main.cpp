#include <Arduino.h>
#include <BleKeyboard.h>

BleKeyboard keyboard;
uint8_t playKeyDown = 0;
uint8_t prevKeyDown = 0;

void setup() {
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  digitalWrite(18, LOW);
  digitalWrite(19, LOW);

  Serial.begin(115200);
  Serial.println("Starting.");

  pinMode(8, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);

  keyboard.begin();
}

void loop() {
  if (keyboard.isConnected()) {
    digitalWrite(19, HIGH);

    if (!digitalRead(8) != playKeyDown) {
      playKeyDown = !playKeyDown;
      if (playKeyDown) {
        keyboard.press(KEY_MEDIA_PLAY_PAUSE);
        Serial.println("Pressed play/pause.");
      } else {
        keyboard.release(KEY_MEDIA_PLAY_PAUSE);
        Serial.println("Released play/pause.");
      }
    }

    if (!digitalRead(6) != prevKeyDown) {
      prevKeyDown = !prevKeyDown;
      if (prevKeyDown) {
        keyboard.press(KEY_MEDIA_PREVIOUS_TRACK);
        Serial.println("Pressed previous track.");
      } else {
        keyboard.release(KEY_MEDIA_PREVIOUS_TRACK);
        Serial.println("Released previous track.");
      }
    }

  } else {
    digitalWrite(19, LOW);
  }
}
