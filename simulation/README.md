# manipulator_rviz  
Repo with new URDF of manipulator to visualize in RViz and using command line as well as gui to give input to RViz  
### Steps to run the demo  

* Create a new catkin workspace

```
  source /opt/ros/noetic/setup.bash
  mkdir -p ~/catkin_ws/src
  cd ~/catkin_ws/
  catkin_make
  source devel/setup.bash
```

*  Clone this repo
```
  cd ~/catkin_ws/src
  cp --remove-destination -r ~/ROS-Workshop-2.1/simulation/* . 
```
  
  
*  Rebuild
```
  cd ~/catkin_ws
  catkin_make
```
*  Run the launch file
```
  roslaunch manipulator_description display.launch 
```

<p align="center">
  <img src="./assets/launch1.png" width="500"/>
</p>


   *  If you come across this error  
Could not find the GUI, install the 'joint_state_publisher_gui' package  
   *  Install  using  
sudo apt install ros-<your_version_of_ros>-joint-state-publisher-gui 
----------------------------------------------------------------------  
  
*  Once you are done with the visualisation with gui , Ctrl+ c to stop this .  
  
  
*  For command line input    
    *  roslaunch manipulator_rviz new.launch    
    *  Now ,On a different terminal  
    cd/manipulator_rviz  
    *  python pub_try1.py  
Then initially set all values to zero , to get the default position of the manipulator .  
After this you can now check for different values.

### Steps to run the demo in Gazebo
* Follow the above steps to setup the workspace and clone the repository.
*  Run the launch file
```
  roslaunch manipulator_description gazebo.launch 
```

<p align="center">
  <img src="./assets/gazebo.png" width="800"/>
</p>

### Using RQT to send commands
In this section we'll go over tools to help you visualize the performance of your controller and tune any gains/parameters the controller might have, particularly PID gains. We'll be using RQT, ROS's plugin-based user interface, so be sure you first have that installed.

Start RQT:

```
rosrun rqt_gui rqt_gui
```
#### Add a Command Publisher
On the 'Plugins' menu of RQT add the 'Topics->Message Publisher' plugin then choose the topic from the drop down box that commands any particular controller that you want to publish to. For the RRBot, add the controller:

```
/manipulator/joint_1_controller/command
```
<p align="center">
  <img src="./assets/Control_bot.gif"/>
</p>

Then press the green plus sign button at the top right.

Enable the topic publisher by checking the check box on the left of the topic name. Set the rate column to 20 (the frequency we send it commands - 20hz in this case).

Next, expand the topic so that you see the "data" row. In the expression column, on the data row, try different radian values between joint1's joint limits.

Next, in that same expression box we'll have it automatically change values using a sine wave. Add the following

```
sin(i/10)
```

#### Visualize the controller's performance
Add a Plot plugin to RQT and add the same topic as the one you chose above for the topic publisher:

```
/manipulator/joint_1_controller/command/data
```

Click the green add button. You should now see a sine wave being plotted on the screen.

Add another topic to the Plot plugin that tracks the actual position of the actuator being controlled.

```
/manipulator/joint_1_controller/state/process_value
```
<p align="center">
  <img src="./assets/Sin_Wave.gif" width="800"/>
</p>

In the graph you can see that the controller is trying to follow the command we have provided it. We have already set the PID values for our bot, but if you want to tune it there is a plugin in RQT. To know more about it visit [this tutorial](http://gazebosim.org/tutorials/?tut=ros_control#TunethePIDgains). 

**Note :** The process value doesn't go lesser than zero because of the limits we have set on the joints which is 0 to pi radians.

### Steps For Running the Scripts in Gazebo
We will be testing out 3 scripts (Testing.py, forward_kinematics.py, inverse_kinematics.py).

For running the scripts on gazebo, firstly launch gazebo world using the command

```
roslaunch manipulator_description gazebo.launch
```

After starting gazebo we will be testing out `Testing.py`. The command for that is :

```
rosrun manipulator_description Testing.py
```
Similarly, you can test out the scripts for  `forward_kinematics.py` and `inverse_kinematics.py`

