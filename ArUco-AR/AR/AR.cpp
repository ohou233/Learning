#include "AR.h"
#include<opencv.hpp>
#include<string>
#include<qtimer.h>
#include<qpushbutton.h>
#include<qpixmap.h>
#include<aruco.hpp>
using namespace cv;
using namespace std;

AR::AR(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

	static cv::Mat cameraMatrix, distCoeffs;
	vector<double> cameraVec = { 657.1548323619423, 0, 291.8582472145741,0, 647.384819351103, 391.254810476919,0, 0, 1 };
	cameraMatrix = Mat(cameraVec);
	cameraMatrix = cameraMatrix.reshape(1, 3);
	vector<double> dist = { 0.1961793476399528, -1.38146317350581, -0.002301820186177369, -0.001054637905895881, 2.458286937422959 };
	distCoeffs = Mat(dist);
	distCoeffs = distCoeffs.reshape(1, 1);

	QPixmap black = QPixmap(ui.label1->size());
	ui.label1->setPixmap(black);
	ui.label2->setPixmap(black);

	ui.pushButton2->setDisabled(true);
	ui.pushButton3->setDisabled(true);

    static VideoCapture camera, video;
	video.open("D:\\opencv_c++\\opencv_tutorial\\data\\images\\Megamind.avi");
	if (!video.isOpened())
	{
		cout << "can't open video" << endl;
		exit(-1);
	}
	camera.open("http://192.168.3.2:8081");
	if (!camera.isOpened())
	{
		cout << "can't open camera" << endl;
		exit(-1);
	}

	QTimer *timer1 = new QTimer;
	timer1->setInterval(30);
	connect(timer1, &QTimer::timeout, ui.label1, [=]() {
		camera.read(frame);
		QImage qframe = QImage((const uchar*)frame.data, frame.cols, frame.rows, QImage::Format::Format_BGR888);
		ui.label1->setPixmap(QPixmap::fromImage(qframe.scaled(ui.label1->size(), Qt::AspectRatioMode::KeepAspectRatio)));
		});

	connect(ui.pushButton1, &QPushButton::clicked, ui.label1, [=]() {
		ui.pushButton2->setDisabled(false);
		ui.pushButton3->setDisabled(false);
		if (!camera.isOpened())
		{
			camera.open("http://192.168.3.2:8081");
		}
		timer1->start();
		});


	QTimer* timer2 = new QTimer;
	timer2->setInterval(30);
	connect(ui.pushButton2, &QPushButton::clicked, ui.label2, [=]() {
		ui.pushButton1->setDisabled(true);
		ui.pushButton2->setDisabled(true);
		if (!video.isOpened())
		{
			video.open("D:\\opencv_c++\\opencv_tutorial\\data\\images\\Megamind.avi");
		}

		Mat firstFrame;
		video.read(firstFrame);
		video.read(firstFrame);
		int width = firstFrame.cols;
		int height = firstFrame.rows;
		//提取替换图像的四个顶点
		new_image_box.clear();
		new_image_box.push_back(Point(0, 0));
		new_image_box.push_back(Point(width, 0));
		new_image_box.push_back(Point(width, height));
		new_image_box.push_back(Point(0, height));

		timer2 ->start();
		});

	
	connect(timer2, &QTimer::timeout, ui.label2, [=]() {
		camera.read(frame);
		Mat newFrame;
		video.read(videoFrame);
		if (videoFrame.empty())
		{
			timer2->stop();
		}
		//进行标记检测
		auto dictionary = aruco::getPredefinedDictionary(aruco::DICT_6X6_250);
		vector<vector<Point2f>>corners, rejectedImaPoints;
		vector<int>ids;
		auto parameters = aruco::DetectorParameters::create();
		aruco::detectMarkers(frame, dictionary, corners, ids, parameters, rejectedImaPoints, cameraMatrix, distCoeffs);
		if (ids.size() != 4)
		{
			QImage qframe = QImage((const uchar*)frame.data, frame.cols, frame.rows, QImage::Format::Format_BGR888);
			ui.label2->setPixmap(QPixmap::fromImage(qframe.scaled(ui.label2->size(), Qt::AspectRatioMode::KeepAspectRatio)));
		}
		else
		{
			//aruco::drawDetectedMarkers(videoFrame, corners, ids, Scalar(0, 255, 0));
			vector<vector<Point2f>> cornersList(4);
			for (int i = 0; i < 4; i++)
			{
				if (ids[i] == 2)
				{
					cornersList[0] = corners[i];
				}
				else if (ids[i] == 1)
				{
					cornersList[1] = corners[i];
				}
				else if (ids[i] == 0)
				{
					cornersList[2] = corners[i];
				}
				else if (ids[i] == 4)
				{
					cornersList[3] = corners[i];
				}
			}
			//提取四个标记形成的ROI区域
			vector<Point2f> roi_box_pt(4);
			//寻找方框的四个顶点，从检测到标记的顺序决定
			roi_box_pt[0] = cornersList[0][0];
			roi_box_pt[1] = cornersList[1][1];
			roi_box_pt[2] = cornersList[2][2];
			roi_box_pt[3] = cornersList[3][3];
			//计算从替换图像到目标ROI图像的3x3单应性矩阵
			H = findHomography(new_image_box, roi_box_pt);
			//进行透视变换
			cv::warpPerspective(videoFrame, videoFrame, H, frame.size(), INTER_CUBIC);
			//制作掩膜
			mask_mat = Mat(frame.size(), CV_8UC3, Scalar(255, 255, 255));
			for (int i = 0; i < frame.rows; i++)
			{
				for (int j = 0; j < frame.cols; j++)
				{
					if (videoFrame.at<Vec3b>(i, j) != Vec3b(0, 0, 0))
					{
						mask_mat.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
					}
				}
			}
			Mat kernel = getStructuringElement(MorphShapes::MORPH_RECT, Size(10, 10));
			cv::morphologyEx(mask_mat, mask_mat, MORPH_OPEN, kernel);
			//用透视变换后的替换图像，替换原图像中的ROI区域
			Mat result;
			bitwise_and(frame, mask_mat, newFrame);
			addWeighted(newFrame, 1, videoFrame, 0.7, 1.0, result);
			QImage qresult = QImage((const uchar*)result.data, result.cols, result.rows, QImage::Format::Format_BGR888);
			ui.label2->setPixmap(QPixmap::fromImage(qresult.scaled(ui.label2->size(), Qt::AspectRatioMode::KeepAspectRatio)));
		}
		});
	
	connect(ui.pushButton3, &QPushButton::clicked, ui.label1, [=]() {
		ui.pushButton1->setDisabled(false);
		ui.pushButton2->setDisabled(true);
		camera.release();
		video.release();
		timer1->stop();
		timer2->stop();
		ui.label1->setPixmap(black);
		ui.label2->setPixmap(black);
		});

}
