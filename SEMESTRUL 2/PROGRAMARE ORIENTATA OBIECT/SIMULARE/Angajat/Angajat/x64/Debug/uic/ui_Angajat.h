/********************************************************************************
** Form generated from reading UI file 'Angajat.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANGAJAT_H
#define UI_ANGAJAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AngajatClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *AngajatClass)
    {
        if (AngajatClass->objectName().isEmpty())
            AngajatClass->setObjectName("AngajatClass");
        AngajatClass->resize(600, 400);
        menuBar = new QMenuBar(AngajatClass);
        menuBar->setObjectName("menuBar");
        AngajatClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(AngajatClass);
        mainToolBar->setObjectName("mainToolBar");
        AngajatClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(AngajatClass);
        centralWidget->setObjectName("centralWidget");
        AngajatClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(AngajatClass);
        statusBar->setObjectName("statusBar");
        AngajatClass->setStatusBar(statusBar);

        retranslateUi(AngajatClass);

        QMetaObject::connectSlotsByName(AngajatClass);
    } // setupUi

    void retranslateUi(QMainWindow *AngajatClass)
    {
        AngajatClass->setWindowTitle(QCoreApplication::translate("AngajatClass", "Angajat", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AngajatClass: public Ui_AngajatClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANGAJAT_H
