## Installations

[**1. ROS2 Humble**](https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debians.html)

**2. Micro-Ros:**

So, general guidlines to run and install microros:
1. make a microros agent workspace
`mkdir -p microros_ws/src`

2. clone microros agent repository in src
`git clone -b humble https://github.com/micro-ROS/micro-ROS-Agent.git`

3. Install all the necessary dependencies for microros agent
`sudo apt update && rosdep update`

5. go back cd ..
`rosdep install --from-paths src --ignore-src -y`

6. Now, go back to home directory with `cd` and clone micro_ros_espidf_component
`git clone -b humble https://github.com/micro-ROS/micro_ros_espidf_component.git`

7. Now, before proceeding install the dependencies
`pip3 install catkin_pkg lark-parser colcon-common-extensions`

Now, you can test your code in examples

## Usage

**1. First terminal:**
`cd micro_ros_espidf_component/example/esp32_servo_subs`
```
. $IDF_PATH/export.sh
# Set target board [esp32|esp32s2|esp32s3|esp32c3]
idf.py set-target esp32
idf.py menuconfig
# Set your micro-ROS configuration and WiFi credentials under micro-ROS Settings
idf.py build
idf.py flash
idf.py monitor
```

**2. Second terminal**
cd microros_ws
colcon build
source install/setup.sh
source /opt/ros/humble/setup.sh
ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888

**3. Third terminal**
source /opt/ros/humble/setup.sh
ros2 topic list
ros2 topic echo /cmd_vel

**4. Third terminal**
source /opt/ros/humble/setup.sh
ros2 topic pub /cmd_vel geometry_msgs/Twist '{linear: {z: -0.2}, angular: {z: -0.2}}'
