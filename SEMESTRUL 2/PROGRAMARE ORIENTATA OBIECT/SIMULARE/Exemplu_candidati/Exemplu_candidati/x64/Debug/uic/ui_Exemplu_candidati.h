/********************************************************************************
** Form generated from reading UI file 'Exemplu_candidati.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXEMPLU_CANDIDATI_H
#define UI_EXEMPLU_CANDIDATI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Exemplu_candidatiClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Exemplu_candidatiClass)
    {
        if (Exemplu_candidatiClass->objectName().isEmpty())
            Exemplu_candidatiClass->setObjectName("Exemplu_candidatiClass");
        Exemplu_candidatiClass->resize(600, 400);
        menuBar = new QMenuBar(Exemplu_candidatiClass);
        menuBar->setObjectName("menuBar");
        Exemplu_candidatiClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Exemplu_candidatiClass);
        mainToolBar->setObjectName("mainToolBar");
        Exemplu_candidatiClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Exemplu_candidatiClass);
        centralWidget->setObjectName("centralWidget");
        Exemplu_candidatiClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Exemplu_candidatiClass);
        statusBar->setObjectName("statusBar");
        Exemplu_candidatiClass->setStatusBar(statusBar);

        retranslateUi(Exemplu_candidatiClass);

        QMetaObject::connectSlotsByName(Exemplu_candidatiClass);
    } // setupUi

    void retranslateUi(QMainWindow *Exemplu_candidatiClass)
    {
        Exemplu_candidatiClass->setWindowTitle(QCoreApplication::translate("Exemplu_candidatiClass", "Exemplu_candidati", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Exemplu_candidatiClass: public Ui_Exemplu_candidatiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXEMPLU_CANDIDATI_H
