# Micro-ROS with Gazebo Integration

## Overview
This project demonstrates how to establish communication between an ESP32 microcontroller and Gazebo simulation environment using micro-ROS, enabling real-time control and visualization of a robotic manipulator.

## Prerequisites
- ROS 2 installed and configured
- Gazebo simulator
- ROS 2 workspace with micro-ROS agent built (`ros2_ws`)
- ESP-IDF development environment
- WiFi connection
- `net-tools` package

## Option 1: WiFi Network

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
   cd ros2_ws_firmware/4_microros_gazebo_mujoco
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

## Option 2: PC Hotspot

If you don't have access to a shared WiFi network, you can create a hotspot from your PC.

### Terminal 1: Create PC Hotspot
```bash
nmcli device wifi hotspot ssid YOUR_HOTSPOT_NAME password "YOUR_PASSWORD" band bg
```

Check the PC's IP address:
```bash
ifconfig
```
The PC hotspot IP is typically `10.42.0.1`.

### Terminal 2: Start Micro-ROS Agent
```bash
cd ros2_ws
source install/setup.bash
ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888 -v6
```

### Terminal 3: Configure and Flash ESP32

1. Navigate to project directory:
   ```bash
   cd ros2_ws_firmware/4_microros_gazebo_mujoco
   ```

2. Source ESP-IDF:
   ```bash
   source $IDF_PATH/export.sh   # Or use 'get_idf' if aliased
   ```

3. Configure settings:
   ```bash
   idf.py menuconfig
   ```
   In `micro-ROS Settings`:
   - WiFi SSID: `YOUR_HOTSPOT_NAME` (must match the hotspot name)
   - WiFi Password: `YOUR_PASSWORD` (must match the hotspot password)
   - Agent IP: `10.42.0.1` (verify with `ifconfig`)
   - Agent Port: `8888`

4. Build and flash:
   ```bash
   idf.py build
   idf.py -p PORT flash
   ```

### Terminal 4: Launch Simulation and FK Node
```bash
cd ros2_ws
source install/setup.bash
ros2 launch simulation_gazebo basic_gazebo.launch.py
```

In a new terminal:
```bash
cd ros2_ws
source install/setup.bash
ros2 run simulation_gazebo forward_kinematics.py
```

> **Note:** If the ESP32 fails to connect, try pressing the reset button on the SRA board after the agent is running.

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
