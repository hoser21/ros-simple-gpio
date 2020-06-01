#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include <pigpio.h>

// Toggle LEDs to the message's data
// LED Pins are pin 0 and 7 (wiringPi)
const int LED_BLUE = 4;
const int LED_YELLOW = 17;

void chatterCallback(const std_msgs::Bool msg)
{
    gpioWrite(LED_BLUE, msg.data);
    gpioWrite(LED_YELLOW, !msg.data);

    ROS_INFO("I heard: [%d]. Toggling LEDs.", msg.data);
}

int main(int argc, char **argv)
{
    // configure gpio ports for output
    if (gpioInitialise() < 0)
    {
        ROS_INFO("pigpio failed to initialise");
        return 1;
    }
    gpioSetMode(LED_BLUE, PI_OUTPUT);
    gpioSetMode(LED_YELLOW, PI_OUTPUT);

    // configure ROS
    ros::init(argc, argv, "listener");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("chatter", 1000, chatterCallback);
    ros::spin();

    gpioTerminate();
    return 0;
}
