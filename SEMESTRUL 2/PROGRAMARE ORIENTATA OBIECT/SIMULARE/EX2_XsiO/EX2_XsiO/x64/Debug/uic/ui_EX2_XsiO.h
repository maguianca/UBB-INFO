/********************************************************************************
** Form generated from reading UI file 'EX2_XsiO.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EX2_XSIO_H
#define UI_EX2_XSIO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EX2_XsiOClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EX2_XsiOClass)
    {
        if (EX2_XsiOClass->objectName().isEmpty())
            EX2_XsiOClass->setObjectName("EX2_XsiOClass");
        EX2_XsiOClass->resize(600, 400);
        menuBar = new QMenuBar(EX2_XsiOClass);
        menuBar->setObjectName("menuBar");
        EX2_XsiOClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(EX2_XsiOClass);
        mainToolBar->setObjectName("mainToolBar");
        EX2_XsiOClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(EX2_XsiOClass);
        centralWidget->setObjectName("centralWidget");
        EX2_XsiOClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(EX2_XsiOClass);
        statusBar->setObjectName("statusBar");
        EX2_XsiOClass->setStatusBar(statusBar);

        retranslateUi(EX2_XsiOClass);

        QMetaObject::connectSlotsByName(EX2_XsiOClass);
    } // setupUi

    void retranslateUi(QMainWindow *EX2_XsiOClass)
    {
        EX2_XsiOClass->setWindowTitle(QCoreApplication::translate("EX2_XsiOClass", "EX2_XsiO", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EX2_XsiOClass: public Ui_EX2_XsiOClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EX2_XSIO_H
