#include "rrbot_cam_object_follower/ObjectFollower.hpp"

namespace rrbot_cam_object_follower {

ObjectFollower::ObjectFollower() : Node("object_follower") {
  declare_parameter("image_width", IMG_WIDTH);
  declare_parameter("image_heigh", IMG_HEIGHT);

  get_parameter("image_width", IMG_WIDTH);
  get_parameter("image_height", IMG_HEIGHT);

  detected_object_sub_ = create_subscription<vision_msgs::msg::Detection2D>(
      "detection", rclcpp::SensorDataQoS(),
      std::bind(&ObjectFollower::detected_object_cb, this,
                std::placeholders::_1));

  command_pub_ =
      create_publisher<rrbot_cam_msgs::msg::PanTiltCommand>("command", 10);
}

void ObjectFollower::detected_object_cb(
    const vision_msgs::msg::Detection2D::ConstSharedPtr &msg) {
  rrbot_cam_msgs::msg::PanTiltCommand cmd_msg;
  // *2 to get range from 0 to 2, -1 to get range from -1 to 1
  cmd_msg.pan = (msg->bbox.center.position.x / IMG_WIDTH) * 2 - 1;
  cmd_msg.tilt = (msg->bbox.center.position.y / IMG_HEIGHT) * 2 - 1;
  command_pub_->publish(cmd_msg);
  
}

}  // namespace rrbot_cam_object_follower