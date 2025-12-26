/********************************************************************************
** Form generated from reading UI file 'Simulare_briciu.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULARE_BRICIU_H
#define UI_SIMULARE_BRICIU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Simulare_briciuClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Simulare_briciuClass)
    {
        if (Simulare_briciuClass->objectName().isEmpty())
            Simulare_briciuClass->setObjectName("Simulare_briciuClass");
        Simulare_briciuClass->resize(600, 400);
        menuBar = new QMenuBar(Simulare_briciuClass);
        menuBar->setObjectName("menuBar");
        Simulare_briciuClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Simulare_briciuClass);
        mainToolBar->setObjectName("mainToolBar");
        Simulare_briciuClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Simulare_briciuClass);
        centralWidget->setObjectName("centralWidget");
        Simulare_briciuClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Simulare_briciuClass);
        statusBar->setObjectName("statusBar");
        Simulare_briciuClass->setStatusBar(statusBar);

        retranslateUi(Simulare_briciuClass);

        QMetaObject::connectSlotsByName(Simulare_briciuClass);
    } // setupUi

    void retranslateUi(QMainWindow *Simulare_briciuClass)
    {
        Simulare_briciuClass->setWindowTitle(QCoreApplication::translate("Simulare_briciuClass", "Simulare_briciu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Simulare_briciuClass: public Ui_Simulare_briciuClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULARE_BRICIU_H
