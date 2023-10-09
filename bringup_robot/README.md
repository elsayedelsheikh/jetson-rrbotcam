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
* To run the container you need to run the following command
* you need to have arduino connected to the jetson nano through USB-Serial port, in this case the arduino is connected to /dev/ttyUSB0 
* It would start a container with the name rrbotcam_bringup_robot with network host and share the /dev/ttyUSB0 with the container in the background and it would be removed when you exit the container
``` bash
./run.sh
```