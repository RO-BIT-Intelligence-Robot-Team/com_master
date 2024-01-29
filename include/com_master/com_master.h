#ifndef COM_MASTER_H
#define COM_MASTER_H

#include <ros/ros.h>
#include <iostream>
#include "udp.h"

#include <std_msgs/Bool.h>
#include <sensor_msgs/Image.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Point.h>
#include "mobile_base_msgs/RobotCommunication.h"
#include "mobile_base_msgs/RobotControl.h"

#include <opencv2/opencv.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/imgcodecs.hpp"
#include "image_transport/image_transport.h"

#define IMAGE_WIDTH
#define IMAGE_HEIGHT

udp::UDP udpInstance;

ros::Publisher udp_publisher;

void robotControlMsgCallBack(const mobile_base_msgs::RobotControl::ConstPtr &msg);

#endif 
