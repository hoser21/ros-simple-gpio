#include "ros/ros.h"
#include "std_msgs/Bool.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "simple_gpio");

    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<std_msgs::Bool>("chatter", 1000);

    ros::Rate loop_rate(1);

    bool led = false;

    while (ros::ok())
    {
        std_msgs::Bool msg;

        led = !led;
        msg.data = led;

        ROS_INFO("%d", msg.data);

        pub.publish(msg);

        ros::spinOnce();

        loop_rate.sleep();
    }

    return 0;
}