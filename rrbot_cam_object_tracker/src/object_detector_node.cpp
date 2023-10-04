#include <memory>

#include "rrbot_cam_object_tracker/ObjectDetector.hpp"

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);

  auto node_detector =
      std::make_shared<rrbot_cam_object_tracker::ObjectDetector>();
  rclcpp::spin(node_detector);
  rclcpp::shutdown();
  return 0;
}