#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int32.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include <fstream>
#include <string>
#include <iostream>

geometry_msgs::PoseStamped ground_odom;
nav_msgs::Odometry current_odom;
using namespace std;
void pose_stamped_callback(const geometry_msgs::PoseStamped& msg)
{
  ground_odom=msg;
          std::ofstream out;
        out.open("stamped_groundtruth.txt", std::ios_base::app);
        out<<ros::Time::now()<<" "<<ground_odom.pose.position.x<<" "<<ground_odom.pose.position.y<<" "<<ground_odom.pose.position.z<<" "<<ground_odom.pose.orientation.x<<" "<<ground_odom.pose.orientation.y<<" "<<ground_odom.pose.orientation.z<<" "<<ground_odom.pose.orientation.w<<endl;
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
      ros::Subscriber ground_truth_odom=nh.subscribe("/blackbird/pose_ref",1,pose_stamped_callback);
      ros::Subscriber odom=nh.subscribe("/vimo_estimator/odometry",1,odom_callback);
      ros::spin();
}
