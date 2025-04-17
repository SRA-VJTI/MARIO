# Servo Test Webserver

## Overview
This project implements a web-based interface for controlling servo motors on an ESP32. Users can interact with the servos through a simple webpage, making it easy to test and control servo movements without specialized hardware.

## Prerequisites
- ESP32 development board
- ESP-IDF development environment
- Connected servo motors
- WiFi network access
- Web browser
- USB cable for flashing

## Hardware Setup
- ESP32 properly connected to servos
- Power supply adequate for servo operation
- USB connection for flashing and monitoring

## Configuration and Installation

### 1. Navigate to Project Directory
```bash
cd ros2_ws_firmware/5_servo_test_webserver
```

### 2. Configure WiFi Settings
```bash
idf.py menuconfig
```
Navigate to:
- Component config
  - MARIO testing
    - WiFi Config
      - Set SSID
      - Set Password

### 3. Build and Flash
```bash
idf.py build
idf.py -p PORT flash    # Replace PORT with your device (e.g., /dev/ttyUSB0)
```

### 4. Monitor Device
```bash
idf.py monitor
```

## Accessing the Web Interface

1. After successful boot, look for the `sta ip` address in the monitor output
2. Open a web browser
3. Enter the IP address in the address bar
4. The control interface should load automatically

## Troubleshooting

### Flash Issues
If you encounter `cmake flash error`:
```bash
sudo chmod 777 /dev/ttyUSB0   # Replace with your port
idf.py -p PORT flash
```

### Common Issues
- Ensure WiFi credentials are correct
- Verify ESP32 is within WiFi range
- Check if servos are properly connected
- Confirm proper power supply to ESP32 and servos

## Features
- Web-based servo control interface
- Real-time servo position updates
- Multiple servo support
- User-friendly interface
- Mobile-responsive design

## Safety Notes
- Keep servos within safe operating ranges
- Monitor servo temperature
- Avoid sudden extreme movements
- Ensure stable power supply
