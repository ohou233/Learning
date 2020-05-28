/********************************************************************************
** Form generated from reading UI file 'AR.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AR_H
#define UI_AR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ARClass
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton1;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton3;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label1;
    QLabel *label2;

    void setupUi(QWidget *ARClass)
    {
        if (ARClass->objectName().isEmpty())
            ARClass->setObjectName(QString::fromUtf8("ARClass"));
        ARClass->resize(900, 600);
        ARClass->setMinimumSize(QSize(900, 600));
        ARClass->setMaximumSize(QSize(900, 600));
        widget = new QWidget(ARClass);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(170, 440, 581, 131));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton1 = new QPushButton(widget);
        pushButton1->setObjectName(QString::fromUtf8("pushButton1"));
        pushButton1->setMinimumSize(QSize(100, 50));
        pushButton1->setMaximumSize(QSize(100, 50));

        horizontalLayout->addWidget(pushButton1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton2 = new QPushButton(widget);
        pushButton2->setObjectName(QString::fromUtf8("pushButton2"));
        pushButton2->setMinimumSize(QSize(100, 50));
        pushButton2->setMaximumSize(QSize(100, 50));

        horizontalLayout->addWidget(pushButton2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        pushButton3 = new QPushButton(widget);
        pushButton3->setObjectName(QString::fromUtf8("pushButton3"));
        pushButton3->setMinimumSize(QSize(100, 50));
        pushButton3->setMaximumSize(QSize(100, 50));

        horizontalLayout->addWidget(pushButton3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        label1 = new QLabel(ARClass);
        label1->setObjectName(QString::fromUtf8("label1"));
        label1->setGeometry(QRect(10, 30, 440, 390));
        label1->setFrameShape(QFrame::WinPanel);
        label1->setFrameShadow(QFrame::Plain);
        label2 = new QLabel(ARClass);
        label2->setObjectName(QString::fromUtf8("label2"));
        label2->setGeometry(QRect(460, 30, 440, 390));
        label2->setFrameShape(QFrame::WinPanel);
        label2->setFrameShadow(QFrame::Plain);

        retranslateUi(ARClass);

        QMetaObject::connectSlotsByName(ARClass);
    } // setupUi

    void retranslateUi(QWidget *ARClass)
    {
        ARClass->setWindowTitle(QCoreApplication::translate("ARClass", "AR", nullptr));
        pushButton1->setText(QCoreApplication::translate("ARClass", "\345\274\200\345\220\257\346\221\204\345\203\217\345\244\264", nullptr));
        pushButton2->setText(QCoreApplication::translate("ARClass", "\345\242\236\345\274\272\347\216\260\345\256\236", nullptr));
        pushButton3->setText(QCoreApplication::translate("ARClass", "\345\205\263\351\227\255\346\221\204\345\203\217\345\244\264", nullptr));
        label1->setText(QString());
        label2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ARClass: public Ui_ARClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AR_H
