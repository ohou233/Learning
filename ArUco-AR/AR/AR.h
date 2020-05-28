#pragma once

#include <QtWidgets/QWidget>
#include<opencv.hpp>
#include<vector>
#include<stdio.h>
#include "ui_AR.h"
using namespace cv;
using namespace std;

class AR : public QWidget
{
    Q_OBJECT

public:
    AR(QWidget *parent = Q_NULLPTR);
    Mat frame;
    Mat videoFrame;
    Mat H;
    Mat mask_mat;
    vector<Point2f> new_image_box;

private:
    Ui::ARClass ui;

};
