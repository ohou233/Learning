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
	///***********************************************训练***********************************************/
	//string model_path = "D:\\opencv_c++\\opencv_tutorial\\data\\models\\face_detector\\opencv_face_detector_uint8.pb";
	//string config_path = "D:\\opencv_c++\\opencv_tutorial\\data\\models\\face_detector\\opencv_face_detector.pbtxt";
	//Net face_detector = readNetFromTensorflow(model_path, config_path);
	//face_detector.setPreferableBackend(DNN_BACKEND_INFERENCE_ENGINE);
	//face_detector.setPreferableTarget(DNN_TARGET_CPU);
	////加载正负样本
	//string positive_path = "D:\\opencv_c++\\opencv_tutorial\\data\\Face_Mask_Detection\\positive\\";
	//string negative_path = "D:\\opencv_c++\\opencv_tutorial\\data\\Face_Mask_Detection\\negative\\";
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
	//trainSVM(positive_images, negative_images, savePath, face_detector);


	/****************************************检测******************************************/
	//string model_path = "D:\\opencv_c++\\opencv_tutorial\\data\\models\\face_detector\\opencv_face_detector_uint8.pb";
	//string config_path = "D:\\opencv_c++\\opencv_tutorial\\data\\models\\face_detector\\opencv_face_detector.pbtxt";
	//Net face_detector = readNetFromTensorflow(model_path, config_path);
	//face_detector.setPreferableBackend(DNN_BACKEND_INFERENCE_ENGINE);
	//face_detector.setPreferableTarget(DNN_TARGET_CPU);
	//auto detecModel = ml::SVM::load("face_mask_detection.xml");
	//Mat test_image = imread("D:\\opencv_c++\\opencv_tutorial\\data\\images\\objects.jpg");
	//FaceMaskDetect(test_image, detecModel, face_detector);
	////namedWindow("test_image", WINDOW_FREERATIO);
	//imshow("test_image", test_image);
	//
	
	/************************************实时检测********************************************/
	//string model_path = "D:\\opencv_c++\\opencv_tutorial\\data\\models\\face_detector\\opencv_face_detector_uint8.pb";
	//string config_path = "D:\\opencv_c++\\opencv_tutorial\\data\\models\\face_detector\\opencv_face_detector.pbtxt";
	//Net face_detector = readNetFromTensorflow(model_path, config_path);
	//face_detector.setPreferableBackend(DNN_BACKEND_INFERENCE_ENGINE);
	//face_detector.setPreferableTarget(DNN_TARGET_CPU);
	//auto detecModel = ml::SVM::load("face_mask_detection.xml");
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
	//	FaceMaskDetect(frame, detecModel, face_detector);
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