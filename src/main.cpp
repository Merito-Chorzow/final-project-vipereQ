#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  pinMode(19, INPUT_PULLUP);
}

void loop() {
  Serial.println(digitalRead(19));
  delay(500);
}
