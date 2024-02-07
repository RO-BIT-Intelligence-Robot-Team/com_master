#ifndef UDP_TRANSFER_H
#define UDP_TRANSFER_H

#include <ros/ros.h>
#include <iostream>
#include "udp/udp.h"
#include "com_master.h"
#include <QObject>
#include <QByteArray>

using namespace udp;

class UdpTransfer : public QObject
{
  Q_OBJECT
public:
private:
  UdpTransfer()
  {
    CommunicationMaster* comMaster = new CommunicationMaster();

    connect(comMaster, SIGNAL(controlMsgBoolDataSignal(QByteArray)), this, SLOT(controlMsgBoolDataSlot(QByteArray)));
  }
  ~UdpTransfer()
  {
    ROS_INFO("[UDP] Ending UDP.");
  }
public slots:
  void controlMsgBoolDataSlot(QByteArray bool_data);
};

#endif