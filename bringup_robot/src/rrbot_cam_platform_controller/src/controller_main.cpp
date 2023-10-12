#include "rclcpp/rclcpp.hpp"
#include "rrbot_cam_platform_controller/PlatfromController.hpp"

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<rrbot_cam_platform_controller::PlatfromController>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
