/********************************************************************************
** Form generated from reading UI file 'SimulareApartamente.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULAREAPARTAMENTE_H
#define UI_SIMULAREAPARTAMENTE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimulareApartamenteClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SimulareApartamenteClass)
    {
        if (SimulareApartamenteClass->objectName().isEmpty())
            SimulareApartamenteClass->setObjectName("SimulareApartamenteClass");
        SimulareApartamenteClass->resize(600, 400);
        menuBar = new QMenuBar(SimulareApartamenteClass);
        menuBar->setObjectName("menuBar");
        SimulareApartamenteClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SimulareApartamenteClass);
        mainToolBar->setObjectName("mainToolBar");
        SimulareApartamenteClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(SimulareApartamenteClass);
        centralWidget->setObjectName("centralWidget");
        SimulareApartamenteClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(SimulareApartamenteClass);
        statusBar->setObjectName("statusBar");
        SimulareApartamenteClass->setStatusBar(statusBar);

        retranslateUi(SimulareApartamenteClass);

        QMetaObject::connectSlotsByName(SimulareApartamenteClass);
    } // setupUi

    void retranslateUi(QMainWindow *SimulareApartamenteClass)
    {
        SimulareApartamenteClass->setWindowTitle(QCoreApplication::translate("SimulareApartamenteClass", "SimulareApartamente", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SimulareApartamenteClass: public Ui_SimulareApartamenteClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULAREAPARTAMENTE_H
