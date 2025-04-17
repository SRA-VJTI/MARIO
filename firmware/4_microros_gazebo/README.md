# Micro-ROS with Gazebo Integration

## Overview
This project demonstrates how to establish communication between an ESP32 microcontroller and Gazebo simulation environment using micro-ROS, enabling real-time control and visualization of a robotic manipulator.

## Prerequisites
- ROS 2 installed and configured
- Gazebo simulator
- micro-ROS workspace (`microros_ws`)
- ESP-IDF development environment
- WiFi connection
- `net-tools` package

## Setup Instructions

### 1. Launch Micro-ROS Agent

Navigate to micro-ROS workspace and start the agent:
```bash
cd ros2_ws
colcon build
source install/setup.bash
ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888
```

### 2. Configure and Flash ESP32

1. Navigate to project directory:
   ```bash
   cd MARIO/firmware/4_microros_gazebo
   ```

2. Source ESP-IDF:
   ```bash
   source $IDF_PATH/export.sh   # Or use 'get_idf' if aliased
   ```

3. Configure micro-ROS settings:
   ```bash
   idf.py menuconfig
   ```
   In `micro-ROS Settings`:
   - Configure WiFi SSID and Password
   - Set micro-ROS Agent IP (Find using `ifconfig`)
   - Verify port matches agent configuration (8888)

4. Build and flash:
   ```bash
   idf.py build
   idf.py -p PORT flash    # Replace PORT with your device (e.g., /dev/ttyUSB0)
   ```

### 3. Launch Gazebo Simulation

1. Start Gazebo simulation:
   ```bash
   cd ros2_ws
   source install/setup.bash
   ros2 launch simulation_gazebo basic_gazebo.launch.py
   ```

2. Run kinematics node (in a new terminal):
   ```bash
   cd ros2_ws
   source install/setup.bash
   ros2 run simulation_gazebo forward_kinematics.py
   ```

## Network Configuration

If `ifconfig` is not available, install net-tools:
```bash
sudo apt install net-tools
```

## System Architecture
```
[ESP32] <---> [micro-ROS Agent] <---> [ROS 2] <---> [Gazebo]
    |            (UDP/IP)           (ROS 2       (Physics
    |                               Topics)       Simulation)
 (Hardware
  Control)
```

## Troubleshooting

### Common Issues
- Verify WiFi connection is stable
- Check IP address configuration
- Ensure all terminals are properly sourced
- Confirm micro-ROS agent is running
- Verify Gazebo simulation launched successfully

### Port Access Issues
If you encounter permission issues:
```bash
sudo chmod 777 /dev/ttyUSB0   # Replace with your port
```

## Usage
1. Launch micro-ROS agent
2. Configure and flash ESP32
3. Start Gazebo simulation
4. Run kinematics node
5. Input joint angles to control the manipulator
