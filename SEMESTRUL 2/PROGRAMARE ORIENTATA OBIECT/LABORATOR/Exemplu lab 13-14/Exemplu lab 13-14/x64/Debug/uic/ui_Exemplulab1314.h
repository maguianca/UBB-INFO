/********************************************************************************
** Form generated from reading UI file 'Exemplulab1314.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXEMPLULAB1314_H
#define UI_EXEMPLULAB1314_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Exemplulab1314Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Exemplulab1314Class)
    {
        if (Exemplulab1314Class->objectName().isEmpty())
            Exemplulab1314Class->setObjectName("Exemplulab1314Class");
        Exemplulab1314Class->resize(600, 400);
        menuBar = new QMenuBar(Exemplulab1314Class);
        menuBar->setObjectName("menuBar");
        Exemplulab1314Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Exemplulab1314Class);
        mainToolBar->setObjectName("mainToolBar");
        Exemplulab1314Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(Exemplulab1314Class);
        centralWidget->setObjectName("centralWidget");
        Exemplulab1314Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Exemplulab1314Class);
        statusBar->setObjectName("statusBar");
        Exemplulab1314Class->setStatusBar(statusBar);

        retranslateUi(Exemplulab1314Class);

        QMetaObject::connectSlotsByName(Exemplulab1314Class);
    } // setupUi

    void retranslateUi(QMainWindow *Exemplulab1314Class)
    {
        Exemplulab1314Class->setWindowTitle(QCoreApplication::translate("Exemplulab1314Class", "Exemplulab1314", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Exemplulab1314Class: public Ui_Exemplulab1314Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXEMPLULAB1314_H
