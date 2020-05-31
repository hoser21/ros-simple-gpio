#include "ros/ros.h"
#include "std_msgs/Bool.h"

int main(int argc, char **argc)
{
    ros::init(argc, argv, "simple_gpio");

    ros::NodeHandle nd;

    ros::Publisher pub = nh.advertise<std_msgs::Bool>("chatter", 1000);

    ros::Rate loop_rate(10);

    bool led = false;

    while (ros::okay())
    {
        std_msg::Bool msg;

        led = !led;
        msg.data = led;

        ROS_INFO("%d", msg.data);

        pub.publish(msg);

        ros::sinOnce();

        loop_rate.sleep();
    }

    return 0;
}