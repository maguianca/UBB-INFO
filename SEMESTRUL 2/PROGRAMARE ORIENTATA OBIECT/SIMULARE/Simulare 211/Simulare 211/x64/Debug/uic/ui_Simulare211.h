/********************************************************************************
** Form generated from reading UI file 'Simulare211.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULARE211_H
#define UI_SIMULARE211_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Simulare211Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Simulare211Class)
    {
        if (Simulare211Class->objectName().isEmpty())
            Simulare211Class->setObjectName("Simulare211Class");
        Simulare211Class->resize(600, 400);
        menuBar = new QMenuBar(Simulare211Class);
        menuBar->setObjectName("menuBar");
        Simulare211Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Simulare211Class);
        mainToolBar->setObjectName("mainToolBar");
        Simulare211Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(Simulare211Class);
        centralWidget->setObjectName("centralWidget");
        Simulare211Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Simulare211Class);
        statusBar->setObjectName("statusBar");
        Simulare211Class->setStatusBar(statusBar);

        retranslateUi(Simulare211Class);

        QMetaObject::connectSlotsByName(Simulare211Class);
    } // setupUi

    void retranslateUi(QMainWindow *Simulare211Class)
    {
        Simulare211Class->setWindowTitle(QCoreApplication::translate("Simulare211Class", "Simulare211", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Simulare211Class: public Ui_Simulare211Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULARE211_H
