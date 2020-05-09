#pragma once
#include<opencv2/opencv.hpp>
#include<stdlib.h>
#include<string>
#include<vector>
using namespace std;
using namespace cv;


//计算0~9每个数字的特征向量
vector<vector<float>> AllFeatures(vector<Mat>ROI_digits, vector<vector<float>>features)
{
	vector<float> digit_feature;
	for (int i = 0;i < ROI_digits.size();i++)
	{
		Mat digit = ROI_digits[i];
		//计算4x5网格内每个区域cell的前景像素数，并归一化，得到20个特征值
		float width = digit.cols;
		float height = digit.rows;
		//4x5网格分割
		float cell_w = float(width) / 4;
		float cell_h = float(height) / 5;
		vector<Mat>cells;
		for (float row = 0.0; row < height; row += cell_h)
		{
			for (float col = 0.0;col < width;col += cell_w)
			{
				int r = floor(row);
				int c = floor(col);
				Rect cell_box(c, r, floor(cell_w), floor(cell_h));
				Mat cell = digit(cell_box).clone();
				cells.push_back(cell);
			}
		}
		//计算每个cell中的背景像素数并做归一化
		for (int i = 0; i < cells.size();i++)
		{
			float pixelNum_cell = 0;
			for (int row = 0;row < cells[i].rows;row++)
			{
				for (int col = 0;col < cells[i].cols;col++)
				{
					uchar pixelValue_cell = cells[i].at<uchar>(row, col);
					if (0 == pixelValue_cell)
					{
						pixelNum_cell++;
					}
				}
			}
			pixelNum_cell = pixelNum_cell / float(cells[i].rows * cells[i].cols);
			digit_feature.push_back(pixelNum_cell);
		}

		//计算x方向的投影像素数，分为10个bin
		int bin = 10;
		float bin_y = height / bin;
		vector<Mat>bins_y;
		for (float row = 0.0; row < height; row += bin_y)
		{
			Rect bin_box(0, floor(row), width, floor(bin_y));
			Mat bin = digit(bin_box).clone();
			bins_y.push_back(bin);
			if (10 == bins_y.size())
			{
				break;
			}
		}
		for (int i = 0;i < bins_y.size();i++)
		{
			float pixelNum_bin = 0.0;
			for (int row = 0; row < bins_y[i].rows;row++)
			{
				for (int col = 0; col < bins_y[i].cols;col++)
				{
					uchar pixelVal_bin = bins_y[i].at<uchar>(row, col);
					if (0 == pixelVal_bin)
					{
						pixelNum_bin++;
					}
				}
			}
			pixelNum_bin = pixelNum_bin / float(bins_y[i].rows * bins_y[i].cols);
			digit_feature.push_back(pixelNum_bin);
		}

		//计算y方向的投影像素数，分为10个bin
		float bin_x = width / bin;
		vector<Mat>bins_x;
		for (float col = 0.0; col < width; col += bin_x)
		{
			if (bin_x < 1)
			{
				int new_bin_x = 1;
				int f_bin_x = new_bin_x - bin_x;
				Rect bin_box(floor(col), 0, new_bin_x, height);
				Mat bin = digit(bin_box).clone();
				bins_x.push_back(bin);
				if (9 == bins_x.size())
				{
					int flag = floor(f_bin_x * 10);
					bins_x.push_back(bins_x[flag]);
					break;
				}
			}
			else
			{
				Rect bin_box(floor(col), 0, floor(bin_x), height);
				Mat bin = digit(bin_box).clone();
				bins_x.push_back(bin);
				if (10 == bins_x.size())
				{
					break;
				}
			}
			
		}
		for (int i = 0;i < bins_x.size();i++)
		{
			float pixelNum_bin_y = 0.0;
			for (int row = 0; row < bins_x[i].rows;row++)
			{
				for (int col = 0; col < bins_x[i].cols;col++)
				{
					uchar pixelVal_bin = bins_x[i].at<uchar>(row, col);
					if (0 == pixelVal_bin)
					{
						pixelNum_bin_y++;
					}
				}
			}
			pixelNum_bin_y = pixelNum_bin_y / float(bins_x[i].rows * bins_x[i].cols);
			digit_feature.push_back(pixelNum_bin_y);
		}

		features.push_back(digit_feature);
		digit_feature.clear();
	}
	
	return features;
}


