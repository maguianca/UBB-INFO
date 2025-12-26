/********************************************************************************
** Form generated from reading UI file 'Simulare216.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULARE216_H
#define UI_SIMULARE216_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Simulare216Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Simulare216Class)
    {
        if (Simulare216Class->objectName().isEmpty())
            Simulare216Class->setObjectName("Simulare216Class");
        Simulare216Class->resize(600, 400);
        menuBar = new QMenuBar(Simulare216Class);
        menuBar->setObjectName("menuBar");
        Simulare216Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Simulare216Class);
        mainToolBar->setObjectName("mainToolBar");
        Simulare216Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(Simulare216Class);
        centralWidget->setObjectName("centralWidget");
        Simulare216Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Simulare216Class);
        statusBar->setObjectName("statusBar");
        Simulare216Class->setStatusBar(statusBar);

        retranslateUi(Simulare216Class);

        QMetaObject::connectSlotsByName(Simulare216Class);
    } // setupUi

    void retranslateUi(QMainWindow *Simulare216Class)
    {
        Simulare216Class->setWindowTitle(QCoreApplication::translate("Simulare216Class", "Simulare216", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Simulare216Class: public Ui_Simulare216Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULARE216_H
