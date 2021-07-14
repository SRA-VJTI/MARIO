# Servo Test Webserver

This example implements webserver functionality. It provides an easy webpage based User Interface to interact with the servos.

## Steps to follow

* Configure the project
    * ```cd firmware/servo_test_webserver```
    * ```idf.py menuconfig```
    * Inside ```component config -> MARIO testing -> WiFi Config``` set the ssid and password

* Build and Flash the code 
    
    * ```idf.py build```
    * ```idf.py -p PORT flash```

* Monitor the logs
    * ``` idf.py monitor ```

* Access the website using the ```sta ip``` shown on terminal. Simply paste that ```sta_ip``` on browser link section.

Note :- If it shows ```cmake flash error```. Run the following commands
* ```sudo chmod 777 PORT```
* ```idf.py -p PORT flash```


## Demo 
