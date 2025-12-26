/********************************************************************************
** Form generated from reading UI file 'Simulare_jucator.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULARE_JUCATOR_H
#define UI_SIMULARE_JUCATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Simulare_jucatorClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Simulare_jucatorClass)
    {
        if (Simulare_jucatorClass->objectName().isEmpty())
            Simulare_jucatorClass->setObjectName("Simulare_jucatorClass");
        Simulare_jucatorClass->resize(600, 400);
        menuBar = new QMenuBar(Simulare_jucatorClass);
        menuBar->setObjectName("menuBar");
        Simulare_jucatorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Simulare_jucatorClass);
        mainToolBar->setObjectName("mainToolBar");
        Simulare_jucatorClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Simulare_jucatorClass);
        centralWidget->setObjectName("centralWidget");
        Simulare_jucatorClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Simulare_jucatorClass);
        statusBar->setObjectName("statusBar");
        Simulare_jucatorClass->setStatusBar(statusBar);

        retranslateUi(Simulare_jucatorClass);

        QMetaObject::connectSlotsByName(Simulare_jucatorClass);
    } // setupUi

    void retranslateUi(QMainWindow *Simulare_jucatorClass)
    {
        Simulare_jucatorClass->setWindowTitle(QCoreApplication::translate("Simulare_jucatorClass", "Simulare_jucator", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Simulare_jucatorClass: public Ui_Simulare_jucatorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULARE_JUCATOR_H
