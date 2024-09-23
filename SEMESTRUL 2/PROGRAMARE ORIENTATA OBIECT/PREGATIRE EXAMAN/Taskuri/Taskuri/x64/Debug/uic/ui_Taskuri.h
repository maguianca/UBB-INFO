/********************************************************************************
** Form generated from reading UI file 'Taskuri.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKURI_H
#define UI_TASKURI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TaskuriClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TaskuriClass)
    {
        if (TaskuriClass->objectName().isEmpty())
            TaskuriClass->setObjectName("TaskuriClass");
        TaskuriClass->resize(600, 400);
        menuBar = new QMenuBar(TaskuriClass);
        menuBar->setObjectName("menuBar");
        TaskuriClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TaskuriClass);
        mainToolBar->setObjectName("mainToolBar");
        TaskuriClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(TaskuriClass);
        centralWidget->setObjectName("centralWidget");
        TaskuriClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(TaskuriClass);
        statusBar->setObjectName("statusBar");
        TaskuriClass->setStatusBar(statusBar);

        retranslateUi(TaskuriClass);

        QMetaObject::connectSlotsByName(TaskuriClass);
    } // setupUi

    void retranslateUi(QMainWindow *TaskuriClass)
    {
        TaskuriClass->setWindowTitle(QCoreApplication::translate("TaskuriClass", "Taskuri", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TaskuriClass: public Ui_TaskuriClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKURI_H
