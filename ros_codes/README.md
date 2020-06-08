# MARIO v2.1 

ROS Codes for **M**anipulator on **R**OS **B**ased **I**nput **O**utput  

Start master by running `roscore`  

* In two different terminals run `rosrun sra20 chat_talker.py` and `rosrun sra20 chat_listener.py` for sending string message  

* In two different terminals run `rosrun sra20 publisher.py` and `rosrun sra20 subscriber.py` for sending custom message of type specified in `msg` directory  

* `rosrun sra20 publisher_forward_kinematics.py` for entering joint angles and getting end-effector's coordinates  

* `rosrun sra20 publisher_inverse_kinematics.py` for entering end-effector's coordinates and getting joint angles  

Run forward and inverse kinematics in different terminals to check the respective values  
