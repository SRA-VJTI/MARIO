# Servo Set Zero

This example illustrates how to set all three servos at a specific angle

## Steps to follow

* Build and Flash the code
    * Open the project directory using :
      ``` cd firmware/servo_set_zero ```
    * Ensure that ESP-IDF environment is sourced ( ``` get_idf ``` or ``` $IDF_PATH/export.sh ``` ) before proceeding further. Build using the command :
      ``` idf.py build ```
    * Flash the code onto the ESP32
      ``` idf.py -p PORT flash ```

Note :- If it shows ``` cmake flash error ```. Run the following commands
* ``` sudo chmod 777 PORT ```
* ``` idf.py -p PORT flash ```
*  ``` PORT ``` is the port name to which ESP32 is connected (example : ``` /dev/ttyUSB0 ```)
