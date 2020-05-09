#pragma once
#include<stdlib.h>
#include<string>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void train_svm(string positive_path, string negative_path)
{
	//通过glob()将输入路径下的所有图像文件的路径以string类型读取进来
	vector<string> positive_images_str, negative_images_str;
	glob(positive_path, positive_images_str);
	glob(negative_path, negative_images_str);
	//将string类型的图像数据转换为Mat类型
	vector<Mat>positive_images, negative_images;
	for (int i = 0; i < positive_images_str.size(); i++)
	{
		Mat positive_image = imread(positive_images_str[i]);
		resize(positive_image, positive_image, Size(64, 128));
		positive_images.push_back(positive_image);
	}
	for (int j = 0; j < negative_images_str.size(); j++)
	{
		Mat negative_image = imread(negative_images_str[j]);
		resize(negative_image, negative_image, Size(64, 128));
		negative_images.push_back(negative_image);
	}

	//分别获取正负样本中每张图像的HOG特征描述子，并进行标注
	HOGDescriptor *hog_train = new HOGDescriptor;
	vector<vector<float>> train_descriptors;
	int positive_num = positive_images.size();
	int negative_num = negative_images.size();
	vector<int> labels;
	for (int i = 0; i < positive_num; i++)
	{
		Mat gray;
		cvtColor(positive_images[i], gray, COLOR_BGR2GRAY);			//计算HOG描述子时需要使用灰度图像
		vector<float> descriptor;
		hog_train->compute(gray, descriptor, Size(8, 16), Size(0, 0));
		train_descriptors.push_back(descriptor);
		labels.push_back(1);
	}
	for (int j = 0; j < negative_num; j++)
	{
		Mat gray;
		cvtColor(negative_images[j], gray, COLOR_BGR2GRAY);
		vector<float> descriptor;
		hog_train->compute(gray, descriptor, Size(8, 16), Size(0, 0));
		train_descriptors.push_back(descriptor);
		labels.push_back(-1);
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
	//使用最优参数训练SVM分类器，并保存到与代码同目录下
	auto train_svm = ml::SVM::create();
	train_svm->trainAuto(train_data, ml::ROW_SAMPLE, labels);
	train_svm->save("model.xml");
	hog_train->~HOGDescriptor();
	train_svm->clear();
	positive_images_str.~vector();
	negative_images_str.~vector();
	positive_images.~vector();
	negative_images.~vector();
	labels.~vector();
	train_data.~Mat();
}
