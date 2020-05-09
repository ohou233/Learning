#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
#include<fstream>
#include<stdlib.h>
using namespace std;
using namespace cv;


void Debevec(vector<Mat>exposureImages, vector<float>exposureTimes);
void Robertson(vector<Mat>exposureImages, vector<float>exposureTimes);
void Mertens(vector<Mat>exposureImages);
int main()
{
	//加载曝光图像序列
	vector<string>imgPath;
	glob("D:\\opencv_c++\\opencv_tutorial\\data\\images\\exposures\\", imgPath);
	vector<Mat> exposure_images;
	for (int i = 0;i < imgPath.size();i++)
	{
		Mat exposure_image = imread(imgPath[i]);
		exposure_images.push_back(exposure_image);
	}
	//加载曝光时间序列
	String exposureTimesPath = "D:\\opencv_c++\\Learning-OpenCV\\高动态（HDR）图像\\exposuresTime.txt";
	ifstream fp(exposureTimesPath);
	if (!fp.is_open())
	{
		cout << "can't open file" << endl;
		exit(-1);
	}
	vector<float> exposureTimes;
	while (!fp.eof())
	{
		string time;
		getline(fp, time);
		float t = float(atof(time.c_str()));
		exposureTimes.push_back(t);
	}
	//进行HDR合成
	Debevec(exposure_images, exposureTimes);
	Robertson(exposure_images, exposureTimes);
	Mertens(exposure_images);

	waitKey(0);
	return 0;
}


//使用对比度、饱和度和曝光度好坏来对像素加权，而不是使用拉普拉斯金字塔来对图像进行加权。得到的图像权重被构造为对比度、饱和度和曝光度良好度量的加权平均值。
//生成的图像不需要进行色调映射，并且可以通过乘以255转换为8位图像，但是建议应用伽马校正或线性色调映射。
//不需要对应曝光时间, 可以在不需要HDR图像时使用，可直接得到低动态范围图像
void Mertens(vector<Mat>exposureImages)
{
	auto merge_mertens = createMergeMertens();
	Mat fusion;
	merge_mertens->process(exposureImages, fusion);
	//进行伽马矫正，需根据实际图像调节参数，2.2f可满足大多数显示情况
	/*auto tonemap = createTonemap(2.2f);
	tonemap->process(fusion, fusion);*/
	fusion = fusion * 255;
	fusion.convertTo(fusion, CV_8UC3);
	imshow("Mertens", fusion);
	imwrite("D:\\opencv_c++\\Learning-OpenCV\\高动态（HDR）图像\\Mertens.png", fusion);
}


//使用Debevec方法进行HDR合成，将多张曝光时间不同的照片及其对应的曝光值进行加权平均，得到float32类型的高动态范围HDR图像
//需要传入曝光图像序列和对应的曝光时间
void Debevec(vector<Mat>exposureImages, vector<float>exposureTimes)
{
	//auto Debevec_response = createCalibrateDebevec();
	//Mat response;
	//Debevec_response->process(exposureImages, response, exposureTimes);

	auto  merge_Debevec = createMergeDebevec();
	Mat hdr;
	merge_Debevec->process(exposureImages, hdr, exposureTimes);
	//由于是在普通的LDR显示器上进行显示，因此我们必须将HDR图像映射到保留大多数细节的8位范围的低动态范围LDR图像。
	//这是进行色调映射的主要目标，伽玛校正值设置为2.2f适用于大多数情况
	Mat ldr;
	auto tonemap = createTonemap(2.2f);
	tonemap->process(hdr, ldr);
	//HDR图像进行色调映射后得到的LDR图像取值范围在 [ 0 , 1 ] ，所以乘255将范围拉伸到 [ 0 , 255 ] 
	ldr = ldr * 255;
	//将float32类型转化为uchar8类型
	ldr.convertTo(ldr, CV_8UC3);
	imshow("Debevec_HDR", hdr);
	imshow("Debevec_LDR", ldr);
	imwrite("D:\\opencv_c++\\Learning-OpenCV\\高动态（HDR）图像\\Debevec_LDR.png", ldr);
}


//使用Robertson方法进行HDR图像合成，将多张曝光时间不同的照片及其对应的曝光值进行加权平均，得到float32类型的高动态范围HDR图像
//需要传入曝光图像序列和对应的曝光时间
void Robertson(vector<Mat>exposureImages, vector<float>exposureTimes)
{
	//auto Robertson_response = createCalibrateRobertson();
	//Mat response;
	//Robertson_response->process(exposureImages, response, exposureTimes);

	auto  merge_Robertson = createMergeRobertson();
	Mat hdr;
	merge_Robertson->process(exposureImages, hdr, exposureTimes);
	//由于是在普通的LDR显示器上进行显示，因此我们必须将HDR图像映射到保留大多数细节的8位范围的低动态范围LDR图像。
	//这是进行色调映射的主要目标，伽玛校正值设置为2.2f适用于大多数情况
	Mat ldr;
	auto tonemap = createTonemap(2.2f);
	tonemap->process(hdr, ldr);
	//HDR图像进行色调映射后得到的LDR图像取值范围在 [ 0 , 1 ] ，所以乘255将范围拉伸到 [ 0 , 255 ] 
	ldr = ldr * 255;
	ldr.convertTo(ldr, CV_8UC3);
	imshow("Robertson_HDR", hdr);
	imshow("Robertson_LDR", ldr);
	imwrite("D:\\opencv_c++\\Learning-OpenCV\\高动态（HDR）图像\\Robertson_LDR.png", ldr);

}