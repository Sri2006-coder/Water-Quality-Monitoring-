# Water Quality Monitoring System 💧

An Arduino-based real-time Water Quality Monitoring system measuring **TDS (Total Dissolved Solids)** and **Water Temperature**, displaying readings and safety status on a 16x2 LCD screen with visual smiley indicators and an audible buzzer alert.

---

## 📌 Features

- **TDS Measurement**: Reads analog voltage from an analog TDS sensor, converts voltage to TDS values (ppm), and uses an exponential moving average (smoothing filter) for steady readings.
- **Water Temperature Monitoring**: Uses a waterproof DS18B20 digital temperature sensor (OneWire) for precise temperature measurement in Celsius.
- **16x2 LCD Display**: Displays live TDS and Temperature readings, along with custom 8-bit smiley faces:
  - 😃 **Happy Face**: Water parameters are within safe ranges.
  - 🙁 **Sad Face**: Parameter limits exceeded.
- **Buzzer Alert**: Beeps non-blockingly at 200ms intervals if water quality is poor.

---

## 🔔 Alert Thresholds

The alert buzzer and sad face trigger when:
- **TDS** is `< 50 ppm` or `> 500 ppm`
- **Temperature** is `< 15 °C` or `> 35 °C`

---

## 🔌 Pin Configuration

| Component | Pin / Bus | Arduino Pin |
|---|---|---|
| **TDS Sensor** | Analog Out (AOUT) | `A0` |
| **DS18B20 Temp Sensor** | Data Pin (OneWire) | `D2` (with 4.7kΩ pull-up to 5V) |
| **Buzzer** | Positive (+) | `D8` |
| **16x2 LCD** | RS, EN, D4, D5, D6, D7 | `12, 11, 5, 4, 3, 6` |

---

## 📦 Required Libraries

Install the following libraries via the Arduino Library Manager:
1. `LiquidCrystal` (Built-in)
2. `OneWire` by Paul Stoffregen
3. `DallasTemperature` by Miles Burton

---

## 🚀 How to Run

1. Open `Water_Quality_Monitoring.ino` in the Arduino IDE.
2. Select your board (e.g., Arduino Uno / Nano) and COM port under **Tools**.
3. Install the required libraries.
4. Click **Upload**.
