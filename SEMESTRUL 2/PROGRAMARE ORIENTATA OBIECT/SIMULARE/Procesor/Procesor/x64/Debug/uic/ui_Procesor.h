/********************************************************************************
** Form generated from reading UI file 'Procesor.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROCESOR_H
#define UI_PROCESOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProcesorClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ProcesorClass)
    {
        if (ProcesorClass->objectName().isEmpty())
            ProcesorClass->setObjectName("ProcesorClass");
        ProcesorClass->resize(600, 400);
        menuBar = new QMenuBar(ProcesorClass);
        menuBar->setObjectName("menuBar");
        ProcesorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ProcesorClass);
        mainToolBar->setObjectName("mainToolBar");
        ProcesorClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ProcesorClass);
        centralWidget->setObjectName("centralWidget");
        ProcesorClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ProcesorClass);
        statusBar->setObjectName("statusBar");
        ProcesorClass->setStatusBar(statusBar);

        retranslateUi(ProcesorClass);

        QMetaObject::connectSlotsByName(ProcesorClass);
    } // setupUi

    void retranslateUi(QMainWindow *ProcesorClass)
    {
        ProcesorClass->setWindowTitle(QCoreApplication::translate("ProcesorClass", "Procesor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProcesorClass: public Ui_ProcesorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROCESOR_H
