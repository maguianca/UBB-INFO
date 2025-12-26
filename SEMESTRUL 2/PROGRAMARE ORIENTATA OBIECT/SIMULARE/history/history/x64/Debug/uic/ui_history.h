/********************************************************************************
** Form generated from reading UI file 'history.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTORY_H
#define UI_HISTORY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_historyClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *historyClass)
    {
        if (historyClass->objectName().isEmpty())
            historyClass->setObjectName("historyClass");
        historyClass->resize(600, 400);
        menuBar = new QMenuBar(historyClass);
        menuBar->setObjectName("menuBar");
        historyClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(historyClass);
        mainToolBar->setObjectName("mainToolBar");
        historyClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(historyClass);
        centralWidget->setObjectName("centralWidget");
        historyClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(historyClass);
        statusBar->setObjectName("statusBar");
        historyClass->setStatusBar(statusBar);

        retranslateUi(historyClass);

        QMetaObject::connectSlotsByName(historyClass);
    } // setupUi

    void retranslateUi(QMainWindow *historyClass)
    {
        historyClass->setWindowTitle(QCoreApplication::translate("historyClass", "history", nullptr));
    } // retranslateUi

};

namespace Ui {
    class historyClass: public Ui_historyClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTORY_H
