# Secure Plant Monitor

Secure Plant Monitor is an IoT project designed to monitor environmental conditions such as temperature, humidity, light levels, and the presence of open flames. It focuses on the **security** of the system. It **securely transmits this data** using **MQTT** with **TLS encryption**, ensuring **data integrity** and **privacy**.

## Features

- **Environmental Monitoring**: Continuously measures temperature, humidity, and light levels for the plant health.
- **Flame Detection**: Alerts when an open flame is detected with a buzzer sounding an alarm.
- **Secure Data Transmission**: Utilizes MQTT protocol with TLS encryption to send data securely.

## Hardware Requirements

- **Microcontroller**: Compatible with Arduino IDE (e.g., ESP8266, ESP32).
- **Sensors**:
  - Temperature and Humidity Sensor (e.g., DHT11, DHT22)
  - Light Sensor (e.g., LDR)
  - Flame Sensor
  - Buzzer (that can play a sound of 1kHz)
- **Network**: Wi-Fi connectivity for MQTT communication.
- **MQTT Server**: To subscribe to the sensor topics.

## Software Requirements

- **IDE**: For programming the microcontroller.
- **Python 3.x**: For running the MQTT listener script.
- **MQTT Broker**: Supports TLS encryption (e.g., Mosquitto).

## Setup Instructions

1. **Hardware Setup**:

   - Connect the sensors to the microcontroller according to their specifications.
   - Ensure proper power supply and connections.

2. **Microcontroller Configuration**:

   - Open `project.ino` in the Arduino IDE.
   - Configure Wi-Fi credentials and MQTT broker details.
   - Add the real certificates and upload them to the microcontroller
   - Upload the code to the microcontroller.

3. **MQTT Listener**:
   - Navigate to the project directory.
   - Install mosquitto.
   - Run `listeners.py` to start receiving and processing sensor data.
   - If you are not on a Mac or not using iTerm2 run the scripts in `listeners.py` manually

## Security Considerations

- **TLS Encryption**: Ensure that the MQTT broker is configured to use TLS encryption to protect data in transit.
- **Firewall**: Configure network firewalls to allow only necessary traffic to the MQTT broker.
- **Physical Security**: Ensure the physical safety of the device using a secure enclosure, positioning and the flame detection system

## Usage

Once set up, the system will monitor environmental conditions and transmit data securely to the specified MQTT broker. The `listeners.py` script can be used to receive and process this data for further analysis or alerting.
