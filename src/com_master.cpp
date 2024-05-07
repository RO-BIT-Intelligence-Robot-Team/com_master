#include "../include/com_master/com_master.h"
#include "../include/com_master/udp_transfer.h"

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

int main(int argc, char** argv)
{
  ros::init(argc, argv, "robot_udp_communication_master_node");
  ros::NodeHandle nh;

  ros::Rate loop_rate(100);

  CommunicationMaster ComMaster;
  UdpTransfer udpMaster(&ComMaster);

  while (ros::ok())
  {
    ComMaster.test();
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}

CommunicationMaster::CommunicationMaster()
{
  ROS_INFO("[COM] Starting Robot Communication Node.");
}

CommunicationMaster::~CommunicationMaster()
{
  ROS_INFO("[COM] Closing Communication Node.");
}

void CommunicationMaster::test()
{
  QByteArray bool_data, flipper_data, rpm_data;
  bool_data.append(false);
  emit controlMsgBoolDataSignal(bool_data);
}
