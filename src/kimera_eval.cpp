#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int32.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/TransformStamped.h>
#include <fstream>
#include <string>
#include <iostream>

geometry_msgs::TransformStamped vicon_odom;
nav_msgs::Odometry current_odom;
using namespace std;
void vicon_odom_callback(const geometry_msgs::TransformStamped& msg)
{
  vicon_odom=msg;
          std::ofstream out;
        out.open("stamped_groundtruth.txt", std::ios_base::app);
        out<<ros::Time::now()<<" "<<vicon_odom.transform.translation.x<<" "<<vicon_odom.transform.translation.y<<" "<<vicon_odom.transform.translation.z<<" "<<vicon_odom.transform.rotation.x<<" "<<vicon_odom.transform.rotation.y<<" "<<vicon_odom.transform.rotation.z<<" "<<vicon_odom.transform.rotation.w<<endl;
        out.close();
} 

void odom_callback(const nav_msgs::Odometry& msg)
{
  current_odom=msg;
          std::ofstream outfile;
        outfile.open("stamped_pose_graph_estimate.txt", std::ios_base::app);
        outfile<<ros::Time::now()<<" "<<current_odom.pose.pose.position.x<<" "<<current_odom.pose.pose.position.y<<" "<<current_odom.pose.pose.position.z<<" "<<current_odom.pose.pose.orientation.x<<" "<<current_odom.pose.pose.orientation.y<<" "<<current_odom.pose.pose.orientation.z<<" "<<current_odom.pose.pose.orientation.w<<endl;
        outfile.close();
} 


int main(int argc, char** argv) {
  ros::init(argc,argv,"relative_pose");
  ros::NodeHandle nh;
      ros::Subscriber noisy_odom=nh.subscribe("/vicon/firefly_sbx/firefly_sbx",1,vicon_odom_callback);
      ros::Subscriber odom=nh.subscribe("/kimera_vio_ros/odometry",1,odom_callback);
      //ros::Subscriber odom=nh.subscribe("/rovio/odometry",1,odom_callback);
      //ros::Subscriber odom=nh.subscribe("/firefly_sbx/vio/odom",1,odom_callback);
      ros::spin();
}
