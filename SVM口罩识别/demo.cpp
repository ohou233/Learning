#include<opencv.hpp>
#include<vector>
#include<stdlib.h>
#include<string>
#include<iostream>
#include<fstream>
#include"face.h"
#include"face_mask.h"
using namespace std;
using namespace cv;
using namespace cv::dnn;

int main()
{
	/***********************************************训练***********************************************/
	////加载正负样本
	//string positive_path = "D:\\opencv_c++\\opencv_tutorial\\data\\test\\positive\\";
	//string negative_path = "D:\\opencv_c++\\opencv_tutorial\\data\\test\\negative\\";
	////通过glob()将路径下的所有图像文件以string类型读取进来
	//vector<string> positive_images_str, negative_images_str;
	//glob(positive_path, positive_images_str);
	//glob(negative_path, negative_images_str);
	////将string类型的图像数据转换为Mat类型
	//vector<Mat>positive_images, negative_images;
	//for (int i = 0; i < positive_images_str.size(); i++)
	//{
	//	Mat positive_image = imread(positive_images_str[i]);
	//	//resize(positive_image, positive_image, Size(64, 128));
	//	positive_images.push_back(positive_image);
	//}
	//for (int j = 0; j < negative_images_str.size(); j++)
	//{
	//	Mat negative_image = imread(negative_images_str[j]);
	//	//resize(negative_image, negative_image, Size(64, 128));
	//	negative_images.push_back(negative_image);
	//}
	//string savePath = "face_mask_detection.xml";
	//trainSVM(positive_images, negative_images, savePath);


	/****************************************检测******************************************/
	auto detecModel = ml::SVM::load("face_mask_detection.xml");
	Mat test_image = imread("D:/BaiduNetdiskDownload/人脸口罩检测数据集/val/13_Interview_Interview_On_Location_13_3.jpg");
	FaceMaskDetect(test_image, detecModel);
	//namedWindow("test_image", WINDOW_FREERATIO);
	imshow("test_image", test_image);
	
	
	/************************************实时检测********************************************/
	//VideoCapture capture;
	//capture.open(0);
	//if (!capture.isOpened())
	//{
	//	cout << "can't open camera" << endl;
	//	exit(-1);
	//}
	//Mat frame;
	//while (capture.read(frame))
	//{
	//	FaceMaskDetect(frame, detecModel);
	//	//namedWindow("test_image", WINDOW_FREERATIO);
	//	imshow("test_image", frame);

	//	char ch = waitKey(1);
	//	if (ch == 27)
	//	{
	//		break;
	//	}
	//}


	waitKey(0);
	return 0;
}