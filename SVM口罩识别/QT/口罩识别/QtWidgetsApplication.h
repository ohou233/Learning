#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtWidgetsApplication.h"
#include<qlabel.h>
#include<qpushbutton.h>
#include<qimage.h>
#include<qpixmap.h>
#include<opencv.hpp>
#include<string>

using namespace cv;
using namespace std;

class QtWidgetsApplication : public QWidget
{
    Q_OBJECT

public:
    QtWidgetsApplication(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtWidgetsApplicationClass ui;
   

private slots:
};
