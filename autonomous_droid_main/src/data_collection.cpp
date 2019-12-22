#include <ros/ros.h>

int main(){
	ROS_INFO_STREAM("[DC] Starting data collection node.");
	ros::spin();
	return 0;
}
