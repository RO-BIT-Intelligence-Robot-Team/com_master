// udp_transfer.h

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
  UdpTransfer(CommunicationMaster* comMaster);
  ~UdpTransfer();

public slots:
  void controlMsgBoolDataSlot(QByteArray bool_data);

private:
  CommunicationMaster* comMaster;
};

#endif
