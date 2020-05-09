#include<stdlib.h>
#include<string>
#include<opencv2/opencv.hpp>
#include"Train_SVM.h"
#include"Test_SVM.h"
using namespace std;
using namespace cv;


int main()
{
	//自定义对象检测——训练SVM模型：首先通过提取样本的HOG描述子，生成样本的特征数据，再通过SVM线性分类器进行分类学习与训练，
	//将训练结果保存为模型，这样以后就可以通过加载模型来实现对同一种对象的检测。
	//定义加载正样本数据和负样本数据的文件路径
	string positive_path = "D:\\opencv_c++\\Learning-OpenCV\\HOG+SVM自定义对象检测\\moon\\train\\positive\\";
	string negative_path = "D:\\opencv_c++\\Learning-OpenCV\\HOG+SVM自定义对象检测\\moon\\train\\nagetive\\";
	train_svm(positive_path, negative_path);

	//加载自定义对象检测模型和测试图像
	string model_path = "model.xml";
	Mat test_image = imread("D:\\opencv_c++\\Learning-OpenCV\\HOG+SVM自定义对象检测\\moon\\test\\7.jpg");
	test_svm(test_image, model_path);
	
	waitKey(0);
	return 0;
}