#include "../include/com_master/com_master.h"
#include "../include/com_master/udp_transfer.h"

int main(int argc, char** argv)
{
  CommunicationMaster ComMaster(argc, argv);
}

int CommunicationMaster::init()
{
  UdpTransfer udpMaster(this);

  ros::init(init_argc, init_argv, "operator_udp");
  ros::start();  // explicitly needed since our nodehandle is going out of scope.
  ros::NodeHandle nh;

  subscriber_joy = nh.subscribe("/STM_tx_data", 1, &CommunicationMaster::joyDataCallback, this);

  ros::Rate loop_rate(100);

  while (ros::ok())
  {
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}

CommunicationMaster::CommunicationMaster(int argc, char** argv) : init_argc(argc), init_argv(argv)
{
  ROS_INFO("[COM] Starting Robot Communication Node.");
  init();
}

CommunicationMaster::~CommunicationMaster()
{
  ROS_INFO("[COM] Closing Communication Node.");
}

void CommunicationMaster::joyDataCallback(const mobile_base_msgs::STMtx::ConstPtr& msg)
{
  QByteArray data;
  for (int i = 0; i < 4; i++)
  {
    data.append(reinterpret_cast<const char*>(&msg->flipper_control[i].target_pos), 8);
    mobile_base_status_instance.flipper_target_position[i] = msg->flipper_control[i].target_pos;
  }
  for (int i = 0; i < 4; i++)
  {
    data.append(reinterpret_cast<const char*>(&msg->flipper_control[i].target_vel), 8);
    mobile_base_status_instance.flipper_speed[i] = msg->flipper_control[i].target_vel;
  }
  for (int i = 0; i < 4; i++)
  {
    data.append(reinterpret_cast<const char*>(&msg->flipper_control[i].target_acc), 8);
    mobile_base_status_instance.flipper_acc[i] = msg->flipper_control[i].target_acc;
  }
  for (int i = 0; i < 4; i++)
  {
    data.append(reinterpret_cast<const char*>(&msg->flipper_control[i].init_req), 1);
    mobile_base_status_instance.flipper_init_status[i] = msg->flipper_control[i].init_req;
  }
  data.append(reinterpret_cast<const char*>(&msg->L_control.vel), 8);
  data.append(reinterpret_cast<const char*>(&msg->R_control.vel), 8);
  mobile_base_status_instance.RPM[0] = msg->L_control.vel;
  mobile_base_status_instance.RPM[1] = msg->R_control.vel;
  emit joyDataSignal(data);
}
