# jetson-rrbotcam
Control a camera platform (2DOF Revolute-Revolute Joints Robot) using camera feed to follow object.
Using 
Hardware:
* Jetson nano
* Arduino
* 2x Servos
* CSI Camera
Software:
* ROS2 humble
* Docker container

## Setup
``` bash
git clone --recursive --depth=1 https://github.com/elsayedelsheikh/jetson-rrbotcam
```
## Project
This project is divided into 3 main parts:
* `bringup_robot` to communicate with the Arduino & control the hardware (2x Servos)
* `object_detector` to fire up the camera and detect the object to follow using various computer vision techniques (HSV, Deep learning)
* `object_follower` to control the hardware to follow the object centroid (x,y) using PID controller
## bringup_robot 
* Uses `ros_arduino_bridge` to communicate with the Arduino through USB-Serial port
* Uses `ros2_control` to control the 2x Servos positions (Command & State interface) with custom Hardware interface
## object_detector
* Uses [ros-deep-learning](https://github.com/dusty-nv/ros_deep_learning) package to fire up the camera 
Multiple detectors are available:
* HSV detector node to detect a specific color range
* detectnet node to detect a specific object using deep learning models (SSD-Mobilenet by default) from [jetson-inference](https://github.com/dusty-nv/jetson-inference)
### Future work
* Track a person while removing the background
  
