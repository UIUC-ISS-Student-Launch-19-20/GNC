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

#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>
#include "OpenCV.cpp"


//mavros_msgs::State current_state;
// void state_cb(const mavros_msgs::State::ConstPtr& msg){
//     current_state = *msg;
//     print(*msg);

// void stateCallback(const mavros_msgs::State::ConstPtr& msg) {
//     std::cout << *msg <<std::endl;
// }

std::pair<int, int> position;

void image_callback(const sensor_msgs::ImageConstPtr& msg) {
	cout << "yay" << endl;
	Mat imgOriginal = cv_bridge::toCvCopy(msg, "bgr8")->image;
	waitKey(30);

    cout << "WHAT" << endl;

    position = detect(imgOriginal);
}

int main(int argc, char **argv)
{
   ros::init(argc, argv, "vset");
   ros::NodeHandle n;

   ros::Publisher chatter_pub = n.advertise<geometry_msgs::TwistStamped>("/mavros/setpoint_velocity/cmd_vel",100);
   ros::Subscriber image_sub = n.subscribe("/iris/camera/image_raw", 1, image_callback);
   ros::Rate loop_rate(10);

   geometry_msgs::TwistStamped msg;

   while(ros::ok()){
       msg.header.stamp = ros::Time::now();
       msg.header.seq=1;
       // msg.twist.linear.x = 1;
       // msg.twist.angular.x = 1;
       // msg.twist.linear.z = 1;

       chatter_pub.publish(msg);
       ros::spinOnce();
       loop_rate.sleep();

       std::cout << "(" << (position.first - 300) / 200.0 << ", " << -(position.second - 250) / 200.0 << ")" << endl;

       msg.twist.linear.x = -(position.first - 300) / 200.0;
       msg.twist.linear.y = (position.second - 250) / 200.0;
   }
   return 0;
}
