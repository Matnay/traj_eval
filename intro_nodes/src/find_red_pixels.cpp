#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

static const std::string OPENCV_WINDOW = "Open-CV display window";
using namespace std;

class ImageConverter {
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_0;
    image_transport::Subscriber image_sub_1;
    image_transport::Publisher image_pub_0;
    image_transport::Publisher image_pub_1;


public:

    ImageConverter(ros::NodeHandle &nodehandle)
    : it_(nh_) {
        // Subscribe to input video feed and publish output video feed
        image_sub_0 = it_.subscribe("/cam0/image_raw", 1,
                &ImageConverter::imageCb0, this);
        image_sub_1 = it_.subscribe("/cam1/image_raw", 1,
                &ImageConverter::imageCb1, this);
        image_pub_0 = it_.advertise("/cam4/image_raw", 1);
        image_pub_1= it_.advertise("/cam5/image_raw", 1);

        cv::namedWindow(OPENCV_WINDOW);
    }

    ~ImageConverter() {
        cv::destroyWindow(OPENCV_WINDOW);
    }
    void imageCb0(const sensor_msgs::ImageConstPtr& msg){
        cv_bridge::CvImagePtr cv_ptr; //OpenCV data type
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::MONO8);
        cv::Size size_1(376,240);
        cv::Size size_2(188,120);
        cv::Mat dst;//dst image
        cv::Mat dst_2;
        cv::pyrDown( cv_ptr->image, dst, size_1 );//downsample image
        //cv::pyrDown( dst, dst_2, size_2 );//downsample image
        //cv::resize(cv_ptr->image,dst,size);
        cv_bridge::CvImage out_msg;
        out_msg.header   = msg->header; // Same timestamp and tf frame as input image
        out_msg.encoding = sensor_msgs::image_encodings::MONO8;
        out_msg.image    = dst;
        image_pub_0.publish(out_msg.toImageMsg());

        //cv::imshow(OPENCV_WINDOW, dst);//cv_ptr->image);
        //cv::waitKey(3);
    }
    void imageCb1(const sensor_msgs::ImageConstPtr& msg){
        cv_bridge::CvImagePtr cv_ptr; //OpenCV data type
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::MONO8);
        cv::Size size_1(376,240);
        cv::Size size_2(188,120);
        cv::Mat dst;//dst image
        cv::Mat dst_2;
        cv::pyrDown( cv_ptr->image, dst, size_1 );//downsample image
        //cv::pyrDown( dst, dst_2, size_2 );//downsample image
        //cv::resize(cv_ptr->image,dst,size);
        cv_bridge::CvImage out_msg;
        out_msg.header   = msg->header; // Same timestamp and tf frame as input image
        out_msg.encoding = sensor_msgs::image_encodings::MONO8;
        out_msg.image    = dst;
        image_pub_1.publish(out_msg.toImageMsg());
        
        //cv::imshow(OPENCV_WINDOW, dst);//cv_ptr->image);
        //cv::waitKey(3);
    }; 
    
}; //end of class definition

int main(int argc, char** argv) {
    ros::init(argc, argv, "red_pixel_finder");
    ros::NodeHandle n;        
    ImageConverter ic(n);
    ros::Duration timer(0.1);
    while (ros::ok()) {
        ros::spinOnce();
        timer.sleep();
    }
    return 0;
}
