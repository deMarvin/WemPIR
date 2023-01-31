// #include <Arduino.h>
// #include <ESP8266WiFi.h>
#include <WiFiManager.h>

#include "connections.h"

#define PIR_PIN 16

void setup() {
    Serial.begin(115200);
    pinMode(PIR_PIN, INPUT);
}

void loop() {
    if (digitalRead(PIR_PIN)) {
        Serial.println("movement");
    }
    delay(25);
}