#include<stdlib.h>
#include<opencv2/opencv.hpp>
#include<string>
using namespace std;
using namespace cv;

int main()
{
	/***********************CamShift（Continuously Adaptive MeanShift）算法***********************/
	 VideoCapture capture;
	//capture.open("D:\\opencv_c++\\opencv_tutorial\\data\\images\\balltest.mp4");
	capture.open(0);
	if (!capture.isOpened())
	{
		return 0;
	}
	//提取第一帧图像中ROI区域并将其转化为HSV图像
	Mat first_image, first_hsv, roi_image, roi_hsv;
	capture.read(first_image);
	//鼠标左键选择ROI区域，空格键选定
	Rect roi_rect = selectROI("first_image", first_image, false, false);
	roi_image = first_image(roi_rect).clone();
	cvtColor(roi_image, roi_hsv, COLOR_BGR2HSV);
	//计算ROI图像的直方图
	Mat roi_hist;
	int dims = 2;
	int channels[2] = { 0,1 };
	int histSize[2] = { 180,255 };
	float ranges_h[2] = { 0,180 };
	float ranges_s[2] = { 0,255 };
	const float* histRanges[2] = { ranges_h, ranges_s };
	calcHist(&roi_hsv, 1, channels, Mat(), roi_hist, dims, histSize, histRanges);
	normalize(roi_hist, roi_hist, 0, 255, NORM_MINMAX);

	Mat frame, frame_hsv;
	vector<Point2f> centers;
	while (capture.read(frame))
	{
		flip(frame, frame, 1);
		cvtColor(frame, frame_hsv, COLOR_BGR2HSV);
		//对每一帧图像进行反向投影
		Mat backProject;
		calcBackProject(&frame_hsv, 1, channels, roi_hist, backProject, histRanges);
		//进行CamShift算法，不断更新目标窗口位置；返回值为一个包含位置和角度的旋转矩形
		RotatedRect new_rect = CamShift(backProject, roi_rect, TermCriteria(TermCriteria::COUNT | TermCriteria::EPS, 10, 1));
		// //参数probImage：输入的概率分布图像，也就是反向投影图像；
		//	//参数window：目标位置的初始窗口；
		//	//参数criteria：迁移终止条件；TermCriteria::EPS为迁移距离小于阈值时停止迁移，TermCriteria::COUNT为迁移迭代次数达到设定的最大值时停止迁移，可以两者同时使用；
		ellipse(frame, new_rect, Scalar(0, 255, 0), 1, 8);			//绘制目标区域位置

		//获取当前目标中心坐标，并存入点集中；不绘制完整目标移动轨迹，如果点集中的点数量达到规定个数，就清空点集；也就是每次只绘制最近的移动轨迹
		Point2f center = new_rect.center;	
		if (centers.size() % 20 == 0)
		{
			centers.clear();
		}
		centers.push_back(center);

		if (centers.size() > 2)		//只有当目标出现移动时，也就是目标中心坐标至少有两个点时才进行绘制
		{
			for (size_t k = 1; k < centers.size(); k++)
			{
				float  flag = float(k) / float(centers.size());			//标记当前点位于当前绘制的轨迹中的位置
				//通过标记位置的不同，来绘制不同粗细的曲线，从而使绘制出的轨迹曲线有逐渐消失的效果，类似于彗星尾巴
				if (flag < 0.2)
				{
					line(frame, centers[k - 1], centers[k], Scalar(0, 255, 0), 1, LINE_AA, 0);
				}
				else if(flag >= 0.2 && flag <= 0.4)
				{
					line(frame, centers[k - 1], centers[k], Scalar(0, 255, 0), 2, LINE_AA, 0);
				}
				else if (flag >= 0.4 && flag <= 0.6)
				{
					line(frame, centers[k - 1], centers[k], Scalar(0, 255, 0), 3, LINE_AA, 0);
				}
				else if(flag >= 0.6 && flag <= 0.8)
				{
					line(frame, centers[k - 1], centers[k], Scalar(0, 255, 0), 4, LINE_AA, 0);
				}
				else if (flag >= 0.8 && flag <= 1)
				{
					line(frame, centers[k - 1], centers[k], Scalar(0, 255, 0), 5, LINE_AA, 0);
				}
			}
		}
		imshow("frame", frame);

		char ch = waitKey(20);
		if (ch == 27)
		{
			break;
		}

	}
	capture.release();


	waitKey(0);
	return 0;
}