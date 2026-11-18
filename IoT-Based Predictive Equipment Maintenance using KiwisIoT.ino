#include <ESP8266WiFi.h>
#include <KiwisIoT.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <math.h>

// WiFi Credentials
const char* ssid = "YOUR_WIFI_NAME";
const char* pass = "YOUR_WIFI_PASSWORD";

// KiwisIoT Topic ID
const char* topic = "YOUR_TOPIC_ID";

// Temperature Sensor
#define TEMP_PIN D4

// DS18B20
OneWire oneWire(TEMP_PIN);
DallasTemperature tempSensor(&oneWire);

// ADXL345
Adafruit_ADXL345_Unified accel =
  Adafruit_ADXL345_Unified(12345);

// KiwisIoT
KiwisIoT kiwisiot(ssid, pass, topic);

// Monitoring Interval
unsigned long previousMillis = 0;

// Example Warning Thresholds
const float TEMP_LIMIT = 60.0;
const float VIBRATION_LIMIT = 2.0;

void setup() {

  Serial.begin(115200);

  Wire.begin(D2, D1);

  tempSensor.begin();

  if (!accel.begin()) {

    Serial.println("ADXL345 Not Found!");

    while (true) {
      delay(1000);
    }
  }

  accel.setRange(ADXL345_RANGE_16_G);

  kiwisiot.begin();

  Serial.println("Predictive Equipment Monitoring Started");
}

void loop() {

  kiwisiot.run();

  if (millis() - previousMillis >= 3000) {

    previousMillis = millis();

    // Read Temperature
    tempSensor.requestTemperatures();

    float temperature =
      tempSensor.getTempCByIndex(0);

    // Read Accelerometer
    sensors_event_t event;

    accel.getEvent(&event);

    float x = event.acceleration.x;
    float y = event.acceleration.y;
    float z = event.acceleration.z;

    // Calculate Acceleration Magnitude
    float magnitude =
      sqrt(x * x + y * y + z * z);

    // Remove Approximate Gravity Component
    float vibration =
      fabs(magnitude - 9.81);

    // Equipment Condition
    String equipmentStatus = "NORMAL";

    if (vibration > VIBRATION_LIMIT ||
        (temperature != DEVICE_DISCONNECTED_C &&
         temperature > TEMP_LIMIT)) {

      equipmentStatus = "WARNING";
    }

    Serial.println("\n--- EQUIPMENT HEALTH ---");

    if (temperature != DEVICE_DISCONNECTED_C) {

      Serial.print("Temperature: ");
      Serial.print(temperature);
      Serial.println(" C");

      kiwisiot.send("0", String(temperature, 2));

    } else {

      Serial.println("Temperature Sensor Error");

    }

    Serial.print("Vibration: ");
    Serial.print(vibration);
    Serial.println(" m/s2");

    Serial.print("Equipment Status: ");
    Serial.println(equipmentStatus);

    // Send Information to KiwisIoT
    kiwisiot.send("1", String(vibration, 2));

    kiwisiot.send("2", equipmentStatus);

  }
}