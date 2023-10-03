ARG ROS_DISTRO="humble"
ARG BRANCH="humble"
FROM ros:$ROS_DISTRO

ENV ROS_UNDERLAY /root/ws_ros2_control/install
WORKDIR $ROS_UNDERLAY/../src

## add packages
ADD https://raw.githubusercontent.com/ros-controls/ros2_control/$BRANCH/ros2_control.$ROS_DISTRO.repos ros2_control.repos
COPY rrbot_cam ./rrbot_cam
RUN vcs import < ros2_control.repos

## install dependencies
RUN apt-get update && \
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

