// #include <Arduino.h>
#include <ArduinoOTA.h>
// #include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiManager.h>

#define PIR_PIN 16

#define HOSTNAME "WemPIR"
#define MQTT_IP "10.0.0.7"
#define MQTT_PORT 1883
#define MQTT_TOPIC ""

uint64_t lastMillis = -60000;

WiFiClient espClient;
PubSubClient client(espClient);

void reconnect() {
  if (!client.connected()) {
    if (lastMillis == 0) {
      lastMillis = millis();
    }
    unsigned long currentMillis = millis();
    if ((unsigned long)(currentMillis - lastMillis) >= 60000) {
      if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        // Serial.println("Connection Failed!");
      }
      if (client.connect(HOSTNAME)) {
        // Serial.println("Connected to MQTT-Broker");
        client.publish("stat/diyHall/POWER", "off");
        client.subscribe("cmnd/diyHall/POWER");
      } else {
        // Serial.print("failed, rc=");
        // Serial.println(client.state());
        // Serial.println("Not Connected to MQTT-Broker");
        lastMillis = 0;
      }
    }
  }
}

void callback(char *topic, byte *payload, unsigned int length) {
  String msg = "";
  // Serial.print(topic);
  for (uint16_t i = 0; i < length; i++) {
    msg = msg + (char)payload[i];
  }
  // Serial.println(" " + msg);
  if (strcmp(topic, "cmnd/diyHall/POWER") == 0) {
    if (msg.equalsIgnoreCase("on") || msg.equalsIgnoreCase("true")) {
    } else if (msg.equalsIgnoreCase("reboot")) {
      ESP.restart();
    } else {
    }
  }
}

void handleWifi() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  ArduinoOTA.handle();
}

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