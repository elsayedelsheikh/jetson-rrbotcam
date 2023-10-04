# jetson-rrbotcam
## Objective
Control a camera platform (2DOF Revolute-Revolute Joints Robot) using camera feed to follow any specific object.
Using 
* ROS2 humble
* Docker container
* Docker compose
* Jetson nano
## ros2_control 
Arduino communication through USB-Serial port
Custom Hardware interface to control 2x Servos positions (Command & State interface)
## Computer vision
Different Computer vision applications that order the joints to follow any specific item using PID controller
* Certain color using HSV-color range node
* Detection of wide range of classes with different models from jetson-inference nodes
## Future work
* Create Background Removal and follower node
  
