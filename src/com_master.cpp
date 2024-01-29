#include "../include/com_master/com_master.h"

QHostAddress ROBOT_IP = QHostAddress("192.168.188.100");  
QHostAddress OPERATOR_IP = QHostAddress("192.168.188.253");

int main(int argc, char** argv)
{
    ros::init(argc, argv, "robot_udp_communication_master");
    ros::NodeHandle nh;
    
    ROS_INFO("[COM] Starting Robot Communication Node.");

    ros::Rate loop_rate(100);
    while (ros::ok())
    {
        ros::spinOnce();
        loop_rate.sleep();
    }
    ROS_INFO("[COM] Closing Communication Node.");
    return 0;
}

void robotControlMsgCallBack(const mobile_base_msgs::RobotControl::ConstPtr &msg)
{
    ROS_INFO("[COM] Sending Robot Control Data to robot.");
}
