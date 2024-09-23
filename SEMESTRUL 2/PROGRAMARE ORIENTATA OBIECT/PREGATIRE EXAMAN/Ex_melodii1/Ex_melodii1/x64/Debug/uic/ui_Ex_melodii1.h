/********************************************************************************
** Form generated from reading UI file 'Ex_melodii1.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EX_MELODII1_H
#define UI_EX_MELODII1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Ex_melodii1Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Ex_melodii1Class)
    {
        if (Ex_melodii1Class->objectName().isEmpty())
            Ex_melodii1Class->setObjectName("Ex_melodii1Class");
        Ex_melodii1Class->resize(600, 400);
        menuBar = new QMenuBar(Ex_melodii1Class);
        menuBar->setObjectName("menuBar");
        Ex_melodii1Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Ex_melodii1Class);
        mainToolBar->setObjectName("mainToolBar");
        Ex_melodii1Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(Ex_melodii1Class);
        centralWidget->setObjectName("centralWidget");
        Ex_melodii1Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Ex_melodii1Class);
        statusBar->setObjectName("statusBar");
        Ex_melodii1Class->setStatusBar(statusBar);

        retranslateUi(Ex_melodii1Class);

        QMetaObject::connectSlotsByName(Ex_melodii1Class);
    } // setupUi

    void retranslateUi(QMainWindow *Ex_melodii1Class)
    {
        Ex_melodii1Class->setWindowTitle(QCoreApplication::translate("Ex_melodii1Class", "Ex_melodii1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Ex_melodii1Class: public Ui_Ex_melodii1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EX_MELODII1_H
