#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include <iostream>
#include "std_msgs/String.h"
#include <sstream>
#include <sensor_msgs/Range.h>
#include <ros/time.h>

class node_class
{
public:
    node_class();
    bool init();
    void pub_data(int num);
private:
    ros::NodeHandle nh_;
    ros::Publisher pub_2;
};
node_class::node_class()
{
    pub_2= (nh_.advertise<diagnostic_light::Num>("chatter", 10));
}

bool node_class::init()
{

    return True;
}

void node_class::pub_data(int num) {
    diagnostic_light::Num new_msg;
    new_msg.num = num;
    new_msg.bool3 = {1, 1, 1};
    pub_2.publish(new_msg);

}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "node_class");
    node_class this_node;
    bool init_worked = this_node.init();

    if (not init_worked) {
        ROS_ERROR("Could not initialize main class. Exiting.");
        return -1;
    }

    ros::Rate main_loop_rate(10);
    int loop_count = 0;

    while(ros::ok())
    {
        this_node.pub_data(loop_count);
        loop_count++;
        ros::spinOnce();
        main_loop_rate.sleep();
    }

    return 0;   // Design Pattern Gang of four book   first 90 pg
}
//
// Created by muntahi on 20.11.18.
//

