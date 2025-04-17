# Servo Set Zero

This example demonstrates how to set all three servos to a specific angle position.

## Prerequisites

- ESP-IDF development environment installed and configured
- ESP32 development board
- USB cable for flashing

## Building and Flashing

1. Navigate to the project directory:
   ```bash
   cd firmware/servo_set_zero
   ```

2. Source the ESP-IDF environment (if not already done):
   ```bash
   # Option 1
   get_idf

   # Option 2
   source . ./esp/esp-idf/export.sh
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

If you encounter a `cmake flash error`, try the following:

1. Grant permissions to the serial port:
   ```bash
   sudo chmod 777 /dev/ttyUSB0   # Replace with your port
   ```

2. Flash again:
   ```bash
   idf.py -p PORT flash
