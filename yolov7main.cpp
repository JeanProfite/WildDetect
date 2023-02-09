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


YoloV7 yolov7;
int target_size = 640;

int main(int argc, char** argv)
{
    const char* videopath = argv[1];

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s [videopath]\n", argv[0]);
        return -1;
    }

    yolov7.load(target_size);

    cv::VideoCapture cap(videopath);

    if(!cap.isOpened())
    {
        fprintf(stderr, "cv::imread %s failed\n", videopath);
        return -1;
    }

    int64 t1 = 0;
    int64 t2 = 0;
    double fps = -1;
    std::string fps_text = "";
    cv::Mat frame;
    int key=0;
    std::vector<Object> objects;


    while (cap.read(frame) and key !='q')
    {
        t1 = cv::getTickCount();

        yolov7.detect(frame, objects);
        yolov7.draw(frame, objects);

        fps_text = "FPS: " + std::to_string(float(fps));
        cv::putText(frame, fps_text, cv::Point(30, 30), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255), 1);

        cv::imshow("Inférence YOLOV7",frame);

        t2 = cv::getTickCount();
        fps = cv::getTickFrequency()  / (t2 - t1);

        key = cv::waitKey(5);
        //printf("t2-t1=%ld Freq=%lf\n",t2-t1,cv::getTickFrequency());
        printf("FPS:%f  Nombre d'oiseaux:%lu\n",fps,objects.size());

    }

    return 0;
}
