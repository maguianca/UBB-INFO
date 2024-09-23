/********************************************************************************
** Form generated from reading UI file 'XsiO.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XSIO_H
#define UI_XSIO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_XsiOClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *XsiOClass)
    {
        if (XsiOClass->objectName().isEmpty())
            XsiOClass->setObjectName("XsiOClass");
        XsiOClass->resize(600, 400);
        menuBar = new QMenuBar(XsiOClass);
        menuBar->setObjectName("menuBar");
        XsiOClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(XsiOClass);
        mainToolBar->setObjectName("mainToolBar");
        XsiOClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(XsiOClass);
        centralWidget->setObjectName("centralWidget");
        XsiOClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(XsiOClass);
        statusBar->setObjectName("statusBar");
        XsiOClass->setStatusBar(statusBar);

        retranslateUi(XsiOClass);

        QMetaObject::connectSlotsByName(XsiOClass);
    } // setupUi

    void retranslateUi(QMainWindow *XsiOClass)
    {
        XsiOClass->setWindowTitle(QCoreApplication::translate("XsiOClass", "XsiO", nullptr));
    } // retranslateUi

};

namespace Ui {
    class XsiOClass: public Ui_XsiOClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XSIO_H
