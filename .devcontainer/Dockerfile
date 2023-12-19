ARG ROS_DISTRO="humble"
ARG USERNAME=ros
FROM althack/ros2:$ROS_DISTRO-dev 

ENV DEBIAN_FRONTEND=noninteractive

# Use Cyclone DDS as middleware
# Install foxglove-bridge for remote visualization
RUN apt-get update && apt-get install -y --no-install-recommends \
        ros-${ROS_DISTRO}-rmw-cyclonedds-cpp \
        ros-${ROS_DISTRO}-foxglove-bridge

ENV RMW_IMPLEMENTATION=rmw_cyclonedds_cpp

## install moveit2 binaries
RUN apt-get update \
   && apt-get -y install --no-install-recommends \
   ros-$ROS_DISTRO-moveit \
   ros-$ROS_DISTRO-moveit-planners* \
   ros-$ROS_DISTRO-moveit-ros-move-group \
   ros-$ROS_DISTRO-moveit-ros-control* \
   ros-$ROS_DISTRO-joy \
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

## install dependencies
RUN apt-get update \
   && apt-get -y install --no-install-recommends \
   libserial-dev \
   ros-$ROS_DISTRO-joint-state-publisher-gui \
   ros-$ROS_DISTRO-vision-msgs \
   ros-$ROS_DISTRO-cv-bridge \
   ros-$ROS_DISTRO-ros2-controllers-test-nodes \
   # Clean up
   && apt-get autoremove -y \
   && apt-get clean -y \
   && rm -rf /var/lib/apt/lists/*

## Add user to dialout group to access serial ports
RUN groupadd -f dialout && usermod -aG dialout ros

ENV DEBIAN_FRONTEND=dialog

# Set up auto-source of workspace for ros user
ARG WORKSPACE
RUN echo "if [ -f ${WORKSPACE}/install/setup.bash ]; then source ${WORKSPACE}/install/setup.bash; fi" >> /home/ros/.bashrc