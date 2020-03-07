#### check if directory catkin_ws exists, and take necessary actions #######
cd $HOME
if [ -d "$HOME/catkin_ws" ]
then
    echo -e "\e[101mDirectory $HOME/catkin_ws/ already EXISTS.\e[49m" 
    read -p "Press Y to DELETE the folder, N to EXIT the setup: " optionvar 	
    
    if [ "$optionvar" == "Y" ] || [ "$optionvar" == "y" ]
    then
        echo -e "\e[101mREMOVING $HOME/catkin_ws/\e[49m" 
		rm -r -f $HOME/catkin_ws/
    else
	exit 9999
    fi
fi

echo -e "\e[42mCreating directory $HOME/catkin_ws\e[49m"
mkdir -p $HOME/catkin_ws/src
#############################################################################

#### catkin make ############################################################
cd ~/catkin_ws/
catkin_make
#############################################################################

#### source devel/setup.bash ################################################
echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc
source ~/.bashrc
#############################################################################

#### To make sure your workspace is properly overlayed by setup script ######
echo -e "\e[42m$ROS_PACKAGE_PATH\e[49m"
#############################################################################

#### Create package named sra ###############################################
cd ~/catkin_ws/src
catkin_create_pkg sra std_msgs rospy roscpp
#############################################################################

#### catkin make ############################################################
cd ~/catkin_ws
catkin_make
. ~/catkin_ws/devel/setup.bash
#############################################################################

#### copying codes ##########################################################
echo -e "\e[42mCopying msg scripts cmakelists package\e[49m"
if [ -e "$HOME/catkin_ws/src/sra/CMakeLists.txt" ]
then
	rm -r -f $HOME/catkin_ws/src/sra/CMakeLists.txt
fi
if [ -e "$HOME/catkin_ws/src/sra/package.xml" ]
then
	rm -r -f $HOME/catkin_ws/src/sra/package.xml
fi
cp -r $HOME/ros20_ws/src/sra20/requirements_catkin_ws/msg/ $HOME/catkin_ws/src/sra/
cp -r $HOME/ros20_ws/src/sra20/requirements_catkin_ws/scripts/ $HOME/catkin_ws/src/sra/
cp -r $HOME/ros20_ws/src/sra20/requirements_catkin_ws/CMakeLists.txt $HOME/catkin_ws/src/sra/
cp -r $HOME/ros20_ws/src/sra20/requirements_catkin_ws/package.xml $HOME/catkin_ws/src/sra/
#############################################################################

#### Success message ########################################################
clear
if [ -d $HOME/catkin_ws/src/sra/scripts ] && [ -e $HOME/catkin_ws/src/sra/package.xml ]
then
	echo -e "\e[42mSuccessful\e[49m"
fi
#############################################################################