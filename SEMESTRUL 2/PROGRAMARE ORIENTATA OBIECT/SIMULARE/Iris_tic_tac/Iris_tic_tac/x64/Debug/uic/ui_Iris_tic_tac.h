/********************************************************************************
** Form generated from reading UI file 'Iris_tic_tac.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IRIS_TIC_TAC_H
#define UI_IRIS_TIC_TAC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Iris_tic_tacClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Iris_tic_tacClass)
    {
        if (Iris_tic_tacClass->objectName().isEmpty())
            Iris_tic_tacClass->setObjectName("Iris_tic_tacClass");
        Iris_tic_tacClass->resize(600, 400);
        menuBar = new QMenuBar(Iris_tic_tacClass);
        menuBar->setObjectName("menuBar");
        Iris_tic_tacClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Iris_tic_tacClass);
        mainToolBar->setObjectName("mainToolBar");
        Iris_tic_tacClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Iris_tic_tacClass);
        centralWidget->setObjectName("centralWidget");
        Iris_tic_tacClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Iris_tic_tacClass);
        statusBar->setObjectName("statusBar");
        Iris_tic_tacClass->setStatusBar(statusBar);

        retranslateUi(Iris_tic_tacClass);

        QMetaObject::connectSlotsByName(Iris_tic_tacClass);
    } // setupUi

    void retranslateUi(QMainWindow *Iris_tic_tacClass)
    {
        Iris_tic_tacClass->setWindowTitle(QCoreApplication::translate("Iris_tic_tacClass", "Iris_tic_tac", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Iris_tic_tacClass: public Ui_Iris_tic_tacClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IRIS_TIC_TAC_H
