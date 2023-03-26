// Tencent is pleased to support the open source community by making ncnn available.
//
// Copyright (C) 2020 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

//modified 8-2-2021 Q-engineering

#include "yolo.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <vector>

#define DISPLAY
#define RECORD
//#define USECAM

YoloV7 yolov7;
const int target_size = 640;
#ifdef USECAM
std::string gstreamer_pipeline(int capture_width, int capture_height, int framerate, int display_width, int display_height)
{
    return
        " libcamerasrc ! video/x-raw, "
        " width=(int)" + std::to_string(capture_width) + ","
        " height=(int)" + std::to_string(capture_height) + ","
        " framerate=(fraction)" + std::to_string(framerate) +"/1 !"
        " videoconvert ! videoscale !"
        " video/x-raw,"
        " width=(int)" + std::to_string(display_width) + ","
        " height=(int)" + std::to_string(display_height) + " ! appsink";
}
#endif
#ifndef USECAM
std::string gstreamer_pipeline(int capture_width, int capture_height, int framerate, int display_width, int display_height)
{
    return
        "filesrc location=/home/pi/software/YoloV7-ncnn-Raspberry-Pi-4/bird_airport.mp4 ! qtdemux ! decodebin ! videoconvert ! videoscale ! autovideosink";
}
#endif
int main(int argc, char** argv=NULL)
{

    static const char *class_names[] =
    {
        "Animal", "Bird"
    };

    //pipeline parameters
    int capture_width = 640; //1280 ;
    int capture_height = 480; //720 ;
    int framerate = 10 ;
    int display_width = 640; //1280 ;
    int display_height = 480; //720 ;

    std::string pipeline = gstreamer_pipeline(capture_width, capture_height, framerate,
                           display_width, display_height);
    cv::VideoCapture cap(pipeline, cv::CAP_GSTREAMER);
    std::cout << "Using pipeline: \n\t" << pipeline << "\n\n\n";
    yolov7.load(target_size);

    int64 t1 = 0;
    int64 t2 = 0;
    double fps = -1;
    std::string fps_text = "";
    cv::Mat frame;
    int key=0;
    std::vector<Object> objects;
    //Record
    int frame_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    bool recording = false;
    int videoindex = 1;

    cv::VideoWriter video;

    bool delaydetect = false ;
    int cpt =0;
    uint8_t nbdetect = 0;

    while (cap.read(frame) and key !='q')
    {
        t1 = cv::getTickCount();
        yolov7.detect(frame, objects,0.5);
        t2 = cv::getTickCount();
        fps = cv::getTickFrequency()  / (t2 - t1);

#ifdef DISPLAY
        yolov7.draw(frame, objects);
        fps_text = "FPS: " + std::to_string(float(fps));
        cv::putText(frame, fps_text, cv::Point(30, 30), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255), 1);
        cv::imshow("Inférence YOLOV7",frame);
        key = cv::waitKey(1);
#endif
        //printf("t2-t1=%ld Freq=%lf\n",t2-t1,cv::getTickFrequency());
        nbdetect = objects.size();
        printf("FPS:%f  Objets:%d\n",fps,nbdetect);
        for (int i = 0; i < nbdetect; i++)
        {
            printf("%d: %s %1.f%%\n",i,class_names[objects[i].label],objects[i].prob*100);
        }
#ifdef RECORD
        //Recording start
        if(nbdetect > 0 and recording == false)
        {
            char path[100];
            sprintf(path,"recording/%d.avi", videoindex);
            std::cout<<"recording started for" << path <<"\n";
            videoindex +=1;
            video.open(path,cv::VideoWriter::fourcc('M','J', 'P','G'), 2, cv::Size(frame_width,frame_height));
            recording = true;
        }

        //For each frame
        if(recording)
        {
            video.write(frame);

            if(nbdetect == 0)
            {
                cpt++;
            }
            else{cpt=0;}

            if(cpt >= 6)
            {
                delaydetect=true;
                cpt=0;
            }
        }

        if(nbdetect == 0 and recording and delaydetect)
        {
            std::cout << "recording finished.\n";
            recording = false;
            video.release();
            delaydetect=false;
        }

#endif

    }
    cap.release();
    return 0;
}
