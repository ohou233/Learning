/********************************************************************************
** Form generated from reading UI file 'QtWidgetsApplication.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTWIDGETSAPPLICATION_H
#define UI_QTWIDGETSAPPLICATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtWidgetsApplicationClass
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton1;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton3;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label;

    void setupUi(QWidget *QtWidgetsApplicationClass)
    {
        if (QtWidgetsApplicationClass->objectName().isEmpty())
            QtWidgetsApplicationClass->setObjectName(QString::fromUtf8("QtWidgetsApplicationClass"));
        QtWidgetsApplicationClass->resize(800, 600);
        QtWidgetsApplicationClass->setMinimumSize(QSize(800, 600));
        QtWidgetsApplicationClass->setMaximumSize(QSize(800, 600));
        widget = new QWidget(QtWidgetsApplicationClass);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(180, 450, 431, 141));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton1 = new QPushButton(widget);
        pushButton1->setObjectName(QString::fromUtf8("pushButton1"));
        pushButton1->setMinimumSize(QSize(100, 50));

        horizontalLayout->addWidget(pushButton1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton2 = new QPushButton(widget);
        pushButton2->setObjectName(QString::fromUtf8("pushButton2"));
        pushButton2->setMinimumSize(QSize(100, 50));

        horizontalLayout->addWidget(pushButton2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton3 = new QPushButton(widget);
        pushButton3->setObjectName(QString::fromUtf8("pushButton3"));
        pushButton3->setMinimumSize(QSize(100, 50));

        horizontalLayout->addWidget(pushButton3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        label = new QLabel(QtWidgetsApplicationClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(100, 30, 600, 400));
        label->setMinimumSize(QSize(600, 400));
        label->setMaximumSize(QSize(600, 400));

        retranslateUi(QtWidgetsApplicationClass);

        QMetaObject::connectSlotsByName(QtWidgetsApplicationClass);
    } // setupUi

    void retranslateUi(QWidget *QtWidgetsApplicationClass)
    {
        QtWidgetsApplicationClass->setWindowTitle(QCoreApplication::translate("QtWidgetsApplicationClass", "QtWidgetsApplication", nullptr));
        pushButton1->setText(QCoreApplication::translate("QtWidgetsApplicationClass", "\346\211\223\345\274\200\346\221\204\345\203\217\345\244\264", nullptr));
        pushButton2->setText(QCoreApplication::translate("QtWidgetsApplicationClass", "\345\205\263\351\227\255\346\221\204\345\203\217\345\244\264", nullptr));
        pushButton3->setText(QCoreApplication::translate("QtWidgetsApplicationClass", "\345\217\243\347\275\251\346\243\200\346\265\213", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QtWidgetsApplicationClass: public Ui_QtWidgetsApplicationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTWIDGETSAPPLICATION_H
