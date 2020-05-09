#pragma once
#include<stdlib.h>
#include<string>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void test_svm(Mat src, string modelPath)
{
	//测试分类器
	Mat test_image = src.clone();
	resize(test_image, test_image, Size(0, 0), 0.2, 0.2);
	Mat test_gray_image;
	cvtColor(test_image, test_gray_image, COLOR_BGR2GRAY);
	HOGDescriptor* hog_test = new HOGDescriptor;
	//加载训练好的SVM分类器
	auto test_svm = ml::SVM::load(modelPath);
	Rect winRect;
	vector<float> descriptors;
	vector<int>winRect_x, winRect_y;
	//对测试图像进行开窗，寻找匹配的窗口区域
	//开窗移动步长选择计算HOG描述子时的窗口步长，这样可以避免步长太小而导致检测框的数目过多而降低运行速度，
	//同时避免步长太大而导致漏检，最后求取多个检测框的平均值即可得到最终的检测框。
	for (int row = 64; row < test_image.rows - 64; row += 16)
	{
		for (int col = 32; col < test_image.cols - 32; col += 8)
		{
			winRect.width = 64;
			winRect.height = 128;
			winRect.x = col - 32;
			winRect.y = row - 64;
			//计算当前窗口区域的HOG描述子，并转换为Mat对象
			hog_test->compute(test_gray_image(winRect), descriptors);
			Mat descriptor_mat = Mat::zeros(Size(descriptors.size(), 1), CV_32FC1);
			for (int i = 0; i < descriptors.size(); i++)
			{
				descriptor_mat.at<float>(0, i) = descriptors[i];
			}
			//对当前窗口的描述子使用SVM模型进行预测，结果是1或-1
			float result;
			result = test_svm->predict(descriptor_mat);
			if (result > 0)
			{
				//保存当前窗口左上角坐标
				winRect_x.push_back(col - 32);
				winRect_y.push_back(row - 64);
			}
		}
	}
	//如果存在检测出的对象框，则计算平均坐标点并绘制目标框
	if (winRect_x.size() != 0)
	{
		int x = 0, y = 0;
		for (int k = 0; k < winRect_x.size(); k++)
		{
			x += winRect_x[k];
			y += winRect_y[k];
		}
		x = x / winRect_x.size();
		y = y / winRect_y.size();
		//int boxWidth = winRect_x.size() * 8;
		//int boxHeight = winRect_y.size() *8;
		Rect dected_box(x, y, 64, 128);
		rectangle(test_image, dected_box, Scalar(0, 255, 0), 1, 8, 0);
	}
	imshow("test_image", test_image);

	hog_test->~HOGDescriptor();
	test_svm->clear();
	test_image.~Mat();
	test_gray_image.~Mat();
	descriptors.~vector();
	winRect_x.~vector();
	winRect_y.~vector();
}