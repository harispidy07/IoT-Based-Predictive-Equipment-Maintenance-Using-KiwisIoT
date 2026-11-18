# IoT-Based Predictive Equipment Maintenance Using KiwisIoT

## Project Overview

This project monitors equipment health using an ESP8266 NodeMCU, DS18B20 temperature sensor, and ADXL345 accelerometer. It measures equipment temperature and vibration levels to identify abnormal operating conditions and generate warning alerts through the KiwisIoT platform.

## Hardware Components

- ESP8266 NodeMCU
- DS18B20 Temperature Sensor
- ADXL345 Accelerometer
- Jumper Wires
- Power Supply
- Equipment / Motor for Monitoring

## Software Requirements

- Arduino IDE
- ESP8266 Board Package
- KiwisIoT Arduino Library
- Adafruit Sensor Library
- Adafruit ADXL345 Library
- OneWire Library
- DallasTemperature Library

## Circuit Connections

| Component    | ESP8266 Pin |
| ------------ | ----------- |
| DS18B20 Data | D4          |
| ADXL345 SDA  | D2          |
| ADXL345 SCL  | D1          |
| ADXL345 VCC  | 3.3V        |
| ADXL345 GND  | GND         |

Connect the DS18B20 data line with an appropriate pull-up resistor. The ADXL345 communicates with the ESP8266 through the I2C interface.

## Working Principle

The DS18B20 measures equipment temperature, while the ADXL345 detects acceleration and vibration. The ESP8266 calculates vibration magnitude and compares the readings against predefined warning thresholds.

If the temperature exceeds 60°C or vibration exceeds 2.0 m/s², the equipment status changes to WARNING. Sensor readings and equipment status are transmitted to KiwisIoT every 3 seconds for remote monitoring.

## KiwisIoT Dashboard

| Channel   | Data                                |
| --------- | ----------------------------------- |
| Channel 0 | Equipment Temperature (°C)          |
| Channel 1 | Vibration Level (m/s²)              |
| Channel 2 | Equipment Status (NORMAL / WARNING) |

**Note:** The vibration value is calculated from acceleration magnitude after approximate gravity compensation. The warning thresholds are example values and should be calibrated according to the equipment and operating conditions.

## Configuration

Update your Wi-Fi credentials and KiwisIoT Topic ID in the code:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* pass = "YOUR_WIFI_PASSWORD";
const char* topic = "YOUR_TOPIC_ID";
```

Upload the code to the NodeMCU ESP8266 and monitor equipment health through the KiwisIoT dashboard.

## Applications

- Industrial equipment monitoring
- Motor health monitoring
- Predictive maintenance systems
- Machinery temperature monitoring
- Vibration-based fault detection
- Industrial IoT automation

## Project Reference

**Hackster.io Project:**  
[https://www.hackster.io/harispidy07/iot-based-predictive-equipment-maintenance-using-kiwisiot-73b2c7](https://www.hackster.io/harispidy07/iot-based-predictive-equipment-maintenance-using-kiwisiot-73b2c7)

**KiwisIoT Platform:**  
[https://kiwisiot.com/](https://kiwisiot.com/)

**KiwisIoT GitHub Repository:**  
[https://github.com/Kiwistron/KiwisIoT-Projects](https://github.com/Kiwistron/KiwisIoT-Projects)

## Author

**Hariprasath S**

GitHub: [https://github.com/harispidy07](https://github.com/harispidy07)

---

_Built using ESP8266, DS18B20, ADXL345, and KiwisIoT for intelligent equipment health monitoring._
