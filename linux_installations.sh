#!/usr/bin/env bash
set -e

# Define colors for output
red=$(tput setaf 1)
green=$(tput setaf 2)
blue=$(tput setaf 4)
reset=$(tput sgr0)

# Determine which shell configuration file to update
# --- Kept original robust logic ---
if [ -n "$BASH_VERSION" ]; then
    rc_file="$HOME/.bashrc"
elif [ -n "$ZSH_VERSION" ]; then
    rc_file="$HOME/.zshrc"
else
    rc_file="$HOME/.profile"
fi

echo "${blue}======================${reset}"
echo "MARIO - Linux Installation Script"
echo "${blue}======================${reset}"

# -------------------------------------------
# ESP-IDF Installation
# -------------------------------------------
echo "${blue}======================${reset}"
echo "Checking ESP-IDF installation"
echo "${blue}======================${reset}"

if [ -d "$HOME/esp/esp-idf" ]; then
    echo "${red}======================${reset}"
    echo "ESP-IDF is already installed!"
    echo "${blue}======================${reset}"
else
    echo "${blue}======================${reset}"
    echo "Installing ESP-IDF dependencies"
    echo "${blue}======================${reset}"

    sudo apt update && sudo apt upgrade -y
    sudo usermod -a -G dialout "$USER"
    # --- Ensured -y is present ---
    sudo apt install -y git wget flex bison gperf python3 python3-pip python3-setuptools cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0 python3-venv

    # Create ESP directory and clone ESP-IDF repository
    mkdir -p "$HOME/esp"
    pushd "$HOME/esp" || { echo "Error: Cannot change directory to $HOME/esp"; exit 1; }
    git clone -b release/v5.1 --recursive https://github.com/espressif/esp-idf.git
    popd
    cd "$HOME/esp/esp-idf"
    ./install.sh esp32

    # Source ESP-IDF environment and confirm installation
    . "$HOME/esp/esp-idf/export.sh"
    echo "${green}ESP-IDF Installation Successful${reset}"

    # Set alias for easy access to ESP-IDF environment
    # --- Kept original $rc_file logic ---
    echo "alias get_idf='. \$HOME/esp/esp-idf/export.sh'" >> "$rc_file"
    idf.py --version
fi

# -------------------------------------------
# MARIO Repository Clone
# -------------------------------------------
echo "${blue}======================${reset}"
echo "Checking MARIO repository"
echo "${blue}======================${reset}"

if [ ! -d "$HOME/MARIO" ]; then
    echo "Cloning MARIO repository..."
    cd "$HOME"
    git clone -b humble --recursive https://github.com/SRA-VJTI/MARIO.git
    echo "${green}MARIO repository cloned successfully${reset}"
else
    echo "${red}MARIO repository already exists. Skipping cloning.${reset}"
fi

# -------------------------------------------
# ROS 2 and Ignition Fortress Installation
# -------------------------------------------
echo "${blue}======================${reset}"
echo "Checking ROS 2 installation"
echo "${blue}======================${reset}"

if ! command -v ros2 &>/dev/null; then
    echo "ROS 2 is not installed. Proceeding with installation..."

    # Ensure UTF-8 locale is set up
    locale
    sudo apt update && sudo apt install -y locales
    sudo locale-gen en_US en_US.UTF-8
    sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
    export LANG=en_US.UTF-8
    locale  # verify locale settings

    # Add ROS 2 repository
    sudo apt install -y software-properties-common
    sudo add-apt-repository universe
    sudo apt update && sudo apt install -y curl
    sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
    echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null
    # --- Ensured -y is present ---
    sudo apt update && sudo apt upgrade -y

    # Install ROS 2
    sudo apt install -y ros-humble-desktop-full
    # --- Kept original $rc_file logic ---
    echo "source /opt/ros/humble/setup.bash" >> "$rc_file"
    source /opt/ros/humble/setup.bash
fi

# -------------------------------------------
# Installing rosdep2
# -------------------------------------------
if ! command -v rosdep &>/dev/null; then
    echo "${blue}======================${reset}"
    echo "Installing rosdep2"
    echo "${blue}======================${reset}"
    sudo apt install -y python3-rosdep
    sudo rosdep init || echo "${green}rosdep already initialized. Continuing.${reset}" # Changed to non-fatal message
    rosdep update
