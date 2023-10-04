#include "rrbot_cam_object_tracker/ObjectDetector.hpp"

#include "cv_bridge/cv_bridge.h"
#include "opencv2/opencv.hpp"

namespace rrbot_cam_object_tracker {

ObjectDetector::ObjectDetector() : Node("object_detector") {
  declare_parameter("hsv_ranges", hsv_ranges_);
  declare_parameter("debug", debug_);

  get_parameter("hsv_rangs", hsv_ranges_);
  get_parameter("debug", debug_);

  image_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
      "input_image", rclcpp::SensorDataQoS(),
      std::bind(&ObjectDetector::image_callback, this, std::placeholders::_1));

  detected_object_pub_ = this->create_publisher<vision_msgs::msg::Detection2D>(
      "output_detection", 10);
}

void ObjectDetector::image_callback(
    const sensor_msgs::msg::Image::ConstSharedPtr &img) {
  // Check if there's any subscribers on output_detection topic
  if (detected_object_pub_->get_subscription_count() == 0) return;

  const double &h = hsv_ranges_[0];
  const double &H = hsv_ranges_[1];
  const double &s = hsv_ranges_[2];
  const double &S = hsv_ranges_[3];
  const double &v = hsv_ranges_[4];
  const double &V = hsv_ranges_[5];

  // Convert image msg to openCV image
  cv_bridge::CvImagePtr cv_ptr;
  try {
    cv_ptr = cv_bridge::toCvCopy(img, sensor_msgs::image_encodings::BGR8);
  } catch (cv_bridge::Exception &e) {
    RCLCPP_INFO(get_logger(), "cv_bridge error: %s", e.what());
    return;
  }

  // Convert to HSV
  cv::Mat img_hsv;
  cv::cvtColor(cv_ptr->image, img_hsv, cv::COLOR_BGR2HSV);

  // Check if it's within range
  cv::Mat1b filtered;
  cv::inRange(img_hsv, cv::Scalar(h, s, v), cv::Scalar(H, S, V), filtered);

  // Get center
  cv::Rect bbox = cv::boundingRect(filtered);
  auto m = cv::moments(filtered, true);

  if (m.m00 < 0.000001) return;

  int cx = m.m10 / m.m00;
  int cy = m.m01 / m.m00;

  // Publish the message
  vision_msgs::msg::Detection2D detection_msg;
  detection_msg.header = img->header;
  detection_msg.bbox.size_x = bbox.width;
  detection_msg.bbox.size_y = bbox.height;
  detection_msg.bbox.center.position.x = cx;
  detection_msg.bbox.center.position.y = cy;

  detected_object_pub_->publish(detection_msg);
}

}  // namespace rrbot_cam_object_tracker