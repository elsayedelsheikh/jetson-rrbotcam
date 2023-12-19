ARG ROS_DISTRO="humble"
FROM althack/ros2:$ROS_DISTRO-dev 

ENV DEBIAN_FRONTEND=noninteractive

ENV ROS_UNDERLAY /ros2_control_ws
WORKDIR $ROS_UNDERLAY/src

# Use Cyclone DDS as middleware
# Install foxglove-bridge for remote visualization
RUN apt-get update && apt-get install -y --no-install-recommends \
        ros-${ROS_DISTRO}-rmw-cyclonedds-cpp \
        ros-${ROS_DISTRO}-foxglove-bridge

ENV RMW_IMPLEMENTATION=rmw_cyclonedds_cpp

## add ros2_control packages
# ADD https://raw.githubusercontent.com/ros-controls/ros2_control/$ROS_DISTRO/ros2_control.$ROS_DISTRO.repos ros2_control.repos
# RUN vcs import < ros2_control.repos
# COPY src/rrbot_cam ./rrbot_cam
# COPY src/rrbot_cam_msgs ./rrbot_cam_msgs
# COPY src/rrbot_cam_platform_controller ./rrbot_cam_platform_controller
# ## install dependencies
# RUN apt-get update \
#     && rosdep update \
#     && rosdep install -iy --from-paths . \
#    # Clean up
#    && apt-get autoremove -y \
#    && apt-get clean -y \
#    && rm -rf /var/lib/apt/lists/*
## compile
# RUN cd $ROS_UNDERLAY \
#     && . /opt/ros/${ROS_DISTRO}/setup.sh \
#     && colcon build --symlink-install

## source entrypoint setup
# RUN sed --in-place --expression \
#       '$isource "$ROS_UNDERLAY/install/setup.bash"' \
#       /ros_entrypoint.sh

## install moveit2 binaries
RUN apt-get update \
   && apt-get -y install --no-install-recommends ros-$ROS_DISTRO-moveit \
   # Clean up
   && apt-get autoremove -y \
   && apt-get clean -y \
   && rm -rf /var/lib/apt/lists/*

## install ros2_control binaries
RUN apt-get update \
   && apt-get -y install --no-install-recommends \
   ros-$ROS_DISTRO-ros2-control \
   ros-$ROS_DISTRO-ros2-controllers \
   ros-$ROS_DISTRO-hardware-interface \
   # Clean up
   && apt-get autoremove -y \
   && apt-get clean -y \
   && rm -rf /var/lib/apt/lists/*



ENV DEBIAN_FRONTEND=dialog

# Set up auto-source of workspace for ros user
ARG WORKSPACE
RUN echo "if [ -f ${WORKSPACE}/install/setup.bash ]; then source ${WORKSPACE}/install/setup.bash; fi" >> /home/ros/.bashrc