else
    echo "${green}rosdep is already installed${reset}"
    # Ensure rosdep is updated even if installed
    echo "${blue}Updating rosdep...${reset}"
    rosdep update
fi

# -------------------------------------------
# Optionally Source /opt/ros/humble/setup.bash (redundant check, source happens above/below)
# This block might be slightly redundant as it's sourced during install and workspace setup
# but leaving it doesn't hurt. Using $rc_file is correct.
# -------------------------------------------
if [ -f "/opt/ros/humble/setup.bash" ]; then
    # Check if the line already exists in the rc file
    if ! grep -q "source /opt/ros/humble/setup.bash" "$rc_file"; then
        echo "${blue}======================${reset}"
        echo "Adding source /opt/ros/humble/setup.bash to $rc_file"
        echo "${blue}======================${reset}"
        echo "source /opt/ros/humble/setup.bash" >> "$rc_file"
    fi
    # Source it for the current session too
    source /opt/ros/humble/setup.bash
fi


# -------------------------------------------
# Installing Ignition Fortress and related ROS 2 packages
# -------------------------------------------
echo "${blue}======================${reset}"
echo "Installing Ignition Fortress and ROS 2 packages"
echo "${blue}======================${reset}"

# Install Ignition Fortress
sudo apt install -y ignition-fortress

# Install ROS 2 Ignition Bridge and related packages
sudo apt install -y ros-humble-ros-ign
sudo apt install -y ros-humble-ign-ros2-control
sudo apt install -y ros-humble-ros-ign-gazebo

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

# Source again in case ROS was just installed
if [ -f "/opt/ros/humble/setup.bash" ]; then
    source /opt/ros/humble/setup.bash
fi

# -------------------------------------------
# Set up ROS 2 workspace
# -------------------------------------------
echo "${blue}======================${reset}"
echo "Setting up ROS 2 workspace"
echo "${blue}======================${reset}"

if [ -d "$HOME/ros2_ws/src" ]; then # Check for src to be more specific
    echo "${green}ros2_ws/src already exists.${reset}"
else
    echo "Creating ros2_ws..."
    mkdir -p "$HOME/ros2_ws/src"
    # Add colcon argcomplete hook if colcon is installed
    if command -v colcon &> /dev/null; then
         if ! grep -q "colcon-argcomplete.bash" "$rc_file"; then # Avoid duplicates
             echo "source /usr/share/colcon_argcomplete/hook/colcon-argcomplete.bash" >> "$rc_file"
         fi
    fi
    # Perform an initial build to create install directory structure
    cd "$HOME/ros2_ws"
    colcon build --symlink-install # Use symlink install for development
    echo "${green}ros2_ws created and initial build done.${reset}"
fi

# Add sourcing the workspace setup to rc file if not already present
if ! grep -q "source \$HOME/ros2_ws/install/setup.bash" "$rc_file"; then
    echo "source \$HOME/ros2_ws/install/setup.bash" >> "$rc_file"
    echo "${green}Added ros2_ws setup sourcing to $rc_file${reset}"
fi


# -------------------------------------------
# Copy MARIO packages to ROS 2 workspace
# -------------------------------------------
echo "${blue}======================${reset}"
echo "Setting up MARIO packages in ros2_ws"
echo "${blue}======================${reset}"

cd "$HOME/ros2_ws/src"
# Check if one of the folders already exists as a proxy
if [[ ! -d "1_chatter_listener" ]]; then
    echo "Copying MARIO's ROS folders to ros2_ws/src..."
    cp -r "$HOME/MARIO"/1_* "$HOME/ros2_ws/src"
    cp -r "$HOME/MARIO"/2_* "$HOME/ros2_ws/src"
    cp -r "$HOME/MARIO"/3_* "$HOME/ros2_ws/src"
    cp -r "$HOME/MARIO"/4_* "$HOME/ros2_ws/src"
    cp -r "$HOME/MARIO"/activities "$HOME/ros2_ws/src"
    echo "${green}MARIO ROS folders copied.${reset}"
