#pragma once
#include<opencv2/opencv.hpp>
#include<stdlib.h>
#include<string>
#include<vector>
#include"AllFeatures.h"
using namespace std;
using namespace cv;


//生成图像数据
vector<Mat> GetTrainData(Mat src, vector<Rect>&box_digits)
{
	Mat gray_digits_image, binary_digits_image;
	cvtColor(src, gray_digits_image, COLOR_BGR2GRAY);
	threshold(gray_digits_image, binary_digits_image, 0, 0255, THRESH_BINARY_INV | THRESH_OTSU);

	vector<vector<Point>>contours;
	findContours(binary_digits_image, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point());
	for (int i = 0; i < contours.size();i++)
	{
		Rect box_digit = boundingRect(contours[i]);
		box_digits.push_back(box_digit);
		rectangle(src, box_digit, Scalar(0, 255, 0), 1, 8);
		//imshow("dd", src);
	}
	for (int i = 0;i < box_digits.size() - 1;i++)
	{
		for (int j = i + 1;j < box_digits.size(); j++)
		{
			if (box_digits[i].x > box_digits[j].x)
			{
				Rect temp = box_digits[i];
				box_digits[i] = box_digits[j];
				box_digits[j] = temp;
			}
		}
	}

	//剪切十个数字区域
	vector<Mat>ROI_digits;
	for (int i = 0;i < box_digits.size();i++)
	{
		Mat ROI_digit = binary_digits_image(box_digits[i]).clone();
		ROI_digits.push_back(ROI_digit);
	}

	return ROI_digits;
}


//生成标签集
vector<int> GetTrainLabels()
{
	vector<int>labels;

	for (int i = 0; i < 9;i++)
	{
		labels.push_back(i + 1);
	}
	labels.push_back(0);

	return labels;
}


void TrainSVM(vector<vector<float>>features, vector<int> labels)
{
	Mat train_digits_feature = Mat::zeros(Size(40, 10), CV_32FC1);
	for (int row = 0;row < train_digits_feature.rows;row++)
	{
		for (int col = 0;col < train_digits_feature.cols;col++)
		{
			train_digits_feature.at<float>(row, col) = features[row][col];
		}
	}
	Mat train_labels = Mat::zeros(Size(1, 10), CV_32SC1);
	for (int row = 0;row < train_labels.rows;row++)
	{
		train_labels.at<int>(row, 0) = labels[row];
	}

	auto train_svm = ml::SVM::create();
	train_svm->trainAuto(train_digits_feature, ml::ROW_SAMPLE, train_labels,100);
	train_svm->save("model.xml");
}