#include "USBComposite.h"

USBMIDI midi;

const int buttonCount = 16;
int buttonPins[buttonCount] = {PB11, PB10, PB1, PB0, PA7, PA6, PA5, PA4,
  PA3, PA2, PA1, PA0, PC15, PC14, PB12, PB13};
int ledPin = PC13;

unsigned long lastDebounceTimes[buttonCount] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int buttonStates[buttonCount] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,
  HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
  
const unsigned long debounceDelay = 50;

void setup() {
  for (int i = 0; i < buttonCount; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  
  USBComposite.setProductId(0x0031);
  midi.begin();
  while (!USBComposite);
}

void loop() {
  unsigned long curTime = millis();
  
  for (int buttonNum = 0; buttonNum < buttonCount; buttonNum++) {
    bool newButtonState = digitalRead(buttonPins[buttonNum]);

    if ((curTime - lastDebounceTimes[buttonNum]) > debounceDelay) {
      if (newButtonState != buttonStates[buttonNum]) {
        lastDebounceTimes[buttonNum] = curTime;
        
        if (newButtonState == LOW) {
          midi.sendNoteOn(0, 36 + buttonNum, 127);
        } else {
          midi.sendNoteOff(0, 36 + buttonNum, 127);
        }
      }
    }
    
    buttonStates[buttonNum] = newButtonState;
  }
}
