/*
  EntryDNSUpdate.cpp - Library for updating dynamic DNS entry at entrydns.net
  Created by Kristian Berg, October 24, 2016.
  Released into the public domain.
*/


#include "arduino.h"
#include <WiFiClientSecure.h>
#include "EntryDNSUpdate.h"

EntryDNSUpdate::EntryDNSUpdate(String _token, unsigned long _updateFrequencySeconds): token(_token), updateFrequencySeconds(_updateFrequencySeconds) {
}

void EntryDNSUpdate::update() {
  unsigned long now = millis();
  if(lastUpdated == 0 || (lastUpdated + updateFrequencySeconds * 1000) < now){
    doUpdate();
    lastUpdated = now;
  }
}

void EntryDNSUpdate::doUpdate() {

  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  if (client.verify(fingerprint, host)) {
    Serial.println("certificate matches");
  } else {
    Serial.println("certificate doesn't match");
  }

  String url = "/records/modify/" + token;
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: EntryDNSUpdateESP8266\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("request sent");
  Serial.println("status:");
  bool ok = false;
  if (client.connected()) {

    String firstLine = client.readStringUntil('\n');
    Serial.println(firstLine);
    if (firstLine.startsWith("200 OK", 9)) {
      ok = true;
    }

    Serial.println("headers:");
    String line;
    do {
      line = client.readStringUntil('\n');
      Serial.println(line);
    } while (line != "\r");
    Serial.println("headers received");
  }
  String line = client.readStringUntil('\r\n');
  Serial.println(line);
  int length = (int) strtol( line.c_str(), NULL, 16);
  uint8_t body[length];
  client.read(body, length);
  if (ok) {
    Serial.println("EntryDNS updated successfully");
  } else {
    Serial.println("EntryDNS update failed");
  }
  Serial.println("body:");
  Serial.println("==========");
  Serial.println(String((const char*)body).substring(0,length));
  Serial.println("==========");
  Serial.println("closing connection");
}


