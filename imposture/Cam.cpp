#include "Cam.h"

#include <opencv2/opencv.hpp>


int Cam::showCam(){
    cv::VideoCapture capture(0); // open default camera

    if (!capture.isOpened()) {
        return -1;
    }

    cv::namedWindow("imposture", 1);

    cv::Mat frame;

    while (true) {
        capture >> frame;

        cv::imshow("imposture", frame);

        int key = cv::waitKey(1);
        if (key == 27) {
            break;
        }
    }
    return 0;
}
