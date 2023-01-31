#include "connections.h"

#define HOSTNAME "WemPIR"
#define MQTT_IP "10.0.0.7"
#define MQTT_PORT 1883
#define MQTT_TOPIC ""

unsigned long lastMillis = -60000;

WiFiClient espClient;
PubSubClient client(espClient);

bool connect() {
    if (!client.connect(HOSTNAME)) {
        // Serial.print("failed, rc=");
        // Serial.println(client.state());
        // Serial.println("Not Connected to MQTT-Broker");
        return false;
    }
    lastMillis = 0;
    return true;
    // Serial.println("Connected to MQTT-Broker");
    // client.publish("stat/diyHall/POWER", "off");
    // client.subscribe("cmnd/diyHall/POWER");
}

void reconnect() {
    if (!client.connected()) {
        if (lastMillis == 0) {
            lastMillis = millis();
        }
        unsigned long currentMillis = millis();
        if ((unsigned long)(currentMillis - lastMillis) >= 60000) {
            connect();
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

void setupWifi() {
    client.setServer(MQTT_IP, MQTT_PORT);
    client.setCallback(callback);
    ArduinoOTA.setHostname(HOSTNAME);
    ArduinoOTA.begin();
}

void handleWifi() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
    ArduinoOTA.handle();
}