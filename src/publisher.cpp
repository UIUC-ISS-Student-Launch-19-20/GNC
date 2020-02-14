#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

int main(int argc, char ** argv) {

    ros::init(argc, argv,'publisher');

    ros::NodeHandle nh;

    ros::Publisher pos_publish = nh.advertise<geometry_msgs::PoseStamped>
        ("mavros/setpoint_position/local", 10);

    geometry_msgs::PoseStamped pose;
    pose.position.x = 0;
    pose.position.y = 0;
    pose.position.z = 0;

}

