## Steps to run the demo in Mujoco

### Build the mujoco folder from parent dir:
```
  colcon build --packages-select simulation_mujoco
```

### Now run launch file (make sure to source)
```
    source install/setup.bash
    ros2 launch simulation_mujoco mujoco_launch.py
```
### In new terminal run forward_kinematics node:
```
    source install/setup.bash
    ros2 run simulation_mujoco forward_kinematics.py
```
