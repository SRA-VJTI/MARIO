# Manipulator Simulation
* Here we will simulate the manipulator


## File Structure
    .
    ├── simulation_gazebo       #package for running the Manipulator simulation in gazebo
        ├── launch              #folder containing the launch files
        ├── urdf                #folder containing the urdf files           
        ├── scripts             #folder containing the scripts
        ├── config              #folder containing the config.yaml file
        └── config              #folder containing the config.yaml file
    └── simulation_rviz         #package for running the Manipulator simulation in rviz
        ├── launch              #folder containing the launch files
        ├── urdf                #folder containing the urdf files           
        ├── scripts             #folder containing the scripts
        ├── config              #folder containing the config.yaml file
        └── config              #folder containing the config.yaml file

    .
    |──simulation_gazebo #package for running the Manipulator simulation in gazebo
      |--
    |--simulation_rviz #package for running the Manipulator simulation in rviz
      |--
    |--simulation_DH #package for running the Simulation for calculating the DH parameters 

## Steps for Setting up the workspace
* First we will source ROS

```
source ~/Ros_workshop/devel/setup.bash
```

* installing the drivers for ros-control

```
sudo apt-get install ros-noetic-ros-control ros-noetic-ros-controllers
```
Now you can run the simulations in Gazebo and RViz.
