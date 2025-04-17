# Micro-ROS with RViz Integration

## Overview
This project demonstrates the integration of ESP32 with RViz using micro-ROS, allowing real-time visualization and control of a robotic manipulator.

## Prerequisites
- ROS 2 installed and configured
- micro-ROS workspace set up (`microros_ws`)
- ESP-IDF development environment
- RViz
- WiFi connection
- `net-tools` package (for network configuration)

## Setup Instructions

### 1. Start Micro-ROS Agent

Navigate to micro-ROS workspace and start the agent:
```bash
cd microros_ws
colcon build
source install/setup.bash
ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888
```

### 2. Configure and Flash ESP32

1. Navigate to project directory:
   ```bash
   cd MARIO/firmware/3_microros_rviz
   ```

2. Source ESP-IDF:
   ```bash
   source $IDF_PATH/export.sh   # Or use 'get_idf' if aliased
   ```

3. Configure WiFi and micro-ROS settings:
   ```bash
   idf.py menuconfig
   ```
   In `micro-ROS Settings`:
   - Set WiFi SSID and Password
   - Configure micro-ROS Agent IP (Find using `ifconfig`)

4. Build and flash:
   ```bash
   idf.py build
   idf.py -p PORT flash    # Replace PORT with your device (e.g., /dev/ttyUSB0)
   ```

### 3. Launch RViz Visualization

1. Navigate to ROS 2 workspace:
   ```bash
   cd ros2_ws
   source install/setup.bash
   ros2 run simulation_rviz rviz.py
   ```

## Network Configuration

If `ifconfig` command is not found, install net-tools:
```bash
sudo apt install net-tools
```

## Troubleshooting

### Script Execution Issues
If the script isn't executable, set permissions:
```bash
sudo chmod +x rviz.py
```

### Common Issues
- Ensure WiFi connection is stable
- Verify IP addresses are correctly configured
- Check if all terminals are properly sourced
- Confirm micro-ROS agent is running

## Usage
1. Start micro-ROS agent
2. Flash and run ESP32 code
3. Launch RViz visualization
4. Input angles through the publisher interface
5. Observe manipulator movement in RViz

## System Architecture
```
[ESP32] <---> [micro-ROS Agent] <---> [ROS 2] <---> [RViz]
    |            (UDP/IP)           (ROS 2       (Visualization)
    |                               Topics)
 (Hardware
  Control)
```

## Additional Notes
- Ensure all dependencies are installed
- Keep network configuration consistent
- Monitor ESP32 serial output for debugging
- Check ROS 2 topic lists to verify communication
