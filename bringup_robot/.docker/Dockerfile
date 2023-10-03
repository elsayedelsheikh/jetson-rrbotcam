ARG ROS_DISTRO="humble"
FROM ros:$ROS_DISTRO
ARG BRANCH="humble"

ENV ROS_UNDERLAY /root/ws_ros2_control/install
WORKDIR $ROS_UNDERLAY/../src

ADD https://raw.githubusercontent.com/ros-controls/ros2_control/$BRANCH/ros2_control.$ROS_DISTRO.repos ros2_control.repos

## Add Package
RUN echo "  elsayedelsheikh/rrbot_cam:" >> ros2_control.repos
RUN echo "    type: git" >> ros2_control.repos
RUN echo "    url: https://github.com/elsayedelsheikh/rrbot_cam.git" >> ros2_control.repos
RUN echo "    version: main" >> ros2_control.repos
RUN vcs import < ros2_control.repos

RUN apt-get update && \
    tmux && \
    rosdep update && \
    rosdep install -iy --from-paths . && \
    rm -rf /var/lib/apt/lists/

RUN cd $ROS_UNDERLAY/.. && \
        . /opt/ros/${ROS_DISTRO}/setup.sh && \
        colcon build

# source entrypoint setup
RUN sed --in-place --expression \
      '$isource "$ROS_UNDERLAY/setup.bash"' \
      /ros_entrypoint.sh

