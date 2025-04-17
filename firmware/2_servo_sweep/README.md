# Servo Sweep Demo

## Overview
This project demonstrates controlling three servos to perform synchronized sweep motions on an ESP32. Each servo moves through different angles in a coordinated pattern.

## Prerequisites
- ESP32 development board
- 3 servo motors connected
- ESP-IDF development environment
- USB cable for flashing

## Hardware Setup
- Ensure all three servos are properly connected to the ESP32
- Check power supply is adequate for all servos
- Verify servo signal pins are connected to correct GPIO pins

## Building and Flashing

1. Navigate to the project directory:
   ```bash
   cd firmware/servo_sweep
   ```

2. Source the ESP-IDF environment:
   ```bash
   # Option 1
   get_idf

   # Option 2
   source $IDF_PATH/export.sh
   ```

3. Build the project:
   ```bash
   idf.py build
   ```

4. Flash to ESP32:
   ```bash
   idf.py -p PORT flash
   ```
   Replace `PORT` with your ESP32's serial port (e.g., `/dev/ttyUSB0` on Linux or `COM3` on Windows)

## Troubleshooting

If you encounter a `cmake flash error`:

1. Set port permissions:
   ```bash
   sudo chmod 777 /dev/ttyUSB0   # Replace with your port
   ```

2. Try flashing again:
   ```bash
   idf.py -p PORT flash
   ```

## Demo

![Servo Sweep Demo](../../assets/simulation_mario_v2.3.gif)

## Features
- Synchronized movement of three servo motors
- Smooth sweep motion implementation
- Configurable angle ranges for each servo
- Adjustable sweep speed

## Safety Notes
- Ensure servos are mounted securely
- Keep movement area clear of obstacles
- Monitor servo temperature during extended operation
