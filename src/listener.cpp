#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include <wiringPi.h>

// Toggle LEDs to the message's data
// LED Pins are pin 0 and 7 (wiringPi)
const int LED_BLUE = 0;
const int LED_YELLOW = 7;

void chatterCallback(const std_msgs::Bool msg)
{
    digitalWrite(LED_BLUE, msg.data);
    digitalWrite(LED_BLUE, !msg.data);
    
    ROS_INFO("I head: [%d]", msg.data);
}

int main(int argc, char **argv)
{
    // configure gpio ports for output
    wiringPiSetup();
    pinMode(LED_BLUE, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);
    
    // configure ROS
    ros::init(argc, argv, "listener");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("chatter", 1000, chatterCallback);
    ros::spin();

    return 0;
}