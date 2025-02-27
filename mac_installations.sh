#!/usr/bin/env bash

set -e

red=`tput setaf 1`
green=`tput setaf 2`
blue=`tput setaf 4`
reset=`tput sgr0`

echo "${blue}======================${reset}"
echo "MARIO - macOS Installation Script"
echo "${blue}======================${reset}"

_shell_="${0##*/}"

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
    
    # Check and install Homebrew if needed
    if brew --version | grep -q 'Homebrew'; then
        echo "Homebrew is already installed"
    else 
        echo "Installing homebrew..."
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
        echo "${green}Homebrew installed successfully${reset}"
    fi
    
    # Install ESP-IDF dependencies
    brew install git cmake ninja dfu-util python3
    
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
    echo "alias get_idf='. $HOME/esp/esp-idf/export.sh'" >> $HOME/."$_shell_"rc
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

# Install Mambaforge for ROS 2
echo "${blue}======================${reset}"
echo "Setting up Mambaforge for ROS 2"
echo "${blue}======================${reset}"

if command -v mamba &>/dev/null; then
    echo "Mambaforge is already installed"
else
    echo "Installing Mambaforge..."
    wget -q https://github.com/conda-forge/miniforge/releases/latest/download/Mambaforge-$(uname)-$(uname -m).sh -O mambaforge.sh
    chmod +x mambaforge.sh
    ./mambaforge.sh -b
    rm mambaforge.sh
    export PATH="$HOME/mambaforge/bin:$PATH"
    mamba init --all
    echo "${green}Mambaforge installed and initialized${reset}"
    echo "Please reopen your terminal after this script completes to activate mambaforge."
fi

# Set up Mamba environment
echo "${blue}======================${reset}"
echo "Setting up ROS 2 environment with Mamba"
echo "${blue}======================${reset}"

# Ensure mamba is in the PATH
export PATH="$HOME/mambaforge/bin:$PATH"

# Install mamba in the base environment
conda install mamba -y -c conda-forge

# Create ROS environment if it doesn't exist
if conda info --envs | grep -q "ros_env"; then
    echo "ros_env environment already exists"
else
    echo "Creating ros_env environment..."
    mamba create -n ros_env -y -c conda-forge 
fi

# Activate the environment and configure channels
source $HOME/mambaforge/etc/profile.d/conda.sh
conda activate ros_env
conda config --env --add channels conda-forge
conda config --env --add channels robostack-staging
conda config --env --remove channels defaults || true

# Install ROS 2 and related packages
echo "${blue}======================${reset}"
echo "Installing ROS 2 packages (this may take a while)"
echo "${blue}======================${reset}"

mamba install -y ros-humble-desktop-full

# Install additional ROS 2 packages
echo "${blue}======================${reset}"
echo "Installing additioal ROS 2 packages"
echo "${blue}======================${reset}"

mamba install -n ros_env -y \
    ros-humble-ros2-control \
    ros-humble-joint-state-broadcaster \
    ros-humble-joint-state-publisher \
    ros-humble-joint-state-publisher-gui \
    ros-humble-forward-command-controller \
    ros-humble-robot-state-publisher \
    ros-humble-controller-manager \
    ros-humble-controller-manager-msgs \
    ros-humble-joint-trajectory-controller \
    ros-humble-xacro \
    ros-humble-rviz2 \
    catkin_tools \
    colcon-common-extensions \
    rosdep

# Add environment activation to shell config
if ! grep -q "conda activate ros_env" $HOME/."$_shell_"rc; then
    echo "# Activate ROS 2 environment" >> $HOME/."$_shell_"rc
    echo "conda activate ros_env" >> $HOME/."$_shell_"rc
fi

# Set up workspace
echo "${blue}======================${reset}"
echo "Setting up ROS 2 workspace"
echo "${blue}======================${reset}"

if [ -d "$HOME/ros2_ws" ]; then
    echo "ros2_ws already exists."
else
    echo "Creating ros2_ws..."
    mkdir -p $HOME/ros2_ws/src
    cd $HOME/ros2_ws
    
    # Ensure proper permissions
    sudo chown -R $(whoami) $HOME/ros2_ws
    
    # Initial build
    conda activate ros_env
    colcon build
    
    # Add workspace setup to shell config
    echo "# Source ROS 2 workspace" >> $HOME/."$_shell_"rc
    echo "source $HOME/ros2_ws/install/setup.bash" >> $HOME/."$_shell_"rc
    
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
        cp -r $HOME/MARIO/firmware/* $HOME/ros2_ws_firmware
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
pip3 install catkin_pkg lark-parser
git clone -b humble https://github.com/micro-ROS/micro-ROS-Agent.git

# Build the workspace
echo "${blue}======================${reset}"
echo "Building the workspace"
echo "${blue}======================${reset}"

cd $HOME/ros2_ws
conda activate ros_env
colcon build

# Note about Ignition/Gazebo
echo "${blue}======================${reset}"
echo "Note about Ignition/Gazebo on macOS"
echo "${blue}======================${reset}"
echo "Ignition Fortress is not fully supported on macOS through conda packages."
echo "If you need Gazebo simulation, consider using a Linux virtual machine or dual boot."

echo "${green}======================${reset}"
echo "Installation completed successfully!"
echo "Please restart your terminal to apply all changes."
echo "${green}======================${reset}"n
