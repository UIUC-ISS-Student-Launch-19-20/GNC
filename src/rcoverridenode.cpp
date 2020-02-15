#include "ros/ros.h"
#include "std_msgs/String.h"
#include <mavros_msgs/RCIn.h>
#include <mavros_msgs/OverrideRCIn.h>
#include <cstdlib>
#include <stdlib.h>     /* atoi */
#include <mavros_msgs/CommandBool.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <sstream>
#include <mavros_msgs/ManualControl.h>
#include "geometry_msgs/TwistStamped.h"
#include "geometry_msgs/Vector3Stamped.h"
#include <stdio.h>

//mavros_msgs::State current_state;
// void state_cb(const mavros_msgs::State::ConstPtr& msg){
//     current_state = *msg;
//     print(*msg);

// void stateCallback(const mavros_msgs::State::ConstPtr& msg) {
//     std::cout << *msg <<std::endl;
// }

int main(int argc, char **argv)
{
   ros::init(argc, argv, "override");
   ros::NodeHandle n;

   ros::Publisher control_pub = n.advertise<mavros_msgs::OverrideRCIn>("/mavros/rc/override",100);
   ros::Rate loop_rate(10);

   mavros_msgs::OverrideRCIn omsg;

   while(ros::ok()){
    //    omsg.process.stamp = ros::Time::now();
       omsg.channels[0] = 1500;
       omsg.channels[1] = 1700;
       omsg.channels[2] = 1700;
       omsg.channels[3] = 1500;

       control_pub.publish(omsg);
       ros::spinOnce();
       loop_rate.sleep();
   }    
   return 0;
}