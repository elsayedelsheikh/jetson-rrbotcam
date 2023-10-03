#!/usr/bin/env bash
docker run -it --rm --network host --name rrbotcam_bringup --device /dev/ttyUSB0 elsayedelsheikh/jetson-rrbotcam-bringup-robot:latest ros2 launch rrbot_cam rrbot.launch.py