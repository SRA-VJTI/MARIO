# talker and listener 
Steps to talker ans listener scripts :
* If you haven't cloned the repo, clone the repo and rebuild the catkin workspace by following the instructions specified in the beginning.
* Start `roscore` in a terminal.
```
source /opt/ros/noetic/setup.bash
roscore
```
* Open another terminal to run `talker.py`
```
source ~/catkin_ws/devel/setup.bash
rosrun chatter_listener talker.py
```
* Open another terminal to rub `listener.py`
```
source ~/catkin_ws/devel/setup.bash
rosrun chatter_listener listener.py
```
* To know more about it visit [this tutorial](http://wiki.ros.org/ROS/Tutorials/WritingPublisherSubscriber%28python%29)