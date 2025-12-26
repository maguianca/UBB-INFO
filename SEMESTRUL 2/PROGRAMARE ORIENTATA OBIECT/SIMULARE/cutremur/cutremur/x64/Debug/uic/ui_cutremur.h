/********************************************************************************
** Form generated from reading UI file 'cutremur.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUTREMUR_H
#define UI_CUTREMUR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cutremurClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *cutremurClass)
    {
        if (cutremurClass->objectName().isEmpty())
            cutremurClass->setObjectName("cutremurClass");
        cutremurClass->resize(600, 400);
        menuBar = new QMenuBar(cutremurClass);
        menuBar->setObjectName("menuBar");
        cutremurClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(cutremurClass);
        mainToolBar->setObjectName("mainToolBar");
        cutremurClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(cutremurClass);
        centralWidget->setObjectName("centralWidget");
        cutremurClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(cutremurClass);
        statusBar->setObjectName("statusBar");
        cutremurClass->setStatusBar(statusBar);

        retranslateUi(cutremurClass);

        QMetaObject::connectSlotsByName(cutremurClass);
    } // setupUi

    void retranslateUi(QMainWindow *cutremurClass)
    {
        cutremurClass->setWindowTitle(QCoreApplication::translate("cutremurClass", "cutremur", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cutremurClass: public Ui_cutremurClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUTREMUR_H
