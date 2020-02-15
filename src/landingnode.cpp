#include "ros/ros.h"
#include "std_msgs/String.h"
#include <mavros_msgs/OverrideRCIn.h>
#include <cstdlib>
#include <stdlib.h>     /* atoi */
#include <mavros_msgs/CommandBool.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <sstream>

mavros_msgs::State current_state;
// void state_cb(const mavros_msgs::State::ConstPtr& msg){
//     current_state = *msg;
//     print(*msg);

void stateCallback(const mavros_msgs::State::ConstPtr& msg) {
    std::cout << *msg <<std::endl;
}


int main(int argc, char ** argv) {
    // state_cb(current_state);

    ros::init(argc, argv,"mavros_rc_override");

    ros::NodeHandle nh;

    mavros_msgs::SetMode offb_set_mode; //FIx this
    ros::ServiceClient cl = nh.serviceClient<mavros_msgs::SetMode>("/mavros/set_mode");
    mavros_msgs::SetMode srv_setMode;
    srv_setMode.request.base_mode = 0;
    srv_setMode.request.custom_mode = "LOITER";

    int pitch = 1600;
    // std::cout <<"Pitch: "<< pitch << std::endl;
    int roll = 0;
    int throttle = 1550;
    int yaw = 0;

    int rate = 100;
    ros::Rate r(rate);

    ros::Publisher rc_override_pub = nh.advertise<mavros_msgs::OverrideRCIn>
        ("mavros/rc/override", 10);

    mavros_msgs::OverrideRCIn msg_override;

    while (nh.ok()){
   
        msg_override.channels[0] = roll; //1
        msg_override.channels[1] = pitch; //2
        msg_override.channels[2] = throttle; //3
        msg_override.channels[3] = yaw; //4
        msg_override.channels[4] = 1100;
        msg_override.channels[5] = 1100;
        msg_override.channels[6] = 1100; 
    }
    return 0;
}