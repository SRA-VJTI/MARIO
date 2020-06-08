#/bin/sh

#### check if rosserial is installed ########################################
dpkg -s "ros-kinetic-rosserial" &> /dev/null
if [ $? -eq 0 ] 
then
    echo -e "\e[42mrosserial is INSTALLED!\e[49m"
else
    echo -e "\e[101mrosserial is NOT INSTALLED!\e[49m"
    echo -e "\e[101mINSTALLING rosserial!\e[49m"
    sudo apt install ros-kinetic-rosserial
fi
#############################################################################

### clone code repository ###################################################
if [ -d "$HOME/ros20_workshop_codes" ]
then
    echo -e "\e[101mdirectory $HOME/ros20_workshop_codes/ already EXISTS.\e[49m" 
    read -p "Press [Y]es to DELETE the folder, [N]o to EXIT the setup: " optionvar 	
    
    if [ "$optionvar" == "Yes" ] || [ "$optionvar" == "yes" ]
    then
        echo -e "\e[101mREMOVING $HOME/ros20_workshop_codes/\e[49m" 
	    rm -rf $HOME/ros20_workshop_codes
    else
	    exit 9999
    fi
fi

cd $HOME
git clone https://github.com/SRA-VJTI/ROS-Workshop-2.1.git ros20_workshop_codes
#############################################################################

#### create ros20_ws ########################################################
echo -e "\e[42mcreating directory $HOME/ros20_workshop_codes/ros20_ws/src\e[49m"
mkdir -p $HOME/ros20_workshop_codes/ros20_ws/src
#############################################################################

#### catkin make ############################################################
cd $HOME/ros20_workshop_codes/ros20_ws
catkin_make
#############################################################################

#### copy ros codes in $ROS_WORKSPACE/src ##################################
cp $HOME/ros20_workshop_codes/ros_codes $HOME/ros20_workshop_codes/ros20_ws/src -r
mv $HOME/ros20_workshop_codes/ros20_ws/src/ros_codes $HOME/ros20_workshop_codes/ros20_ws/src/sra20 
#############################################################################

#### catkin make and add source command to bashrc ###########################
cd $HOME/ros20_workshop_codes/ros20_ws
catkin_make	

source $HOME/ros20_workshop_codes/ros20_ws/devel/setup.bash
echo "source $HOME/ros20_workshop_codes/ros20_ws/devel/setup.bash" >> $HOME/.bashrc

cd $HOME
############################################################################

#### check if everything is installed correctly ############################	
if [ -d "$HOME/ros20_workshop_codes" ] && [ -d "$HOME/ros20_workshop_codes/ros20_ws/src/sra20" ]
then
    clear 
    echo -e "\e[42mall files INSTALLED correctly\e[49m"
else
    
    echo -e "\e[101mall files NOT INSTALLED correctly, rerun the script\e[49m"
fi
############################################################################
