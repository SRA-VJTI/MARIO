# MICRO-ROS RVIZ

This example describe how to establish the micro-ROS connection between RViz and ESP32

## Steps to follow

* Navigate to micro-ROS workspace (for example:- `microros_ws`) 
    * ```
mkdir -p $HOME/microros_ws
cd microros_ws/``` (or name of your workspace directory)

* Start and run the micro-ROS agent on your local system by executing following commands:

```bash
colcon build
source install/setup.bash
ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888
```



* Open another terminal and source the ESP-IDF environment
    * ``` cd MARIO/firmware/3_microros_rviz ```
    * ```$IDF_PATH/export.sh``` (or ```get_idf``` if you have set up the alias in your `.bashrc` file)
    
* Configure the micro-ROS settings 
    * ```idf.py menuconfig```
    * inside `micro-ROS Settings` Set up WiFi configuration (SSID and Password) and your IP address in micro-ROS Agent IP (can be found by `ifconfig` command)

**Note** If it shows the error `ifconfig: command not found`, install the package `net-tools` by following command:

```bash
sudo apt install net-tools
```

* Build and Flash the code 
    * ```idf.py build```
    * ```idf.py -p PORT flash``` (For example: ```idf.py -p /dev/ttyUSB0 flash``` )




* In another terminal, Navigate to the ROS2 workspace and Start the Publisher by executing the relevant python script after sourcing the environment
(Make sure you have previously built the folder by executing `colcon build` command with 3_simulation_rviz in the src folder):

```bash
cd ros2_ws/
source install/setup.bash
ros2 run simulation_rviz rviz.py
```


**Note**:- If it shows the error that script is not executable, run the following command in the directory where the script is present.

```bash
sudo chmod +x rviz.py
```

* Enter the angles on the publisher side and voila! See your manipulator moving!
