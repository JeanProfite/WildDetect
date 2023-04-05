#!/bin/bash

# Compiler yolo.cpp
g++ -Wall -Wno-unknown-pragmas -isystem -fPIE -fopenmp -pthread -DNDEBUG -O3 \
  -I/usr/local/include/opencv4 -I/usr/local/include/ncnn \
  -c /home/pi/software/YoloV7-ncnn-Raspberry-Pi-4/yolo.cpp -o obj/Release/yolo.o

# Compiler yolov7main.cpp
g++ -Wall -Wno-unknown-pragmas -isystem -fPIE -fopenmp -pthread -DNDEBUG -O3 \
  -I/usr/local/include/opencv4 -I/usr/local/include/ncnn \
  -c /home/pi/software/YoloV7-ncnn-Raspberry-Pi-4/yolov7main.cpp -o obj/Release/yolov7main.o

# Compiler l'exécutable YoloV7
g++ -o bin/Release/YoloV7 obj/Release/yolo.o obj/Release/yolov7main.o \
  -fopenmp -I/usr/local/include/opencv4 \
  -L/usr/local/lib \
  -lopencv_gapi -lopencv_stitching -lopencv_aruco -lopencv_bgsegm \
  -lopencv_bioinspired -lopencv_ccalib -lopencv_dnn_objdetect \
  -lopencv_dnn_superres -lopencv_dpm -lopencv_face -lopencv_freetype \
  -lopencv_fuzzy -lopencv_hdf -lopencv_hfs -lopencv_img_hash \
  -lopencv_intensity_transform -lopencv_line_descriptor -lopencv_mcc \
  -lopencv_quality -lopencv_rapid -lopencv_reg -lopencv_rgbd \
  -lopencv_saliency -lopencv_stereo -lopencv_structured_light \
  -lopencv_phase_unwrapping -lopencv_superres -lopencv_optflow \
  -lopencv_surface_matching -lopencv_tracking -lopencv_highgui \
  -lopencv_datasets -lopencv_text -lopencv_plot -lopencv_videostab \
  -lopencv_videoio -lopencv_xfeatures2d -lopencv_shape -lopencv_ml \
  -lopencv_ximgproc -lopencv_video -lopencv_dnn -lopencv_xobjdetect \
  -lopencv_objdetect -lopencv_calib3d -lopencv_imgcodecs \
  -lopencv_features2d -lopencv_flann -lopencv_xphoto -lopencv_photo \
  -lopencv_imgproc -lopencv_core -ldl -lpthread -pthread -lgomp \
  -DNDEBUG -rdynamic -s /usr/local/lib/ncnn/libncnn.a

