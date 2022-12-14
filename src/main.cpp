#include <Arduino.h>

#define PIR_PIN 16

bool newStat = false;
bool oldStat = false;

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
}

void loop() {
  if (digitalRead(PIR_PIN)) {
    newStat = true;
  } else {
    newStat = false;
  }
  if (newStat != oldStat) {
    oldStat = newStat;
    Serial.print(newStat);
    Serial.print(" - ");
    Serial.println(millis() / 1000);
  }
  delay(25);
}