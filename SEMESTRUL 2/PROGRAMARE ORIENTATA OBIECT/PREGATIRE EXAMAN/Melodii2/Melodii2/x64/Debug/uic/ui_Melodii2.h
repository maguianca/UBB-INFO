/********************************************************************************
** Form generated from reading UI file 'Melodii2.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MELODII2_H
#define UI_MELODII2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Melodii2Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Melodii2Class)
    {
        if (Melodii2Class->objectName().isEmpty())
            Melodii2Class->setObjectName("Melodii2Class");
        Melodii2Class->resize(600, 400);
        menuBar = new QMenuBar(Melodii2Class);
        menuBar->setObjectName("menuBar");
        Melodii2Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Melodii2Class);
        mainToolBar->setObjectName("mainToolBar");
        Melodii2Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(Melodii2Class);
        centralWidget->setObjectName("centralWidget");
        Melodii2Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Melodii2Class);
        statusBar->setObjectName("statusBar");
        Melodii2Class->setStatusBar(statusBar);

        retranslateUi(Melodii2Class);

        QMetaObject::connectSlotsByName(Melodii2Class);
    } // setupUi

    void retranslateUi(QMainWindow *Melodii2Class)
    {
        Melodii2Class->setWindowTitle(QCoreApplication::translate("Melodii2Class", "Melodii2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Melodii2Class: public Ui_Melodii2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MELODII2_H
