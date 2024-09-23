/********************************************************************************
** Form generated from reading UI file 'Ex_melodii2.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EX_MELODII2_H
#define UI_EX_MELODII2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Ex_melodii2Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Ex_melodii2Class)
    {
        if (Ex_melodii2Class->objectName().isEmpty())
            Ex_melodii2Class->setObjectName("Ex_melodii2Class");
        Ex_melodii2Class->resize(600, 400);
        menuBar = new QMenuBar(Ex_melodii2Class);
        menuBar->setObjectName("menuBar");
        Ex_melodii2Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Ex_melodii2Class);
        mainToolBar->setObjectName("mainToolBar");
        Ex_melodii2Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(Ex_melodii2Class);
        centralWidget->setObjectName("centralWidget");
        Ex_melodii2Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Ex_melodii2Class);
        statusBar->setObjectName("statusBar");
        Ex_melodii2Class->setStatusBar(statusBar);

        retranslateUi(Ex_melodii2Class);

        QMetaObject::connectSlotsByName(Ex_melodii2Class);
    } // setupUi

    void retranslateUi(QMainWindow *Ex_melodii2Class)
    {
        Ex_melodii2Class->setWindowTitle(QCoreApplication::translate("Ex_melodii2Class", "Ex_melodii2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Ex_melodii2Class: public Ui_Ex_melodii2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EX_MELODII2_H
