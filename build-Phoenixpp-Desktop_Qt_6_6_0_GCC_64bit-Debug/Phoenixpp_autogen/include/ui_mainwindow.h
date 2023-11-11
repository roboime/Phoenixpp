/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_pic;
    QGroupBox *groupBox;
    QTextBrowser *textBrowser_3;
    QTextBrowser *textBrowser_4;
    QTextBrowser *textBrowser_5;
    QTextBrowser *textBrowser_6;
    QTextBrowser *textBrowser_7;
    QTextBrowser *textBrowser_8;
    QPushButton *Debug;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1201, 638);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        label_pic = new QLabel(centralwidget);
        label_pic->setObjectName("label_pic");

        horizontalLayout->addWidget(label_pic);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        textBrowser_3 = new QTextBrowser(groupBox);
        textBrowser_3->setObjectName("textBrowser_3");
        textBrowser_3->setGeometry(QRect(12, 32, 141, 41));
        textBrowser_4 = new QTextBrowser(groupBox);
        textBrowser_4->setObjectName("textBrowser_4");
        textBrowser_4->setGeometry(QRect(10, 80, 141, 41));
        textBrowser_5 = new QTextBrowser(groupBox);
        textBrowser_5->setObjectName("textBrowser_5");
        textBrowser_5->setGeometry(QRect(10, 130, 141, 41));
        textBrowser_6 = new QTextBrowser(groupBox);
        textBrowser_6->setObjectName("textBrowser_6");
        textBrowser_6->setGeometry(QRect(10, 180, 141, 41));
        textBrowser_7 = new QTextBrowser(groupBox);
        textBrowser_7->setObjectName("textBrowser_7");
        textBrowser_7->setGeometry(QRect(10, 230, 141, 41));
        textBrowser_8 = new QTextBrowser(groupBox);
        textBrowser_8->setObjectName("textBrowser_8");
        textBrowser_8->setGeometry(QRect(10, 280, 141, 41));
        Debug = new QPushButton(groupBox);
        Debug->setObjectName("Debug");
        Debug->setGeometry(QRect(10, 430, 80, 25));

        horizontalLayout->addWidget(groupBox);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_pic->setText(QCoreApplication::translate("MainWindow", "Imagem", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Robots Information", nullptr));
        Debug->setText(QCoreApplication::translate("MainWindow", "Debug", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
