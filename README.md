# 💧 Water Quality Monitoring System

An ESP32-based IoT system for monitoring water quality in real time using **TDS, Turbidity, and Temperature sensors**. The collected data is displayed locally on a 16×2 I2C LCD and remotely monitored using the **Blynk IoT platform**.

## 🚀 Features

- 🌡️ Real-time water temperature monitoring
- 💧 TDS (Total Dissolved Solids) measurement
- 🌫️ Turbidity measurement
- 📊 Water clarity classification
- 📟 16×2 I2C LCD display
- 📱 Real-time monitoring through Blynk
- 📋 CSV-format data logging through Serial Monitor
- 📡 Wi-Fi connectivity using ESP32

## 🛠️ Hardware Used

- ESP32 Development Board
- TDS Sensor
- Turbidity Sensor
- DS18B20 Temperature Sensor
- 16×2 I2C LCD
- Jumper Wires
- Breadboard
- USB Cable
- Power Supply

## 🔌 Pin Connections

| Component | ESP32 Pin |
|-----------|-----------|
| TDS Sensor | GPIO 34 |
| Turbidity Sensor | GPIO 35 |
| DS18B20 | GPIO 4 |
| I2C LCD SDA | Default I2C SDA |
| I2C LCD SCL | Default I2C SCL |

## 📊 Parameters Monitored

### TDS

The TDS sensor measures the approximate concentration of dissolved solids in the water.

The reading is calculated from the analog voltage received from the TDS sensor.

### Turbidity

The turbidity sensor measures the clarity of the water.

The system classifies the water as:

- **Clear**
- **Cloudy**
- **Very Cloudy**
- **Invalid**

### Temperature

The DS18B20 sensor measures water temperature in degrees Celsius.

## 📱 Blynk Integration

The ESP32 sends sensor readings to the Blynk dashboard using virtual pins.

| Blynk Virtual Pin | Data |
|-------------------|------|
| V0 | TDS |
| V1 | Turbidity |
| V2 | Temperature |
| V4 | Water Clarity Status |

## ⏱️ Data Update Intervals

| Function | Interval |
|----------|----------|
| TDS Reading | 1 second |
| Turbidity Reading | 1.5 seconds |
| Temperature Reading | 2 seconds |
| CSV Logging | 3 seconds |

## 📋 Serial Data Logging

The system outputs sensor readings in CSV format through the Serial Monitor at **115200 baud**.

Example:

```text
Time(ms),Temperature(C),Turbidity,TDS
3000,27.50,42,105.32
6000,27.56,43,106.10
9000,27.62,44,107.21
