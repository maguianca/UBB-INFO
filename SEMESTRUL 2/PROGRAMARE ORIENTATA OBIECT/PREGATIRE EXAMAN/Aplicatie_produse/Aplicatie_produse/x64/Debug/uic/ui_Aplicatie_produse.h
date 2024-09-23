/********************************************************************************
** Form generated from reading UI file 'Aplicatie_produse.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APLICATIE_PRODUSE_H
#define UI_APLICATIE_PRODUSE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Aplicatie_produseClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Aplicatie_produseClass)
    {
        if (Aplicatie_produseClass->objectName().isEmpty())
            Aplicatie_produseClass->setObjectName("Aplicatie_produseClass");
        Aplicatie_produseClass->resize(600, 400);
        menuBar = new QMenuBar(Aplicatie_produseClass);
        menuBar->setObjectName("menuBar");
        Aplicatie_produseClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Aplicatie_produseClass);
        mainToolBar->setObjectName("mainToolBar");
        Aplicatie_produseClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Aplicatie_produseClass);
        centralWidget->setObjectName("centralWidget");
        Aplicatie_produseClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Aplicatie_produseClass);
        statusBar->setObjectName("statusBar");
        Aplicatie_produseClass->setStatusBar(statusBar);

        retranslateUi(Aplicatie_produseClass);

        QMetaObject::connectSlotsByName(Aplicatie_produseClass);
    } // setupUi

    void retranslateUi(QMainWindow *Aplicatie_produseClass)
    {
        Aplicatie_produseClass->setWindowTitle(QCoreApplication::translate("Aplicatie_produseClass", "Aplicatie_produse", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Aplicatie_produseClass: public Ui_Aplicatie_produseClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APLICATIE_PRODUSE_H
