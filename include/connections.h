#ifndef WEMPIR_CONNECTIONS_H_
#define WEMPIR_CONNECTIONS_H_

#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>

extern unsigned long lastMillis;

bool connect();
void reconnect();
void callback(char *topic, byte *payload, unsigned int length);
void handleWifi();

#endif // WEMPIR_CONNECTIONS_H_
