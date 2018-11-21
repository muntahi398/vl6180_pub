#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include <iostream>
#include "std_msgs/String.h"
#include <sstream>
#include<string.h>    //strlen
#include <sensor_msgs/Range.h>
#include <ros/time.h>
// for socket
#include <sys/socket.h>
#include <unistd.h>
#include<arpa/inet.h>

#define BUFLEN 512
#define NPACK 10
#define PORT 3333
//#define s_ip "192.168.0.102"
using namespace std;

//for structure serialization
#define BUFSIZE 512
#define PACKETSIZE sizeof(MSG)
typedef struct MSG
{
    int sensor_no;
    int range_val;
    uint32_t time_now;
    char message[BUFSIZE];
}MSG;
void serialize(MSG* msgPacket, char *data);
void deserialize(char *data, MSG* msgPacket);
void printMsg(MSG* msgPacket);




class node_class
{
public:
    node_class();
    bool init();
    void pub_data(int num);

private:
    ros::NodeHandle nh_;
    ros::Publisher pub_2;
    sensor_msgs::Range range_msg;
    ros::Timer timer1;
    void timer_cb();
    int loop_count;

};
node_class::node_class()
{
    loop_count = 0;
    pub_2= (nh_.advertise<sensor_msgs::Range>("vl6180_msg", 10));
}

void node_class::timer_cb() {
    ROS_INFO("hi");
    pub_data(loop_count);
    loop_count++;

}

bool node_class::init()
{
    char frameid[] = "/vl6180_msg";
    range_msg.radiation_type = sensor_msgs::Range::INFRARED;
    range_msg.header.frame_id =  frameid;
    range_msg.field_of_view = 0.1;  // fake
    range_msg.min_range = 0.0;
    range_msg.max_range = 0.2;

    //timer1 = nh_.createTimer(ros::Duration(0.1), &node_class::timer_cb, this );

    return 1; //True;
}

void node_class::pub_data(int num) {
    range_msg.range = 30;
    range_msg.header.stamp = ros::Time::now ();  //nh_.now();
    pub_2.publish(range_msg);

}







int main(int argc, char **argv)
{
    // socket udp part
    std::string s_ip ("192.168.0.102");
    uint16_t s_sock;
    struct sockaddr_in server;
    int sock, sock1;
    char  message[2], server_reply[PACKETSIZE];
    bzero(server_reply, sizeof(server_reply));
    bzero(message, sizeof(message));
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
    server.sin_addr.s_addr = inet_addr(s_ip.c_str());
    //server.sin_addr.s_addr = inet_addr(htonl(s_ip.c_str()));
    server.sin_family = AF_INET;
    server.sin_port = htons( PORT );//8888   //
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed to server specified  . Error");
        return 1;
    }
    puts("Connected\n");
    while(1) {
        int rlen = recv(sock, server_reply, PACKETSIZE, 0);
        MSG *temp = new MSG;
        deserialize(server_reply, temp);
        printMsg(temp);
        if ((temp->sensor_no) == 1) {

        }

    }



    // ros part
    ros::init(argc, argv, "node_class");
    node_class this_node;
    bool init_worked = this_node.init();

    if (not init_worked) {
        ROS_ERROR("Could not initialize main class. Exiting.");
        return -1;
    }

    ros::spin();

    return 0;
}

void serialize(MSG* msgPacket, char *data)
{
    int *q = (int*)data;
    *q = msgPacket->sensor_no;		q++;
    *q = msgPacket->range_val;	q++;
    *q = msgPacket->time_now;		q++;

    char *p = (char*)q;
    int i = 0;
    while (i < BUFSIZE)
    {
        *p = msgPacket->message[i];
        p++;
        i++;
    }
}

void deserialize(char *data, MSG* msgPacket)
{
    int *q = (int*)data;
    msgPacket->sensor_no = *q;		q++;
    msgPacket->range_val = *q;	q++;
    msgPacket->time_now = *q;		q++;

    char *p = (char*)q;
    int i = 0;
    while (i < BUFSIZE)
    {
        msgPacket->message[i] = *p;
        p++;
        i++;
    }
}

void printMsg(MSG* msgPacket)
{
    cout << msgPacket->sensor_no << endl;
    cout << msgPacket->range_val << endl;
    cout << msgPacket->time_now << endl;
    cout << msgPacket->message << endl;
}
//
// Created by muntahi on 17.07.18.
//

