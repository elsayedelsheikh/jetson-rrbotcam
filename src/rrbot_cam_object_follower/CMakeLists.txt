cmake_minimum_required(VERSION 3.8)
project(rrbot_cam_object_follower)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rrbot_cam_msgs REQUIRED)
find_package(vision_msgs REQUIRED)

set(dependencies
  rclcpp
  rrbot_cam_msgs
  vision_msgs
)

include_directories(include)

add_executable(object_follower 
  src/rrbot_cam_object_follower/ObjectFollower.cpp
  src/object_follower_main.cpp
)

ament_target_dependencies(object_follower ${dependencies})

install(TARGETS
  object_follower
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
