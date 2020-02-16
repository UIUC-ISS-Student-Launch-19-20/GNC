
#include "ros/ros.h"
#include <std_msgs/String.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Pose.h>
#include <std_msgs/Float64.h>
#include <iostream>
#include <math.h>
#include "lib/Vector3.hpp"
#include "lib/Quaternion.hpp"


double calcDelta(int pix, int numPix, double fov, double groundAngle, double groundDist) {
    double pixRatio = (pix - numPix / 2) / (numPix / 2.0);
    double pixAng = atan(pixRatio * tan(fov / 2));
    double pixGroundAng = -groundAngle + pixAng;
    return groundDist * tan(pixGroundAng);
}

void chatterCallback(const geometry_msgs::PoseStamped::ConstPtr& msg) {
  double x = msg->pose.orientation.x;
  double y = msg->pose.orientation.y;
  double z = msg->pose.orientation.z;
  double w = msg->pose.orientation.w;

  Quaternion quat = Quaternion(x, y, z, w);
  Vector3 euler = Quaternion::ToEuler(quat);

  int pixWidth = 640, pixHeight = 480;
  double fovX = 45.0 * M_PI / 180.0, fovY = (fovX * pixHeight) / pixWidth;

  int pixX = 420, pixY = 290;
  double height = 10.0 + (rand() % 1000) / 1000.0;

  double offsetX = calcDelta(pixX, pixWidth, fovX, euler.Y, height);
  double offsetY = calcDelta(pixY, pixHeight, fovY, euler.X, height);

  std::cout << std::endl;
  std::cout << "Orientation: (" << euler.X << ", " << euler.Y << ", " << euler.Z << "), Height: " << height << std::endl;
  std::cout << "Detected position: (" << pixX << ", " << pixY << ")" << std::endl;
  std::cout << "Corrected position: (" << offsetX << ", " << offsetY << ")" << std::endl;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "readernode");  
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/mavros/local_position/pose", 1000, chatterCallback); //<geometry_msgs::PoseStamped>
  ros::spin();
  return 0;
}
