#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/Imu.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

#include "autonomous_droid_main/FusedData.h"

using namespace sensor_msgs;
using namespace message_filters;

void callback(const ImageConstPtr& image1, const ImageConstPtr& image2, const ImuConstPtr& imu1)
{
  // Solve all of perception here...
}

int main(int argc, char** argv)
{
	ROS_INFO_STREAM("[DC] Starting data collection node.");
	ros::init(argc, argv, "data_collection");
        ros::NodeHandle nh;
        message_filters::Subscriber<Image> camera_sub(nh, "camera/color/image_raw", 1);
        message_filters::Subscriber<Image> depth_sub(nh, "camera/depth/image_rect_raw", 1);
        message_filters::Subscriber<Imu> imu_sub(nh, "imu/data", 1);

        typedef sync_policies::ApproximateTime<Image, Image, Imu> MySyncPolicy;
        // ApproximateTime takes a queue size as its constructor argument, hence MySyncPolicy(10)
        Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), camera_sub, depth_sub, imu_sub);
        sync.registerCallback(boost::bind(&callback, _1, _2, _3));

        ros::spin();

        return 0;
}



//DODGY STUFF FROM ONLINE
/*
typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image, sensor_msgs::Image, sensor_msgs::CameraInfo> ApproxTimeSyncPolicy;

class SyncClass {
        message_filters::Subscriber<sensor_msgs::Image> *camera_sub;
        message_filters::Subscriber<sensor_msgs::Image> *camera_depth_sub;
        message_filters::Subscriber<sensor_msgs::CameraInfo> *cinfo_sub;
        message_filters::Synchronizer<NoCloudSyncPolicy>* approx_time_sync;

        // method definitions needed here
}

void SyncClass::init()
{
        ros::NodeHandle nh;

        int q = 1; //queue size
        camera_sub_ = new image_sub_type(nh, "/topic_image_mono", q);
        camera_depth_sub_ = new image_sub_type(nh, "/topic_image_depth", q);
        camera_info_sub_ = new cinfo_sub_type(nh, "/topic_camera_info", q);

        approx_time_sync_ = new message_filters::Synchronizer<ApproxTimeSyncPolicy>(ApproxTimeSyncPolicy(q),  *visua_sub_, *depth_sub_, *camera_info_sub_);

        approx_time_sync_->registerCallback(boost::bind(&SyncClass::callbackMethod, this, _1, _2, _3));
}

//The callback method
void SyncClass::callbackMethod (const sensor_msgs::ImageConstPtr& visual_img_msg, const sensor_msgs::ImageConstPtr& depth_img_msg, const sensor_msgs::CameraInfoConstPtr& cam_info_msg) 
{
     //Your processing code
}
*/




//OLD CODE
/*
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
        message_filters::Subscriber<sensor_msgs::Image> camera_sub;
        message_filters::Subscriber<sensor_msgs::Image> imu_sub;
        camera_sub.subscribe(nh, "camera_msg", 1);
        imu_sub.subscribe(nh, "imu_msg", 1);

//        ros::Subscriber imu_sub = n.subscribe("imu", 1, imuCallback);
//        ros::Subscriber camera_sub = n.subscribe("camera", 1, imuCallback);

        //Publishers
        ros::Publisher fused_data_pub = n.advertise<autonomous_droid_main::FusedData>("fused_data",1000);

        ros::Rate loop_rate(20); //imu only publishes at 20hz
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
*/
