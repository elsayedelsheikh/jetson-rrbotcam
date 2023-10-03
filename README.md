# jetson-rrbotcam


docker/run.sh --ros humble ros2 launch ros_deep_learning video_viewer.ros2.launch input:=csi://0 output:=webrtc://@:8554/output