/********************************************************************************
** Form generated from reading UI file 'Exemplucutremur.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXEMPLUCUTREMUR_H
#define UI_EXEMPLUCUTREMUR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExemplucutremurClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ExemplucutremurClass)
    {
        if (ExemplucutremurClass->objectName().isEmpty())
            ExemplucutremurClass->setObjectName("ExemplucutremurClass");
        ExemplucutremurClass->resize(600, 400);
        menuBar = new QMenuBar(ExemplucutremurClass);
        menuBar->setObjectName("menuBar");
        ExemplucutremurClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ExemplucutremurClass);
        mainToolBar->setObjectName("mainToolBar");
        ExemplucutremurClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ExemplucutremurClass);
        centralWidget->setObjectName("centralWidget");
        ExemplucutremurClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ExemplucutremurClass);
        statusBar->setObjectName("statusBar");
        ExemplucutremurClass->setStatusBar(statusBar);

        retranslateUi(ExemplucutremurClass);

        QMetaObject::connectSlotsByName(ExemplucutremurClass);
    } // setupUi

    void retranslateUi(QMainWindow *ExemplucutremurClass)
    {
        ExemplucutremurClass->setWindowTitle(QCoreApplication::translate("ExemplucutremurClass", "Exemplucutremur", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExemplucutremurClass: public Ui_ExemplucutremurClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXEMPLUCUTREMUR_H
