#include "../include/com_master/udp_transfer.h"

QHostAddress ROBOT_IP = QHostAddress("192.168.188.100");
QHostAddress OPERATOR_IP = QHostAddress("192.168.188.253");
QHostAddress VELODYNE_PC_IP = QHostAddress("192.168.188.99");

void UdpTransfer::controlMsgBoolDataSlot(QByteArray bool_data)
{
  std::cout << "HO" << std::endl;
}