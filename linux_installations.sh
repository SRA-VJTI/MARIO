#!/usr/bin/env bash

set -e

red=`tput setaf 1`
green=`tput setaf 2`
blue=`tput setaf 4`
reset=`tput sgr0`

echo "${blue}======================${reset}"
echo "MARIO - Linux Installation Script"
echo "${blue}======================${reset}"

if [ -n "$ZSH_VERSION" ]; then
    _shell_="zsh"
    _rc_file_="$HOME/.zshrc"
elif [ -n "$BASH_VERSION" ]; then
    _shell_="bash"
    _rc_file_="$HOME/.bashrc"
elif [ -n "$KSH_VERSION" ]; then
    _shell_="ksh"
    _rc_file_="$HOME/.kshrc"
else
    _shell_="bash"
    _rc_file_="$HOME/.bashrc"
fi

# ESP-IDF Installation
echo "${blue}======================${reset}"
echo "Checking ESP-IDF installation"
echo "${blue}======================${reset}"

if [ -d $HOME/esp/esp-idf ]; then
    echo "${red}======================${reset}"
    echo "ESP-IDF is already installed!"
    echo "${blue}======================${reset}"
else
    echo "${blue}======================${reset}"
    echo "Installing ESP-IDF dependencies"
    echo "${blue}======================${reset}"

    sudo apt update && sudo apt upgrade -y
    sudo usermod -a -G dialout $USER
    sudo apt install git wget flex bison gperf python3 python3-pip python3-setuptools cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0 python3-venv -y

    # Create ESP Directory
    mkdir -p "$HOME/esp"
    pushd "$HOME"/esp || (echo "Error: Cannot Make Directory" && exit 1)

    # Clone ESP-IDF Repository
    git clone -b release/v5.1 --recursive https://github.com/espressif/esp-idf.git
    cd $HOME/esp/esp-idf
    ./install.sh esp32

    # Check if installation is successful
    . $HOME/esp/esp-idf/export.sh
    echo "${green}ESP-IDF Installation Successful${reset}"

    # Set IDF Alias
    echo "alias get_idf='. \$HOME/esp/esp-idf/export.sh'" >> "$_rc_file_"
    idf.py --version
fi

# Clone Mario repository if not already cloned
echo "${blue}======================${reset}"
echo "Checking MARIO repository"
echo "${blue}======================${reset}"

if [ ! -d $HOME/MARIO ]; then
    echo "Cloning MARIO repository..."
    cd $HOME
    git clone -b humble --recursive https://github.com/SRA-VJTI/MARIO.git
    echo "${green}MARIO repository cloned successfully${reset}"
else
    echo "${red}MARIO repository already exists. Skipping cloning.${reset}"
fi

# ROS 2 and Ignition Fortress Installation
echo "${blue}======================${reset}"
echo "Checking ROS 2 installation"
echo "${blue}======================${reset}"

if ! command -v ros2 &>/dev/null; then
    echo "ROS 2 is not installed. Proceeding with installation..."

    # Check for UTF-8 locale
    locale
    sudo apt update && sudo apt install locales
    sudo locale-gen en_US en_US.UTF-8
    sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
    export LANG=en_US.UTF-8
    locale  # verify settings

    # Add ROS 2 repository
    sudo apt install software-properties-common
    sudo add-apt-repository universe
    sudo apt update && sudo apt install curl -y
    sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
    echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null
    sudo apt update
    sudo apt upgrade

    # Install ROS 2
    sudo apt install ros-humble-desktop-full -y
    echo "source /opt/ros/humble/setup.bash" >> "$_rc_file_"
fi

# Install Ignition Fortress and ROS 2 packages
echo "${blue}======================${reset}"
echo "Installing Ignition Fortress and ROS 2 packages"
echo "${blue}======================${reset}"

# Install Ignition Fortress
sudo apt install ignition-fortress -y

