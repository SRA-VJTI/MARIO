#!/bin/bash
# Run it as root first and then without
# sudo chmod +x ros_installation.sh
# sudo ./ros_installation.sh && ./ros_installation.sh
# After the file runs successfully, try running roscore in a new terminal.go to catkin_ws present in home and try running catkin_make.
set -e

red=`tput setaf 1`
green=`tput setaf 2`
reset=`tput sgr0`
ros_distro='noetic'
if [[ $(lsb_release -rs) == "18.04" ]]; then
        ros_distro="melodic"
fi
echo $ros_distro
pkg=ros-$ros_distro-desktop-full


function install(){
    apt-get update
    apt-get install curl
    echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list
    curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | apt-key add -
    apt-get update
    apt-get install ros-$ros_distro-desktop-full python3-pip ros-$ros_distro-effort-controllers ros-$ros_distro-rosserial-arduino
    apt-get install python3-rosdep python3-rosinstall python3-rosinstall-generator python3-wstool build-essential net-tools
    rosdep init
}

function configure(){
    set +e
    dpkg -s $pkg &> /dev/null
    if  [ $? -eq 0 ]; then
        echo "$green Successfully installed $pkg $reset"
    else
        echo "$red $pkg is not installed. Run this script as root $reset"
        exit 1
    fi
    /usr/bin/python3 -m pip install empy
    echo "alias get_ros_noetic='source /opt/ros/$ros_distro/setup.bash'" >> $HOME/.bash_aliases
    source $HOME/.bashrc
    source /opt/ros/$ros_distro/setup.bash
    rosdep update
    cd $HOME
    mkdir -p $HOME/catkin_ws/src
    cd $HOME/catkin_ws/src
    if [[ ! -d "1_chatter_listener" ]]; then
        git clone --recursive https://github.com/SRA-VJTI/MARIO.git /tmp/ros_ws
        mv /tmp/ros_ws/1_* $HOME/catkin_ws/src
	mv /tmp/ros_ws/2_* $HOME/catkin_ws/src
	mv /tmp/ros_ws/3_* $HOME/catkin_ws/src
	mv /tmp/ros_ws/4_* $HOME/catkin_ws/src
        if [[ ! -d "$HOME/ros_ws_firmware" ]]; then
            mkdir -p $HOME/ros_ws_firmware
            mv /tmp/ros_ws/firmware/* $HOME/ros_ws_firmware
            echo "${red}======================"
            echo "$green Ros Repository cloned newly and processed : ESP32 Codes $reset"
        else 
            echo "${red}======================"
            echo "$green Already processed : ESP32 Codes $reset"
        fi
        rm -rf /tmp/ros_ws
        echo "${red}======================"
        echo "$green Ros Repository newly cloned and processed$reset"
    else
        echo "${red}======================"
        echo "$green Ros Repository already existed and processed $reset"
    fi
    cd ..
    catkin_make
    source $HOME/catkin_ws/devel/setup.bash
}

if [[ "$EUID" -eq 0 ]]; 
then 
    install
    echo "${red}======================"
    echo "${green}Please run without root once more" 1>&2 
    echo "${red}======================"
    exit
else
    configure
    echo "${green}======================"
    echo "${green}Installed & Configured"
    echo "${green}======================"
    exit
fi








