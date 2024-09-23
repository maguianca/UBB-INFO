/********************************************************************************
** Form generated from reading UI file 'Tractoare.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRACTOARE_H
#define UI_TRACTOARE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TractoareClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TractoareClass)
    {
        if (TractoareClass->objectName().isEmpty())
            TractoareClass->setObjectName("TractoareClass");
        TractoareClass->resize(600, 400);
        menuBar = new QMenuBar(TractoareClass);
        menuBar->setObjectName("menuBar");
        TractoareClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TractoareClass);
        mainToolBar->setObjectName("mainToolBar");
        TractoareClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(TractoareClass);
        centralWidget->setObjectName("centralWidget");
        TractoareClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(TractoareClass);
        statusBar->setObjectName("statusBar");
        TractoareClass->setStatusBar(statusBar);

        retranslateUi(TractoareClass);

        QMetaObject::connectSlotsByName(TractoareClass);
    } // setupUi

    void retranslateUi(QMainWindow *TractoareClass)
    {
        TractoareClass->setWindowTitle(QCoreApplication::translate("TractoareClass", "Tractoare", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TractoareClass: public Ui_TractoareClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACTOARE_H
