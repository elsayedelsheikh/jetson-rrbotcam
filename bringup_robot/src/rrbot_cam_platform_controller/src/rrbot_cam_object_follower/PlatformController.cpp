#include "rrbot_cam_platfrom_controller/PlatformController.hpp"

namespace rrbot_cam_platfrom_controller {

PlatformController::PlatformController():
LifecycleNode("platform_controller"),
pan_pid_(0.41, 0.06, 0.53, 0.0, 1.0, 0.0, 0.3), // Kp, Ki, Kd, RefMin, RefMax, OutputMin, OutputMax
tilt_pid_(0.41, 0.06, 0.53, 0.0, 1.0, 0.0, 0.3)
{
  command_sub_ = create_subscription<rrbot_cam_msgs::msg::PanTiltCommand>(
      "command", 10, std::bind(&PlatformController::command_callback, this, std::placeholders::_1));
  
  joint_state_sub_ = create_subscription<control_msgs::msg::JointTrajectoryControllerState>(
      "joint_state", rclcpp::SensorDataQoS(), std::bind(&PlatformController::joint_state_callback, this, std::placeholders::_1));
  
  trajectory_pub_ = create_publisher<trajectory_msgs::msg::JointTrajectory>("joint_trajectory", 10);
}

}  // namespace rrbot_cam_platfrom_controller