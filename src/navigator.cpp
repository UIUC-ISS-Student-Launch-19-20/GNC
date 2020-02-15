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
   ros::init(argc, argv, "vset");
   ros::NodeHandle n;

   ros::Publisher chatter_pub = n.advertise<geometry_msgs::TwistStamped>("/mavros/setpoint_velocity/cmd_vel",100);
   ros::Rate loop_rate(10);

   geometry_msgs::TwistStamped msg;

   while(ros::ok()){
       msg.header.stamp = ros::Time::now();
       msg.header.seq=1;
       msg.twist.linear.x = 1;
       msg.twist.angular.x = 1;
       msg.twist.linear.z = 1;

       chatter_pub.publish(msg);
       ros::spinOnce();
       loop_rate.sleep();
   }    
   return 0;
}