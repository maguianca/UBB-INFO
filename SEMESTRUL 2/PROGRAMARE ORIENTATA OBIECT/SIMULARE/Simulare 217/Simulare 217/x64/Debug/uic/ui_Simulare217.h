/********************************************************************************
** Form generated from reading UI file 'Simulare217.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULARE217_H
#define UI_SIMULARE217_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Simulare217Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Simulare217Class)
    {
        if (Simulare217Class->objectName().isEmpty())
            Simulare217Class->setObjectName("Simulare217Class");
        Simulare217Class->resize(600, 400);
        menuBar = new QMenuBar(Simulare217Class);
        menuBar->setObjectName("menuBar");
        Simulare217Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Simulare217Class);
        mainToolBar->setObjectName("mainToolBar");
        Simulare217Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(Simulare217Class);
        centralWidget->setObjectName("centralWidget");
        Simulare217Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Simulare217Class);
        statusBar->setObjectName("statusBar");
        Simulare217Class->setStatusBar(statusBar);

        retranslateUi(Simulare217Class);

        QMetaObject::connectSlotsByName(Simulare217Class);
    } // setupUi

    void retranslateUi(QMainWindow *Simulare217Class)
    {
        Simulare217Class->setWindowTitle(QCoreApplication::translate("Simulare217Class", "Simulare217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Simulare217Class: public Ui_Simulare217Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULARE217_H
