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
    image_transport::Subscriber image_sub_;
    image_transport::Publisher image_pub_;

public:

    ImageConverter(ros::NodeHandle &nodehandle)
    : it_(nh_) {
        // Subscribe to input video feed and publish output video feed
        image_sub_ = it_.subscribe("/cam0/image_raw", 1,
                &ImageConverter::imageCb, this);
        image_pub_ = it_.advertise("/cam4/image_raw", 1);

        cv::namedWindow(OPENCV_WINDOW);
    }

    ~ImageConverter() {
        cv::destroyWindow(OPENCV_WINDOW);
    }
    void imageCb(const sensor_msgs::ImageConstPtr& msg){
        cv_bridge::CvImagePtr cv_ptr; //OpenCV data type
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::MONO8);
        cv::Size size(376,240);
        cv::Mat dst;//dst image
        cv::pyrDown( cv_ptr->image, dst, size );//downsample image
        cv_bridge::CvImage out_msg;
        out_msg.header   = msg->header; // Same timestamp and tf frame as input image
        out_msg.encoding = sensor_msgs::image_encodings::MONO8;
        out_msg.image    = dst;
        image_pub_.publish(out_msg.toImageMsg());
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
