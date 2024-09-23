/********************************************************************************
** Form generated from reading UI file 'Produse2.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRODUSE2_H
#define UI_PRODUSE2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Produse2Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Produse2Class)
    {
        if (Produse2Class->objectName().isEmpty())
            Produse2Class->setObjectName("Produse2Class");
        Produse2Class->resize(600, 400);
        menuBar = new QMenuBar(Produse2Class);
        menuBar->setObjectName("menuBar");
        Produse2Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Produse2Class);
        mainToolBar->setObjectName("mainToolBar");
        Produse2Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(Produse2Class);
        centralWidget->setObjectName("centralWidget");
        Produse2Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Produse2Class);
        statusBar->setObjectName("statusBar");
        Produse2Class->setStatusBar(statusBar);

        retranslateUi(Produse2Class);

        QMetaObject::connectSlotsByName(Produse2Class);
    } // setupUi

    void retranslateUi(QMainWindow *Produse2Class)
    {
        Produse2Class->setWindowTitle(QCoreApplication::translate("Produse2Class", "Produse2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Produse2Class: public Ui_Produse2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRODUSE2_H