# Install ROS 2 Ignition Bridge and related packages
sudo apt install ros-humble-ros-ign -y
sudo apt install ros-humble-ign-ros2-control -y
sudo apt install ros-humble-ros-ign-gazebo -y

# Install additional ROS 2 dependencies
sudo apt install -y \
    ros-humble-xacro \
    ros-humble-robot-state-publisher \
    ros-humble-joint-state-broadcaster \
    ros-humble-joint-trajectory-controller \
    ros-humble-forward-command-controller \
    ros-humble-rviz2 \
    ros-humble-ros2-control \
    ros-humble-joint-state-publisher-gui \
    ros-humble-controller-manager \
    ros-humble-controller-manager-msgs \
    python3-colcon-common-extensions \
    ros-humble-micro-ros-msgs
source /opt/ros/humble/setup.bash

# Set up workspace
echo "${blue}======================${reset}"
echo "Setting up ROS 2 workspace"
echo "${blue}======================${reset}"

if [ -d "$HOME/ros2_ws" ]; then
    echo "ros2_ws already exists."
else
    echo "Creating ros2_ws..."
    echo "source /usr/share/colcon_argcomplete/hook/colcon-argcomplete.bash" >> "$_rc_file_"
    mkdir -p $HOME/ros2_ws/src
    cd $HOME/ros2_ws
    colcon build
    echo "source $HOME/ros2_ws/install/setup.bash" >> "$_rc_file_"
    echo "${green}ros2_ws successfully setup${reset}"
fi

# Copy MARIO folders to ros2_ws
echo "${blue}======================${reset}"
echo "Setting up MARIO packages"
echo "${blue}======================${reset}"

cd $HOME/ros2_ws/src
if [[ ! -d "1_chatter_listener" ]]; then
    echo "Copying MARIO's folders to ros2_ws..."
    cp -r $HOME/MARIO/1_* $HOME/ros2_ws/src
    cp -r $HOME/MARIO/2_* $HOME/ros2_ws/src
    cp -r $HOME/MARIO/3_* $HOME/ros2_ws/src
    cp -r $HOME/MARIO/4_* $HOME/ros2_ws/src
    cp -r $HOME/MARIO/activities $HOME/ros2_ws/src

    if [[ ! -d "$HOME/ros2_ws_firmware" ]]; then
        mkdir -p $HOME/ros2_ws_firmware
        mkdir -p $HOME/ros2_ws_firmware/components
        cp -r $HOME/MARIO/firmware/1_* $HOME/ros2_ws_firmware
        cp -r $HOME/MARIO/firmware/2_* $HOME/ros2_ws_firmware
        cp -r $HOME/MARIO/firmware/3_* $HOME/ros2_ws_firmware
        cp -r $HOME/MARIO/firmware/4_* $HOME/ros2_ws_firmware
        cp -r $HOME/MARIO/firmware/components/sra-board-component $HOME/ros2_ws_firmware/components/
        echo "${green}Firmware copied to ros2_ws_firmware${reset}"
    else
        echo "${green}Firmware directory already exists${reset}"
    fi
else
    echo "${green}ROS folders are already copied${reset}"
fi

# Set up microROS Agent
echo "${blue}======================${reset}"
echo "Setting up microROS Agent"
echo "${blue}======================${reset}"

cd $HOME/ros2_ws/src
git clone -b humble https://github.com/micro-ROS/micro-ROS-Agent.git
cd ..
pip3 install catkin_pkg lark-parser colcon-common-extensions

cd $HOME/ros2_ws_firmware/components
git clone --recursive https://github.com/micro-ROS/micro_ros_espidf_component.git
cd ../..

sudo apt install terminator

# Build the workspace
echo "${blue}======================${reset}"
echo "Building the workspace"
echo "${blue}======================${reset}"

cd $HOME/ros2_ws
colcon build
echo "${green}======================${reset}"
echo "Installation completed successfully!"
echo "Please restart your terminal or run 'source ~/.bashrc' to apply changes"
echo "${green}======================${reset}"e
