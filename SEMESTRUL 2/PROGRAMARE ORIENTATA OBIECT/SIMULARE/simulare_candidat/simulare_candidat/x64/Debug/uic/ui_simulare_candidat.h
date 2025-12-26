/********************************************************************************
** Form generated from reading UI file 'simulare_candidat.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULARE_CANDIDAT_H
#define UI_SIMULARE_CANDIDAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_simulare_candidatClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *simulare_candidatClass)
    {
        if (simulare_candidatClass->objectName().isEmpty())
            simulare_candidatClass->setObjectName("simulare_candidatClass");
        simulare_candidatClass->resize(600, 400);
        menuBar = new QMenuBar(simulare_candidatClass);
        menuBar->setObjectName("menuBar");
        simulare_candidatClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(simulare_candidatClass);
        mainToolBar->setObjectName("mainToolBar");
        simulare_candidatClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(simulare_candidatClass);
        centralWidget->setObjectName("centralWidget");
        simulare_candidatClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(simulare_candidatClass);
        statusBar->setObjectName("statusBar");
        simulare_candidatClass->setStatusBar(statusBar);

        retranslateUi(simulare_candidatClass);

        QMetaObject::connectSlotsByName(simulare_candidatClass);
    } // setupUi

    void retranslateUi(QMainWindow *simulare_candidatClass)
    {
        simulare_candidatClass->setWindowTitle(QCoreApplication::translate("simulare_candidatClass", "simulare_candidat", nullptr));
    } // retranslateUi

};

namespace Ui {
    class simulare_candidatClass: public Ui_simulare_candidatClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULARE_CANDIDAT_H
