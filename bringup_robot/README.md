# bringup_robot
## Setup
### Arduino
You need to upload the sketch in ros_arduino_bridge/ROSArduinoBridge/ROSArduinoBridge.ino to the arduino
### Docker
You don't need to build the image you can pull it directly on your jetson nano from docker hub
``` bash
docker pull elsayedelsheikh/jetson-rrbotcam-bringup-robot:latest
```
## Build the image
If you're going to build the image on a jetson nano you need to copy the Dockerfile to bringup_robot/src and build it there because ADD command in Dockerfile can't access files outside the build context
## Run the container
* To run the container you need to run the following command inside the bringup_robot directory (this directory)
* you need to have arduino connected to the jetson nano through USB-Serial port, in this case the arduino is connected to /dev/ttyUSB0 
* It would start a container with the name rrbotcam_bringup_robot with network host and share the /dev/ttyUSB0 with the container in the background and it would be removed when you exit the container
``` bash
#!/usr/bin/env bash
docker run -itd --rm --network host --name rrbotcam_bringup_robot --device /dev/ttyUSB0 elsayedelsheikh/jetson-rrbotcam-bringup-robot:latest 
ros2 launch rrbot_cam rrbot.launch.py
ros2 run rrbot_cam_platform_controller platform_controller  --ros-args -r /joint_trajectory:=/joint_trajectory_position_controller/joint_trajectory -r /joint_state:=/joint_trajectory_position_controller/state
```
docker exec -it rrbotcam_bringup_robot /bin/bash
ros2 control list_controllers -v 

ros2 control load_controller joint_trajectory_position_controller
ros2 control set_controller_state joint_trajectory_position_controller inactive

ros2 control switch_controllers --deactivate forward_position_controller --activate joint_trajectory_position_controller

ros2 lifecycle nodes
ros2 lifecycle get /platform_controller
ros2 lifecycle list /platform_controller
ros2 lifecycle set /platform_controller activate