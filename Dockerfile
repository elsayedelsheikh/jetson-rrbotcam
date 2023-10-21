ARG ROS_DISTRO="humble"
FROM ros:$ROS_DISTRO
ARG BRANCH="humble"

ENV ROS_UNDERLAY /root/ws_ros2_control/install
WORKDIR $ROS_UNDERLAY/../src

## add packages
ADD https://raw.githubusercontent.com/ros-controls/ros2_control/$BRANCH/ros2_control.$ROS_DISTRO.repos ros2_control.repos
RUN vcs import < ros2_control.repos
COPY src/rrbot_cam ./rrbot_cam
COPY src/rrbot_cam_msgs ./rrbot_cam_msgs
COPY src/rrbot_cam_platform_controller ./rrbot_cam_platform_controller

## install dependencies
RUN apt-get update && \
    apt install ros-${ROS_DISTRO}-foxglove-bridge && \
    rosdep update && \
    rosdep install -iy --from-paths . && \
    rm -rf /var/lib/apt/lists/

## compile
RUN cd $ROS_UNDERLAY/.. && \
        . /opt/ros/${ROS_DISTRO}/setup.sh && \
        colcon build

## source entrypoint setup
RUN sed --in-place --expression \
      '$isource "$ROS_UNDERLAY/setup.bash"' \
      /ros_entrypoint.sh

