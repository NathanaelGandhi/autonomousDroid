#include <ros/ros.h>
#include "autonomous_droid_main/FusedData.h"

void imuCallback(const std_msgs::String::ConstPtr& msg){
        ROS_INFO("[DC] IMU Callback");
}

void cameraCallback(const std_msgs::String::ConstPtr& msg){
        ROS_INFO("[DC] Camera Callback");
}

int main(int argc char **argv){
	ROS_INFO_STREAM("[DC] Starting data collection node.");
	ros::init(argc, argv, "data_collection");
        ros::Nodehandle n;

        //Subscribers
        ros::Subscriber imu_sub = n.subscribe("imu", 1, imuCallback);
        ros::Subscriber camera_sub = n.subscribe("camera", 1, imuCallback);

        //Publishers
        ros::Publisher fused_data_pub = n.advertise<autonomous_droid_main::FusedData>("fused_data",1000);

        ros::Rate loop_rate(30);
        int count = 0;
        while(ros::ok()){
                autonomous_droid_main::FusedData msg;
                fused_data_pub.publish(msg)
                ros::spinOnce();
                loop_rate.sleep();
                count++;
        }
	return 0;
}
