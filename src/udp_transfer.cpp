#include "../include/com_master/udp_transfer.h"

QHostAddress ROBOT_IP = QHostAddress("192.168.188.100");
QHostAddress OPERATOR_IP = QHostAddress("192.168.188.253");
QHostAddress VELODYNE_PC_IP = QHostAddress("192.168.188.99");

UdpTransfer::UdpTransfer(CommunicationMaster* comMaster) : comMaster(comMaster)
{
  ROS_INFO("[UDP] Starting UDP.");
  bool result =
      connect(comMaster, SIGNAL(controlMsgBoolDataSignal(QByteArray)), this, SLOT(controlMsgBoolDataSlot(QByteArray)));
  std::cout << result << std::endl;
}

UdpTransfer::~UdpTransfer()
{
  ROS_INFO("[UDP] Ending UDP.");
}

void UdpTransfer::controlMsgBoolDataSlot(QByteArray bool_data)
{
}