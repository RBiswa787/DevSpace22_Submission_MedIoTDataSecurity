#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

void setup() 
{
        Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  StaticJsonDocument<1000> data;
  deserializeJson(data, Serial);
  float heart_rate = data["TDS"];
  float spo2 = data["pH"];
  String payload = "{";
  payload += "\"Heart Rate\":";payload += heart_rate;payload += ",";
  payload += "\"SpO2\":";payload += spo2;
  payload += "}";
  char attributes[1000];
  payload.toCharArray( attributes, 1000 );
  Serial.println( attributes );
  delay(1000);
}