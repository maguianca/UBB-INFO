/********************************************************************************
** Form generated from reading UI file 'Ex_Tractoare.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EX_TRACTOARE_H
#define UI_EX_TRACTOARE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Ex_TractoareClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Ex_TractoareClass)
    {
        if (Ex_TractoareClass->objectName().isEmpty())
            Ex_TractoareClass->setObjectName("Ex_TractoareClass");
        Ex_TractoareClass->resize(600, 400);
        menuBar = new QMenuBar(Ex_TractoareClass);
        menuBar->setObjectName("menuBar");
        Ex_TractoareClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Ex_TractoareClass);
        mainToolBar->setObjectName("mainToolBar");
        Ex_TractoareClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Ex_TractoareClass);
        centralWidget->setObjectName("centralWidget");
        Ex_TractoareClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Ex_TractoareClass);
        statusBar->setObjectName("statusBar");
        Ex_TractoareClass->setStatusBar(statusBar);

        retranslateUi(Ex_TractoareClass);

        QMetaObject::connectSlotsByName(Ex_TractoareClass);
    } // setupUi

    void retranslateUi(QMainWindow *Ex_TractoareClass)
    {
        Ex_TractoareClass->setWindowTitle(QCoreApplication::translate("Ex_TractoareClass", "Ex_Tractoare", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Ex_TractoareClass: public Ui_Ex_TractoareClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EX_TRACTOARE_H
