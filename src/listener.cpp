#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include <pigpiod_if2.h>

// toggle LEDs to the message's data
// LED pins are pin 4 and 17 (BCM)
const int LED_BLUE = 4;
const int LED_YELLOW = 17;

// a class to associate the callback function to a pigpio daemon 
class ListenerGPIO
{
    public:
        ListenerGPIO(int pi) : pigpio_id(pi) {}

        void chatterCallback(const std_msgs::Bool msg)
        {
            gpio_write(pigpio_id, LED_BLUE, msg.data);
            gpio_write(pigpio_id, LED_YELLOW, !msg.data);

            ROS_INFO("I heard: [%d]. Toggling LEDs.", msg.data);
        }

    private:
        const int pigpio_id;
};

int main(int argc, char **argv)
{
    // connect to the pigpio daemon and configure gpio ports
    int pi = pigpio_start(0, 0);
    if (pi < 0)
    {
        ROS_INFO("pigpio failed to initialise");
        return 1;
    }
    set_mode(pi, LED_BLUE, PI_OUTPUT);
    set_mode(pi, LED_YELLOW, PI_OUTPUT);

    // configure ROS
    ros::init(argc, argv, "listener");
    ros::NodeHandle nh;

    // create listener object and subscribe it to the "chatter" topic
    ListenerGPIO listener(pi);
    ros::Subscriber sub = nh.subscribe("chatter", 1000, &ListenerGPIO::chatterCallback, &listener);
    
    ros::spin();
    
    // disconnect from the daemon
    pigpio_stop(pi);
    return 0;
}
