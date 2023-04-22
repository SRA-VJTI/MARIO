#!/usr/bin/env bash

set -e

red=$(tput setaf 1)
green=$(tput setaf 2)
reset=$(tput sgr0)

ros_distro='noetic'

echo $ros_distro
pkg=ros-$ros_distro-desktop-full
shell="${SHELL#${SHELL%/*}/}"
user=$(whoami)

function install_mambaforge() {
    if command -v mamba &>/dev/null; then
        echo "Mambaforge is already installed"
    else
        echo "Installing Mambaforge"
        # Change the download link to the latest version
        wget -q https://github.com/conda-forge/miniforge/releases/latest/download/Mambaforge-$(uname)-$(uname -m).sh -O mambaforge.sh
        bash mambaforge.sh -b
        rm mambaforge.sh
        echo "Mambaforge installed"
        echo "Initializing Mambaforge"
        # Add Mambaforge to the PATH
        export PATH="$HOME/mambaforge/bin:$PATH"
        # Initialize Mambaforge
        mamba init --all
        echo "Mambaforge initialized. Please re-run the installation script for further configuration"
        exit 0
    fi
}

function install() {
    install_mambaforge
    export CONDA_ALWAYS_YES="true"
    conda install -y mamba -c conda-forge

    mamba create -n ros_env python=3.9 -c conda-forge
    conda activate ros_env && conda config --env --add channels conda-forge && conda config --env --add channels robostack-staging
    conda config -n ros_env --env --remove channels defaults
    mamba install -n ros_env -y ros-noetic-desktop-full ros-noetic-effort-controllers ros-noetic-rosserial-python compilers cmake pkg-config make ninja catkin_tools rosdep
    unset CONDA_ALWAYS_YES
    conda activate ros_env && rosdep init && rosdep update
}

function configure() {

    set +e
    conda list -n ros_env $pkg &>/dev/null
    if [ $? -eq 0 ]; then
        echo "$green Successfully installed $pkg $reset"
        exit 1
    else
        echo "$red $pkg is not installed in the Conda environment. Installing. $reset"
        install
    fi

    conda activate ros_env && rosdep update
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
    conda activate ros_env && catkin_make
    source $HOME/catkin_ws/devel/setup.bash
}

configure

echo "${green}======================"
echo "${green}Installed & Configured"
echo "${green}======================"
exit
