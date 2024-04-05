# Servo Sweep

This example and code describes how to set all three servos at different angles & perform a complete "sweep" motion.

## Steps to follow

* Build and Flash the code
    * Open the project directory using :
      ```cd firmware/servo_sweep```
    * Ensure that ESP-IDF environment is sourced ( ``` get_idf ``` or ``` $IDF_PATH/export.sh ``` ) before proceeding further. Build using the command :
      ```idf.py build```
    * Flash the code onto the ESP32
      ```idf.py -p PORT flash```

Note :- If it shows ```cmake flash error```. Run the following commands
* ```sudo chmod 777 PORT```
* ```idf.py -p PORT flash```
*  ``` PORT ``` is the port name to which ESP32 is connected (example : ``` /dev/ttyUSB0 ```)

## Demo 
![](../../assets/arm.gif)
