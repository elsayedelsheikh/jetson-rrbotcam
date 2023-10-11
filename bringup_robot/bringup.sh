#!/usr/bin/env bash
docker run -itd --rm --network host --name rrbotcam_bringup_robot --device /dev/ttyUSB0 elsayedelsheikh/jetson-rrbotcam-bringup-robot:latest ros2 launch rrbot_cam rrbot.launch.py