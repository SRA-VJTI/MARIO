# ROS-Workshop-2.2

*Official Repository for ROS-based Manipulator, implemented with ESP32*

__Prerequisites__: **ROS Kinetic, initialiased with a catkin_ws workspace; ESP-IDF v4.1**

Run the following command for a quick install:

```bash
./install_codes.sh
```

## Steps

* Configure the code `ros_control/`

```bash
cd esp32_codes/ros_control/
idf.py menuconfig
```

* Inside `component config > rosserial`, Set Wifi ssid and password, Set the IP address (can be found by `ifconfig` command)  

* Flash the code `ros_control/`

```bash
idf.py flash
```

* Start the ROS Core service i.e. the ROS Master by the `roscore` command.

* Start the ROS Publisher by executing the relevant python script: (e.g. angle -> coordinates)

```bash
rosrun sra20 publisher_forward_kinematics.py
```

* Start the ROS Subscriber by executing

```bash
rosrun rosserial_python serial_node.py tcp
```

* Enter the angles on the publisher side and voila! See your manipulator moving!

![arm video](assets/arm.gif)

## Resources

Follow this [link](https://drive.google.com/drive/folders/1yD07hE1b5nYZh2sltAaAGxTKHSL-BK6s) for all the reference material related to the workshop.
