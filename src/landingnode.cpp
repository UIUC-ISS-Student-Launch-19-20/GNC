#include "ros/ros.h"
#include "std_msgs/String.h"
#include <mavros_msgs/RCIn.h>
#include <cstdlib>
#include <stdlib.h>     /* atoi */
#include <mavros_msgs/CommandBool.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <sstream>
#include <mavros_msgs/ManualControl.h>


//mavros_msgs::State current_state;
// void state_cb(const mavros_msgs::State::ConstPtr& msg){
//     current_state = *msg;
//     print(*msg);

// void stateCallback(const mavros_msgs::State::ConstPtr& msg) {
//     std::cout << *msg <<std::endl;
// }


int main(int argc, char ** argv) {
    // state_cb(current_state);
    ros::init(argc, argv,"control_node");

    ros::NodeHandle nh;

    // mavros_msgs::SetMode offb_set_mode; //FIx this
    // ros::ServiceClient cl = nh.serviceClient<mavros_msgs::SetMode>("/mavros/set_mode");
    // mavros_msgs::SetMode srv_setMode;
    // srv_setMode.request.custom_mode = "LOITER";

    ros::Publisher control_pub = nh.advertise<mavros_msgs::ManualControl>
        ("mavros/manual_control/send", 50);

    mavros_msgs::ManualControl manual_control_ros{};
    ros::Rate r(50);

    manual_control_ros.header.stamp = ros::Time::now();

    ros::spin();
    manual_control_ros.x = (2000);
    manual_control_ros.y = (2000);
    manual_control_ros.z = (2000);
    control_pub.publish(manual_control_ros);
    std::cout<<"Print"<<std::endl;
   
    
    return 0;
}