#include <ros/ros.h>
#include <std_msgs/Float64.h>

void myCallback(const std_msgs::Float64& message_holder)
{
	ROS_INFO("received value is %f",message_holder.data);
}

int main(int argc,char ** argv)
{
	ros::init(argc,argv,"subscriber");
	ros::NodeHandle sub;
	ros::Subscriber subscriber_object=sub.subscribe("topic1",1,myCallback);
	ros::spin();
	return 0;
}