else
    echo "${green}MARIO ROS folders appear to be already copied.${reset}"
fi

# --- Start: Updated Firmware Handling ---
echo "${blue}======================${reset}"
echo "Setting up MARIO firmware workspace"
echo "${blue}======================${reset}"
if [[ ! -d "$HOME/ros2_ws_firmware" ]]; then
    echo "Creating ros2_ws_firmware and copying firmware files..."
    mkdir -p "$HOME/ros2_ws_firmware/components"
    cp -r "$HOME/MARIO/firmware/1_"* "$HOME/ros2_ws_firmware"
    cp -r "$HOME/MARIO/firmware/2_"* "$HOME/ros2_ws_firmware"
    cp -r "$HOME/MARIO/firmware/3_"* "$HOME/ros2_ws_firmware"
    cp -r "$HOME/MARIO/firmware/4_"* "$HOME/ros2_ws_firmware"
    cp -r "$HOME/MARIO/firmware/components/sra-board-component" "$HOME/ros2_ws_firmware/components/"
    echo "${green}Firmware copied to ros2_ws_firmware.${reset}"
else
    echo "${green}Firmware directory $HOME/ros2_ws_firmware already exists.${reset}"
    # Optionally copy components again if needed, or assume it's okay
    if [ -d "$HOME/MARIO/firmware/components/sra-board-component" ] && [ ! -d "$HOME/ros2_ws_firmware/components/sra-board-component" ]; then
        echo "Copying sra-board-component..."
        cp -r "$HOME/MARIO/firmware/components/sra-board-component" "$HOME/ros2_ws_firmware/components/"
        echo "${green}sra-board-component copied.${reset}"
    fi
fi

# Clone micro_ros_espidf_component if not present
echo "${blue}Checking micro_ros_espidf_component...${reset}"
if [ -d "$HOME/ros2_ws_firmware/components" ]; then
    cd "$HOME/ros2_ws_firmware/components"
    if [ ! -d "micro_ros_espidf_component" ]; then
        echo "Cloning micro_ros_espidf_component..."
        git clone --recursive -b humble https://github.com/micro-ROS/micro_ros_espidf_component.git
        echo "${green}micro_ros_espidf_component cloned.${reset}"
    else
        echo "${green}micro_ros_espidf_component already exists.${reset}"
    fi
else
    echo "${red}Error: $HOME/ros2_ws_firmware/components directory not found. Cannot clone micro_ros_espidf_component.${reset}"
fi
# --- End: Updated Firmware Handling ---

# Return to ROS 2 workspace source directory for agent cloning
cd "$HOME/ros2_ws/src"

# -------------------------------------------
# Setting up microROS Agent
# -------------------------------------------
echo "${blue}======================${reset}"
echo "Setting up microROS Agent in ros2_ws/src"
echo "${blue}======================${reset}"

# --- Kept original existence check ---
if [ ! -d "micro-ROS-Agent" ]; then
    echo "Cloning micro-ROS-Agent..."
    git clone -b humble https://github.com/micro-ROS/micro-ROS-Agent.git
    echo "${green}micro-ROS-Agent cloned.${reset}"
else
    echo "${green}micro-ROS-Agent directory already exists. Skipping clone.${reset}"
fi

# -------------------------------------------
# Install Dependencies and Build Workspace
# -------------------------------------------
echo "${blue}======================${reset}"
echo "Installing dependencies and building the workspace"
echo "${blue}======================${reset}"

cd "$HOME/ros2_ws"

# Install Python dependencies (idempotent)
pip3 install -q catkin_pkg lark-parser colcon-common-extensions

# --- Kept original crucial rosdep step ---
echo "Running rosdep install..."
rosdep install --from-paths src --ignore-src -y

echo "Building the workspace with colcon..."
# Use --symlink-install for easier development iteration
colcon build --symlink-install

echo "${green}======================${reset}"
echo "Installation and setup completed successfully!"
# --- Kept original $rc_file logic ---
echo "Please restart your terminal or run 'source $rc_file' to apply changes."
echo "${green}======================${reset}"
