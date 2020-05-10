#pragma once
#include<opencv.hpp>
#include<vector>
#include<stdlib.h>
#include<string>
#include<iostream>
#include<fstream>
using namespace std;
using namespace cv;
using namespace cv::dnn;


bool faceDetected(Mat inputImg, Mat& outputFace, Rect &facebox)
{
	string model_path = "D:\\opencv_c++\\opencv_tutorial\\data\\models\\face_detector\\opencv_face_detector_uint8.pb";
	string config_path = "D:\\opencv_c++\\opencv_tutorial\\data\\models\\face_detector\\opencv_face_detector.pbtxt";
	Net face_detector = readNetFromTensorflow(model_path, config_path);
	face_detector.setPreferableBackend(DNN_BACKEND_OPENCV);
	face_detector.setPreferableTarget(DNN_TARGET_CPU);
	Mat frame = inputImg;
	Mat inputBlob = blobFromImage(frame, 1.0, Size(300, 300), Scalar(104.0, 177.0, 123.0), false);

	face_detector.setInput(inputBlob);
	Mat prob = face_detector.forward();

	Mat detection(prob.size[2], prob.size[3], CV_32F, prob.ptr<float>());
	float confidence_thresh = 0.5;
	for (int row = 0; row < detection.rows; row++)
	{
		float confidence = detection.at<float>(row, 2);
		if (confidence > confidence_thresh)
		{
			int classID = detection.at<float>(row, 1);
			int notKnown = detection.at<float>(row, 0);
			int top_left_x = detection.at<float>(row, 3) * frame.cols;
			int top_left_y = detection.at<float>(row, 4) * frame.rows;
			int button_right_x = detection.at<float>(row, 5) * frame.cols;
			int button_right_y = detection.at<float>(row, 6) * frame.rows;
			int width = button_right_x - top_left_x;
			int height = button_right_y - top_left_y;
			Rect box(top_left_x, top_left_y, width, height);
			//rectangle(frame, box, Scalar(0, 255, 0), 1, 8, 0);
			cout << classID << "," << notKnown << "," << confidence << endl;
			if (box.x < 0 || box.y < 0)
			{
				box.x = 0;
				box.y = 0;
			}
			else if (box.br().x > frame.cols || box.br().y > frame.rows)
			{
				box.width = frame.cols - box.x;
				box.height = frame.rows - box.y;
			}
			else if (box.x + box.width > frame.cols)
			{
				box.width = frame.cols - box.x - 1;
			}
			else if (box.y + box.height > frame.rows)
			{
				box.height = frame.rows - box.y - 1;
			}
			else if (0 < box.width && 0 < box.height)
			{
				outputFace = frame(box).clone();
				facebox = box;
			}
		}
	}
	if (outputFace.empty())
	{
		return false;
	}
	else
	{
		return true;
	}
}