//计算某个数字的特征向量
vector<float> GetDigitFeature(Mat src)
{
	vector<float> digit_feature;
	Mat digit = src;
	//计算4x5网格内每个区域cell的前景像素数，并归一化，得到20个特征值
	float width = digit.cols;
	float height = digit.rows;
	//4x5网格分割
	float cell_w = float(width) / 4;
	float cell_h = float(height) / 5;
	vector<Mat>cells;
	for (float row = 0.0; row < height; row += cell_h)
	{
		for (float col = 0.0;col < width;col += cell_w)
		{
			int r = floor(row);
			int c = floor(col);
			Rect cell_box(c, r, floor(cell_w), floor(cell_h));
			Mat cell = digit(cell_box).clone();
			cells.push_back(cell);
		}
	}
	//计算每个cell中的背景像素数并做归一化
	for (int i = 0; i < cells.size();i++)
	{
		float pixelNum_cell = 0;
		for (int row = 0;row < cells[i].rows;row++)
		{
			for (int col = 0;col < cells[i].cols;col++)
			{
				uchar pixelValue_cell = cells[i].at<uchar>(row, col);
				if (0 == pixelValue_cell)
				{
					pixelNum_cell++;
				}
			}
		}
		pixelNum_cell = pixelNum_cell / float(cells[i].rows * cells[i].cols);
		digit_feature.push_back(pixelNum_cell);
	}

	//计算x方向的投影像素数，分为10个bin
	int bin = 10;
	float bin_y = height / bin;
	vector<Mat>bins_y;
	for (float row = 0.0; row < height; row += bin_y)
	{
		Rect bin_box(0, floor(row), width, floor(bin_y));
		Mat bin = digit(bin_box).clone();
		bins_y.push_back(bin);
		if (10 == bins_y.size())
		{
			break;
		}
	}
	for (int i = 0;i < bins_y.size();i++)
	{
		float pixelNum_bin = 0.0;
		for (int row = 0; row < bins_y[i].rows;row++)
		{
			for (int col = 0; col < bins_y[i].cols;col++)
			{
				uchar pixelVal_bin = bins_y[i].at<uchar>(row, col);
				if (0 == pixelVal_bin)
				{
					pixelNum_bin++;
				}
			}
		}
		pixelNum_bin = pixelNum_bin / float(bins_y[i].rows * bins_y[i].cols);
		digit_feature.push_back(pixelNum_bin);
	}

	//计算y方向的投影像素数，分为10个bin
	float bin_x = width / bin;
	vector<Mat>bins_x;
	for (float col = 0.0; col < width; col += bin_x)
	{
		Rect bin_box(floor(col), 0, floor(bin_x), height);
		Mat bin = digit(bin_box).clone();
		bins_x.push_back(bin);
		if (10 == bins_x.size())
		{
			break;
		}
	}
	for (int i = 0;i < bins_x.size();i++)
	{
		float pixelNum_bin_y = 0.0;
		for (int row = 0; row < bins_x[i].rows;row++)
		{
			for (int col = 0; col < bins_x[i].cols;col++)
			{
				uchar pixelVal_bin = bins_x[i].at<uchar>(row, col);
				if (0 == pixelVal_bin)
				{
					pixelNum_bin_y++;
				}
			}
		}
		pixelNum_bin_y = pixelNum_bin_y / float(bins_x[i].rows * bins_x[i].cols);
		digit_feature.push_back(pixelNum_bin_y);
	}

	return digit_feature;
}
