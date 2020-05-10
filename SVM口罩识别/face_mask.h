#pragma once
#include<opencv.hpp>
#include<vector>
#include<stdlib.h>
#include<string>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
using namespace cv;

void trainSVM(vector<Mat> positive_images, vector<Mat> negative_images, string path)
{
	//分别获取正负样本中每张图像的HOG特征描述子，并进行标注
	HOGDescriptor* hog_train = new HOGDescriptor;
	vector<vector<float>> train_descriptors;
	int positive_num = positive_images.size();
	int negative_num = negative_images.size();
	vector<int> labels;
	for (int i = 0; i < positive_num; i++)
	{
		Mat positive_face;
		Rect positive_faceBox;
		if (faceDetected(positive_images[i], positive_face, positive_faceBox))
		{
			resize(positive_face, positive_face, Size(64, 128));
			Mat gray;
			cvtColor(positive_face, gray, COLOR_BGR2GRAY);			//计算HOG描述子时需要使用灰度图像
			vector<float> descriptor;
			hog_train->compute(gray, descriptor);
			train_descriptors.push_back(descriptor);
			labels.push_back(1);
		}
	}
	for (int j = 0; j < negative_num; j++)
	{
		Mat negative_face;
		Rect negative_faceBox;
		if (faceDetected(negative_images[j], negative_face, negative_faceBox))
		{
			resize(negative_face, negative_face, Size(64, 128));
			Mat gray;
			cvtColor(negative_face, gray, COLOR_BGR2GRAY);
			vector<float> descriptor;
			hog_train->compute(gray, descriptor);
			train_descriptors.push_back(descriptor);
			labels.push_back(-1);
		}
	}
	//将训练数据vector转换为Mat对象，每一行为一个描述子，行数即为样本数
	int width = train_descriptors[0].size();
	int height = train_descriptors.size();
	Mat train_data = Mat::zeros(Size(width, height), CV_32F);
	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			train_data.at<float>(r, c) = train_descriptors[r][c];
		}
	}
	auto train_svm = ml::SVM::create();
	train_svm->trainAuto(train_data, ml::ROW_SAMPLE, labels);
	train_svm->save(path);
	hog_train->~HOGDescriptor();
	train_svm->clear();
}


bool face_mask_detectd(Mat faceImg, Ptr<ml::SVM> model)
{
	resize(faceImg, faceImg, Size(64, 128));
	Mat face_gray;
	cvtColor(faceImg, face_gray, COLOR_BGR2GRAY);
	HOGDescriptor* hog = new HOGDescriptor;
	vector<float> descriptors;
	hog->compute(face_gray, descriptors);
	float detection = model->predict(descriptors);
	if (detection > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void FaceMaskDetect(Mat& inputImg, Ptr<ml::SVM> detecModel)
{
	Mat face;
	Rect faceBox;
	if (faceDetected(inputImg, face, faceBox))
	{
		if (face_mask_detectd(face, detecModel))
		{
			rectangle(inputImg, faceBox, Scalar(0, 255, 0), 1, 8);
			string output = "Face Mask";
			putText(inputImg, output, Point(faceBox.br().x / 2, faceBox.br().y), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 255, 0), 1, 8);
		}
		else
		{
			rectangle(inputImg, faceBox, Scalar(0, 0, 255), 1, 8);
			string output = "Not Face Mask";
			putText(inputImg, output, Point(faceBox.x, faceBox.y), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 0, 255), 1, 8);
		}
	}
}