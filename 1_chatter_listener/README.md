# ROS 2 Talker and Listener Demo

## Overview
This project demonstrates basic ROS 2 publisher-subscriber communication using a simple talker (publisher) and listener (subscriber) example.

## Prerequisites
- ROS 2 installed and configured
- Working ROS 2 workspace (`ros2_ws`)
- MARIO repository cloned

## Installation

1. Copy the package to your ROS 2 workspace:
   ```bash
   cp -r ~/MARIO/1_chatter_listener ~/ros2_ws/src
   ```

2. Navigate to your workspace:
   ```bash
   cd ~/ros2_ws
   ```

3. Build the package:
   ```bash
   colcon build
   ```

4. Source the workspace:
   ```bash
   source install/setup.bash
   ```

## Running the Demo

### Terminal 1 - Talker (Publisher)
```bash
source ~/ros2_ws/install/setup.bash
ros2 run chatter_listener talker.py
```

### Terminal 2 - Listener (Subscriber)
```bash
source ~/ros2_ws/install/setup.bash
ros2 run chatter_listener listener.py
```

## Demo Visualization

<p align="center">
   <img src="assets/talker_listener.gif" width="800" height="480" alt="Talker Listener Demo">
</p>

## Additional Information
- The talker node publishes messages at a fixed rate
- The listener node subscribes to these messages and displays them
- Both nodes need to be run simultaneously to demonstrate the communication

## Troubleshooting
- Ensure both terminals are properly sourced
- Check if ROS 2 daemon is running (`ros2 daemon status`)
- Verify that nodes are visible using `ros2 node list`
