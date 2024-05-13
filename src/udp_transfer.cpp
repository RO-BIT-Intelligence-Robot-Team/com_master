#include "../include/com_master/udp_transfer.h"

UdpTransfer::UdpTransfer(CommunicationMaster* comMaster) : comMaster(comMaster)
{
  ROS_INFO("[UDP] Starting UDP.");
  udpInstance = new udp::UDP;

  joy_socket = new QUdpSocket(this);
  main_img_socket = new QUdpSocket(this);

  if (main_img_socket->bind(udpInstance->OPERATOR_IP, udpInstance->cam1_PORT));
  {
    connect(main_img_socket, SIGNAL(readyRead()), this, SLOT(mainImageSlot()));
  }

  connect(comMaster, SIGNAL(controlMsgBoolDataSignal(QByteArray)), this, SLOT(controlMsgBoolDataSlot(QByteArray)));
  connect(comMaster, SIGNAL(joyDataSignal(QByteArray)), this, SLOT(joyMsgDataSlot(QByteArray)));
}

UdpTransfer::~UdpTransfer()
{
  ROS_INFO("[UDP] Ending UDP.");
  delete joy_socket;
}

void UdpTransfer::controlMsgBoolDataSlot(QByteArray bool_data)
{
}

void printHex(const QByteArray& data)
{
  for (int i = 0; i < data.size(); ++i)
  {
    std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data.at(i)) << " ";
  }
  std::cout << std::endl;
}

void UdpTransfer::joyMsgDataSlot(QByteArray joy_data)
{
  udpInstance->UdpArrayTransfer(joy_data, udpInstance->mobile_base_PORT, udpInstance->ROBOT_IP, *joy_socket);
}

void UdpTransfer::mainImageSlot()
{
  cv::Mat img;
  img = udpInstance->MatImgRcv(img, udpInstance->cam1_PORT, udpInstance->OPERATOR_IP, *main_img_socket);
  
}
