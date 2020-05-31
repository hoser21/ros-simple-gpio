#include "ros/ros.h"
#include "std_msgs/Bool.h"

void chatterCallback(const std_msg::Bool msg)
{
    ROS_INFO("I head: [%d]", msg.data);
}

int main(int argc, char **argv)
{
    ros::int(argc, argv, "listener");

    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("chatter", 1000, chatterCallback);

    ros::spin();

    return 0;
}