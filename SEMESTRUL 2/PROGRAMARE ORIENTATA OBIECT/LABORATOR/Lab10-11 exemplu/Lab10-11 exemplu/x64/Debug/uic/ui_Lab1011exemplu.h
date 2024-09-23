/********************************************************************************
** Form generated from reading UI file 'Lab1011exemplu.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAB1011EXEMPLU_H
#define UI_LAB1011EXEMPLU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lab1011exempluClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Lab1011exempluClass)
    {
        if (Lab1011exempluClass->objectName().isEmpty())
            Lab1011exempluClass->setObjectName("Lab1011exempluClass");
        Lab1011exempluClass->resize(600, 400);
        menuBar = new QMenuBar(Lab1011exempluClass);
        menuBar->setObjectName("menuBar");
        Lab1011exempluClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Lab1011exempluClass);
        mainToolBar->setObjectName("mainToolBar");
        Lab1011exempluClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Lab1011exempluClass);
        centralWidget->setObjectName("centralWidget");
        Lab1011exempluClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Lab1011exempluClass);
        statusBar->setObjectName("statusBar");
        Lab1011exempluClass->setStatusBar(statusBar);

        retranslateUi(Lab1011exempluClass);

        QMetaObject::connectSlotsByName(Lab1011exempluClass);
    } // setupUi

    void retranslateUi(QMainWindow *Lab1011exempluClass)
    {
        Lab1011exempluClass->setWindowTitle(QCoreApplication::translate("Lab1011exempluClass", "Lab1011exemplu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Lab1011exempluClass: public Ui_Lab1011exempluClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAB1011EXEMPLU_H
