/********************************************************************************
** Form generated from reading UI file 'Elevi.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ELEVI_H
#define UI_ELEVI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EleviClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EleviClass)
    {
        if (EleviClass->objectName().isEmpty())
            EleviClass->setObjectName("EleviClass");
        EleviClass->resize(600, 400);
        menuBar = new QMenuBar(EleviClass);
        menuBar->setObjectName("menuBar");
        EleviClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(EleviClass);
        mainToolBar->setObjectName("mainToolBar");
        EleviClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(EleviClass);
        centralWidget->setObjectName("centralWidget");
        EleviClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(EleviClass);
        statusBar->setObjectName("statusBar");
        EleviClass->setStatusBar(statusBar);

        retranslateUi(EleviClass);

        QMetaObject::connectSlotsByName(EleviClass);
    } // setupUi

    void retranslateUi(QMainWindow *EleviClass)
    {
        EleviClass->setWindowTitle(QCoreApplication::translate("EleviClass", "Elevi", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EleviClass: public Ui_EleviClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ELEVI_H
