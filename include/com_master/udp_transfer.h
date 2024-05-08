// udp_transfer.h

#ifndef UDP_TRANSFER_H
#define UDP_TRANSFER_H

#include <ros/ros.h>
#include <iostream>
#include "com_master.h"
#include <QObject>
#include <QByteArray>
#include "udp/udp.h"

class UdpTransfer : public QObject
{
  Q_OBJECT
public:
  UdpTransfer(CommunicationMaster* comMaster);
  ~UdpTransfer();

public slots:
  void controlMsgBoolDataSlot(QByteArray bool_data);
  void joyMsgDataSlot(QByteArray joy_data);

public Q_SLOTS:
  void mainImageSlot();

private:
  CommunicationMaster* comMaster;
  udp::UDP* udpInstance = nullptr;

  QUdpSocket* joy_socket;
  QUdpSocket* main_img_socket;
};

#endif
