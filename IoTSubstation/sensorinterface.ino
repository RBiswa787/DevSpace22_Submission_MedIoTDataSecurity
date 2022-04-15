#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#define REPORTING_PERIOD_MS     1000
SoftwareSerial espSerial(2,3);
#define USE_ARDUINO_INTERRUPTS true    
PulseOximeter pox;

uint32_t tsLastReport = 0;
int hr = 0;
float spo2 = 0;

void onBeatDetected() {
    Serial.println("Beat!");
}

void setup() {
    Serial.begin(9600);
    espSerial.begin(9600);
    Serial.print("Initializing pulse oximeter..");

    // Initialize sensor
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }

  // Configure sensor to use 7.6mA for LED drive
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

    // Register a callback routine
    pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
    // Read from the sensor
    pox.update();

    // Grab the updated heart rate and SpO2 levels
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print("Heart rate:");
        hr = pox.getHeartRate();
        Serial.print(hr);
        Serial.print("bpm / SpO2:");
        spo2 = pox.getSpO2();
        Serial.print(spo2);
        Serial.println("%");
        StaticJsonDocument<1000> jsonBuffer;
        JsonObject data = jsonBuffer.to<JsonObject>();
        data["heart_rate"] = hr;
        data["spo2"] = spo2;
        serializeJson(data, espSerial);
        jsonBuffer.clear();
        //temp = 0;
        delay(1000);
        tsLastReport = millis();
    }
}