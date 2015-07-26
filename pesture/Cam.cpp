#include "Cam.h"

#include <iostream>
#include <stdio.h>

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"


using namespace std;
using namespace cv;


static void detectAndDisplay(
    Mat frame,
    CascadeClassifier& face_cascade,
    CascadeClassifier& upperbody_cascade
) {
    std::vector<Rect> faces;
    std::vector<Rect> upperbodies;

    Mat frame_gray;
    
    cvtColor(frame, frame_gray, CV_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);
    
    // Detect faces
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
    
    for(size_t i = 0; i < faces.size(); i++) {
        Point center(
            faces[i].x + faces[i].width * 0.5,
            faces[i].y + faces[i].height * 0.5
        );

        ellipse(
            frame, center, Size(faces[i].width * 0.5, faces[i].height * 0.5),
            0, 0, 360, Scalar(255, 0, 255), 4, 8, 0
        );
    }
    
    // Detect upper body
    upperbody_cascade.detectMultiScale(frame_gray, upperbodies);
    
    for(size_t i = 0; i < upperbodies.size(); i++) {
        rectangle(
            frame,
            upperbodies[i].tl(),
            upperbodies[i].br(),
            Scalar(255,255,255)
        );
    }
    
    // Show the frame
    imshow("pesture", frame);
}


int Cam::showCam(){
    CascadeClassifier face_cascade;
    CascadeClassifier upperbody_cascade;
    
    // 1. Load the cascades

    String face_cascade_name = "/data/haarcascade_frontalface_alt.xml";
    String upperbody_cascade_name = "/data/haarcascade_upperbody.xml";
    
    if(!face_cascade.load( face_cascade_name)) {
        printf("ERROR: Unable to load face cascade.\n");
        return -1;
    };
    if(!upperbody_cascade.load( upperbody_cascade_name)) {
        printf("ERROR: Unable to load upper body cascade.\n");
        return -1;
    };
    
    // 2. Read the video stream

    CvCapture* capture = cvCaptureFromCAM(-1);

    if(capture) {
        Mat frame;

        while (true) {
            frame = cvQueryFrame(capture);
            
            // 3. Apply the classifier to the frame
            if(!frame.empty()) {
                detectAndDisplay(frame, face_cascade, upperbody_cascade);
            } else {
                printf("WARNING: No captured frame.");
                break;
            }
            
            int c = waitKey(10);
            if ((char) c == 'c') {
                break;
            }
        }
    }

    return 0;
}
