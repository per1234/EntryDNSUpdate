

/*
    EntryDnsUpdate example sketch

    This example demonstrates how to use
    EntryDnsUpdate class to update an entry at entrydns.net.
    
    Created by Kristian Berg, 2016.
    This example is in public domain.
*/

#include <ESP8266WiFi.h>
#include "EntryDNSUpdate.h"

EntryDNSUpdate entryDNS("7s3WuKQlbWVKjSKcjsj8");
const char *ssid = "SL102";
const char *password = "trygve95kasper00";

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  entryDNS.update();
}

