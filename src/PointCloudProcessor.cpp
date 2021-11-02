#include "ros/ros.h"
#include "std_msgs/String.h"
#include "pcl_ros/point_cloud.h"
#include "pcl/point_cloud.h"
#include "pcl_conversions/pcl_conversions.h"
#include <pcl/compression/octree_pointcloud_compression.h>
#include <sstream>
#include "chrono"

void cloudCallback(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr& cloudMsg)
{
   ROS_INFO("New PointCloud Processing! FrameId:%s, Width:%d, Height:%d", cloudMsg->header.frame_id.c_str(), cloudMsg->width, cloudMsg->height);

   pcl::io::compression_Profiles_e compressionProfile = pcl::io::MED_RES_ONLINE_COMPRESSION_WITH_COLOR;
   pcl::io::OctreePointCloudCompression<pcl::PointXYZ> *PointCloudEncoder = new pcl::io::OctreePointCloudCompression<pcl::PointXYZ>(compressionProfile, false);

   std::stringstream compressedData;

   auto start = std::chrono::system_clock::now();


   PointCloudEncoder->encodePointCloud(cloudMsg, compressedData);


   auto end = std::chrono::system_clock::now();

   auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

   ROS_INFO("Time Taken in Compression: %d ms", ms_int);



//   std::cout << "Compressed Cloud: " << compressedData.str();



}


int main(int argc, char **argv)
{

   ros::init(argc, argv, "PointCloudNode");

   ros::NodeHandle n;

   ros::Subscriber pclPub = n.subscribe("/os_cloud_node/points", 2, &cloudCallback);

   ros::Rate loop_rate(10);

   int count = 0;
   while (ros::ok())
   {
      std_msgs::String msg;

      std::stringstream ss;

      ros::spinOnce();

      loop_rate.sleep();
      ++count;
   }
   return 0;
}