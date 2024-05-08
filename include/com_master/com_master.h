#ifndef COM_MASTER_H
#define COM_MASTER_H

#include <ros/ros.h>
#include <iostream>
#include <QTimer>

#include <std_msgs/Bool.h>
#include <sensor_msgs/Image.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Point.h>

#include "mobile_base_msgs/STMtx.h"
#include "mobile_base_msgs/RobotCommunication.h"
#include "mobile_base_msgs/RobotControl.h"
#include "mobile_base_msgs/RobotState.h"
// #include "mobile_base_msgs/Flipper.h"
#include "mobile_base_msgs/Manipulator.h"
#include "mobile_base_msgs/STMtx.h"
#include "mobile_base_msgs/STMrx.h"

#include <opencv2/opencv.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/imgcodecs.hpp"
#include "image_transport/image_transport.h"

#define IMAGE_WIDTH 1080
#define IMAGE_HEIGHT 720

#define NUM_OF_CAMERA 6     // MAX 10
#define NUM_OF_REALSENSE 4  // MAX 4

struct communication_check
{
  bool connection = false;
  int check_cnt = 0;
};

struct mobile_base_status
{
  bool init_trigger = false;  // robotControlMsgCallBack
  bool robot_init = false;

  bool stm_connection = false;

  bool auto_flipper = false;  // robotControlMsgCallBack

  float flipper_current[4] = {
    0,
  };  // robotControlMsgCallBack

  float flipper_target_position[4] = {
    0,
  };  // robotControlMsgCallBack

  float flipper_speed[4] = {
    0,
  };  // robotControlMsgCallBack

  float flipper_acc[4] = {
    0,
  };  // robotControlMsgCallBack

  bool flipper_init_status[4] = { false, false, false, false };

  float RPM[2] = {
    0,
  };  // robotControlMsgCallBack

  float battery[4] = {
    0,
  };
};

struct manipulator_status
{
};

struct camera_status
{
  bool transport_status[NUM_OF_CAMERA];  // robotControlMsgCallBack
  float fps[NUM_OF_CAMERA] = {
    0,
  };

  float bps[NUM_OF_CAMERA] = {
    0,
  };

  std::string command;  // robotControlMsgCallBack
};

struct realsense_status
{
  bool transport_status[NUM_OF_REALSENSE];  // robotControlMsgCallBack
  float fps[NUM_OF_REALSENSE] = {
    0,
  };

  float bps[NUM_OF_REALSENSE] = {
    0,
  };
};

class CommunicationMaster : public QObject
{
  Q_OBJECT

public:
  CommunicationMaster(int argc, char** argv);
  ~CommunicationMaster();

  // Subscribers
  ros::Subscriber subscriber_joy;

  // Publishers
  ros::Publisher publisher_robot_state;
  ros::Publisher publisher_udp_image_main;

  // Topic Callbacks
  void joyDataCallback(const mobile_base_msgs::STMtx::ConstPtr& msg);
  void robotControlMsgCallBack(const mobile_base_msgs::RobotControl::ConstPtr& msg);

private:
  int init_argc;
  char** init_argv;

  int init();

  communication_check communication_check_instance;
  mobile_base_status mobile_base_status_instance;
  camera_status camera_status_instance;
  realsense_status realsense_status_instance;
  QTimer *_5ms_Timer, *_6ms_Timer, *_1s_Timer, *_1ms_Timer;

signals:
  void controlMsgBoolDataSignal(QByteArray bool_data);
  void joyDataSignal(QByteArray joy_data);
};

#endif
