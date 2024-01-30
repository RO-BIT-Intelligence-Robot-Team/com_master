#include "../include/com_master/com_master.h"

// uint16_t camera_request_PORT = 8888;  // tx
// uint16_t cam1_PORT = 8881;            // rx
// uint16_t cam2_PORT = 8882;            // rx
// uint16_t cam3_PORT = 8883;            // rx
// uint16_t cam4_PORT = 8884;            // rx
// uint16_t cam5_PORT = 8885;            // rx
// uint16_t cam6_PORT = 8886;            // rx

// uint16_t communication_status_PORT = 4444;  // rx, tx
// uint16_t mobile_base_PORT = 1111;           // rx,tx
// uint16_t flipper_PORT = 2222;               // rx, tx
// uint16_t manipulator_PORT = 3333;           // rx, tx
// uint16_t robot_status_PORT = 5555;          // rx

// uint16_t realsense1_PORT = 7771;  // rx
// uint16_t realsense2_PORT = 7772;  // rx
// uint16_t realsense3_PORT = 7773;  // rx
// uint16_t realsense4_PORT = 7774;  // rx

// uint16_t velodyne_PORT = 6666;
// uint16_t SLAM_PORT = 6665;

QHostAddress ROBOT_IP = QHostAddress("192.168.188.100");
QHostAddress OPERATOR_IP = QHostAddress("192.168.188.253");

int main(int argc, char** argv)
{
  ros::init(argc, argv, "robot_udp_communication_master");
  ros::NodeHandle nh;

  ROS_INFO("[COM] Starting Robot Communication Node.");

  ros::Rate loop_rate(100);
  while (ros::ok())
  {
    ros::spinOnce();
    loop_rate.sleep();
  }
  ROS_INFO("[COM] Closing Communication Node.");
  return 0;
}

// Current Robot Status Update Fuction.
void robotControlMsgCallBack(const mobile_base_msgs::RobotControl::ConstPtr& msg)
{
  ROS_INFO("[COM] Recieved Control Message.");
  mobile_base_msgs::RobotCommunication pub_msg;

  // Mobile Base Status Update.
  mobile_base_status_instance.init_trigger = msg->init_trigger;
  mobile_base_status_instance.auto_flipper = msg->flipper_control.flipper_auto;
  for (int i = 0; i < 4; i++)
  {
    mobile_base_status_instance.flipper_target_position[i] = msg->flipper_control.flipper_target_position[i];
    mobile_base_status_instance.flipper_current[i] = msg->flipper_control.flipper_current[i];
    mobile_base_status_instance.flipper_speed[i] = msg->flipper_control.flipper_speed[i];
  }
  mobile_base_status_instance.RPM[0] = msg->L_RPM;
  mobile_base_status_instance.RPM[1] = msg->R_RPM;

  // Image Transport Status Update.
  for (int i = 0; i < NUM_OF_CAMERA; i++)
  {
    camera_status_instance.transport_status[i] = msg->image_transport_status[i];
  }
  camera_status_instance.command = msg->camera_request;

  // Realsense Transport Status Update.
  for (int i = 0; i < NUM_OF_REALSENSE; i++)
  {
    realsense_status_instance.transport_status[i] = msg->realsense_transport_status[i];
  }
}
