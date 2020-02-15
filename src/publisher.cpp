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
void state_cb(const mavros_msgs::State::ConstPtr& msg){
    current_state = *msg;
}

int main(int argc, char ** argv) {

    mavros_msgs::SetMode offb_set_mode; //FIx this
    ros::ServiceClient cl = n.serviceClient<mavros_msgs::SetMode>("/mavros/set_mode");
    mavros_msgs::SetMode srv_setMode;
    srv_setMode.request.base_mode = 0;
    srv_setMode.request.custom_mode = "LOITER"


    ros::init(argc, argv,"mavros_rc_override");

    ros::NodeHandle nh;

    int pitch = 1600;
    int roll = 0;
    int throttle = 1550;
    int yaw = 0;

    int rate = 100;
    ros::Rate r(rate);

    ros::Publisher rc_override_pub = nh.advertise<mavros_msgs::OverrideRCIn>
        ("mavros/rc/override", 10);

    mavros_msgs::OverrideRCIn msg_override;

    while (nh.ok()){
   
        msg_override.channels[0] = roll;
        msg_override.channels[1] = pitch;
        msg_override.channels[2] = throttle;
        msg_override.channels[3] = yaw;
        msg_override.channels[4] = 1100;
        msg_override.channels[5] = 1100;
        msg_override.channels[6] = 1100; 