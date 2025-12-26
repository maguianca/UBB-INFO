/********************************************************************************
** Form generated from reading UI file 'ExempluSimulareAbonament.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXEMPLUSIMULAREABONAMENT_H
#define UI_EXEMPLUSIMULAREABONAMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExempluSimulareAbonamentClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ExempluSimulareAbonamentClass)
    {
        if (ExempluSimulareAbonamentClass->objectName().isEmpty())
            ExempluSimulareAbonamentClass->setObjectName("ExempluSimulareAbonamentClass");
        ExempluSimulareAbonamentClass->resize(600, 400);
        menuBar = new QMenuBar(ExempluSimulareAbonamentClass);
        menuBar->setObjectName("menuBar");
        ExempluSimulareAbonamentClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ExempluSimulareAbonamentClass);
        mainToolBar->setObjectName("mainToolBar");
        ExempluSimulareAbonamentClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ExempluSimulareAbonamentClass);
        centralWidget->setObjectName("centralWidget");
        ExempluSimulareAbonamentClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ExempluSimulareAbonamentClass);
        statusBar->setObjectName("statusBar");
        ExempluSimulareAbonamentClass->setStatusBar(statusBar);

        retranslateUi(ExempluSimulareAbonamentClass);

        QMetaObject::connectSlotsByName(ExempluSimulareAbonamentClass);
    } // setupUi

    void retranslateUi(QMainWindow *ExempluSimulareAbonamentClass)
    {
        ExempluSimulareAbonamentClass->setWindowTitle(QCoreApplication::translate("ExempluSimulareAbonamentClass", "ExempluSimulareAbonament", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExempluSimulareAbonamentClass: public Ui_ExempluSimulareAbonamentClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXEMPLUSIMULAREABONAMENT_H
