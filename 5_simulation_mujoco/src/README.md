## Steps to run the demo in Mujoco

### Build the mujoco folder from 5_simulation_mujoco:
```
  cd 5_simulation_mujoco/
  colcon build 
```

### Now run launch file (make sure to source):
```
    source install/setup.bash
    ros2 launch simulation_mujoco mujoco_launch.py
```
### In new terminal run forward_kinematics node:
```
    source install/setup.bash
    ros2 run simulation_mujoco forward_kinematics.py
```

### To run mario with box simulation:
```
    source install/setup.bash
    ros2 launch simulation_mujoco mario_controller.py
```
