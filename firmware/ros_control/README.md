# ROS Control

This example describe how to establish the rosserial connection with ESP32

## Steps to follow

* Configure the ros_control
    * ``` cd firmware/ros_control ```
    * ```idf.py menuconfig```
    * Inside `component config > MARIO-Rosserial`, Set Wifi ssid and password, Set the IP address (can be found by `ifconfig` command)

* Build and Flash the code 
    * ```idf.py build```
    * ```idf.py -p PORT flash```

* Start the ROS Core service by running the following command
    * ```roscore```

* Start the ROS Publisher by executing the relevant python script: (e.g. angle -> coordinates)

```bash
rosrun simulation_gazebo forward_kinematics.py
```
In the same way publisher_inverse_kinematices.py can be run.

**Note**:- If it shows the error that script is not executable, run the following command in the directory where the script is present.

```bash
sudo chmod +x publisher_forward_kinematics.py
```
* Start the ROS Subscriber by executing

```bash
rosrun rosserial_python serial_node.py tcp
```
* Enter the angles on the publisher side and voila! See your manipulator moving!

* Demo 
