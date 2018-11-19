#include <iostream>
#include <sstream>
#include <opencv2/opencv.hpp>

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

#include <cv.h>
#include <highgui.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace cv;
using namespace std;

std::string get_tegra_pipeline(int width, int height, int fps)
{
    return "nvcamerasrc ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480, format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=2 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}

int main(int argc, char **argv)
{
    // Options
    int WIDTH = 752;
    int HEIGHT = 480;
    int FPS = 30;

    // Define the gstream pipeline
    std::string pipeline = get_tegra_pipeline(WIDTH, HEIGHT, FPS);

    // Create OpenCV capture object, ensure it works.
    cv::VideoCapture cap(pipeline, cv::CAP_GSTREAMER);
    if (!cap.isOpened())
    {
        std::cout << "Connection failed\n";
        return -1;
    }
    ros::init(argc, argv, "tx2_camera");

    ros::NodeHandle n;

    image_transport::ImageTransport it(n);
    image_transport::Publisher pub = it.advertise("/camera/image_raw", 1);
    sensor_msgs::ImagePtr msg;
    // View video
    cv::Mat frame;
    while (ros::ok())
    {
        usleep(35000);
        cap>>frame;
        // imshow("Display window", frame);
        // cv::waitKey(1);
        cv_bridge::CvImage camera_img = cv_bridge::CvImage(std_msgs::Header(), sensor_msgs::image_encodings::BGR8, frame);

        msg = camera_img.toImageMsg();
        pub.publish(msg);
        ros::spinOnce();
    }
}
