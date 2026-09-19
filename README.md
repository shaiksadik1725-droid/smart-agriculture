# Smart Agriculture Monitoring & Control System

A distributed IoT agriculture project that monitors environmental and soil conditions, controls actuators, communicates between field nodes using LoRa, and forwards data to a cloud dashboard.

## Overview

The project uses multiple embedded boards to monitor different agricultural zones. Sensor nodes measure soil moisture, pH, temperature, humidity, probe temperature, and water level. Local control logic operates pumps, fans, thermoelectric devices, indicators, and alarms.

LoRa is used for long-range node communication, while an ESP32 gateway forwards received information to Blynk.

## Main Features

- Multi-node agriculture monitoring
- Soil moisture sensing
- pH monitoring
- Temperature and humidity monitoring
- Water-level monitoring
- Automatic pump control
- Fan control
- Thermoelectric heating/cooling logic
- LED and buzzer alerts
- LoRa wireless communication
- ESP32 gateway
- Blynk dashboard integration

## Architecture

```text
Field Node 1 ─┐
              ├── LoRa ──> Gateway / MCU ──> ESP32 ──> Blynk
Field Node 2 ─┘
```

## Technology Stack

### Hardware
- ESP32
- LoRa modules
- DHT22
- Soil-moisture sensor
- pH sensor
- Water-level sensor
- Temperature probe
- Relays
- Pumps / fan
- LEDs and buzzer

### Software
- Arduino / C++
- Blynk
- LoRa libraries
- Fritzing
- draw.io

## Project Structure

```text
smart-agriculture/
├── codes/
│   ├── board1/
│   ├── board2/
│   ├── esp/
│   └── mkr/
├── BOARD1.fzz
├── Block Diagram.drawio
├── FLOWCHART.drawio
├── RECEIVER_FLOW.drawio
└── smart_agriculture.docx
```

## Security Configuration

Wi-Fi credentials and Blynk tokens are intentionally represented by placeholders in the public source. Add your own credentials locally before deployment and do not commit real secrets.

## Future Improvements

- Move secrets to a dedicated local configuration file
- Add soil and weather forecasting
- Add MQTT and local data storage
- Add OTA firmware updates
- Add solar/battery power monitoring
- Add automated testing for gateway parsing

## Author

**Sadik Shaik**

Computer Engineering / AI & Embedded Systems Projects
