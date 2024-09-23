/********************************************************************************
** Form generated from reading UI file 'Exercitiu_produse2.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXERCITIU_PRODUSE2_H
#define UI_EXERCITIU_PRODUSE2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Exercitiu_produse2Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Exercitiu_produse2Class)
    {
        if (Exercitiu_produse2Class->objectName().isEmpty())
            Exercitiu_produse2Class->setObjectName("Exercitiu_produse2Class");
        Exercitiu_produse2Class->resize(600, 400);
        menuBar = new QMenuBar(Exercitiu_produse2Class);
        menuBar->setObjectName("menuBar");
        Exercitiu_produse2Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Exercitiu_produse2Class);
        mainToolBar->setObjectName("mainToolBar");
        Exercitiu_produse2Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(Exercitiu_produse2Class);
        centralWidget->setObjectName("centralWidget");
        Exercitiu_produse2Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Exercitiu_produse2Class);
        statusBar->setObjectName("statusBar");
        Exercitiu_produse2Class->setStatusBar(statusBar);

        retranslateUi(Exercitiu_produse2Class);

        QMetaObject::connectSlotsByName(Exercitiu_produse2Class);
    } // setupUi

    void retranslateUi(QMainWindow *Exercitiu_produse2Class)
    {
        Exercitiu_produse2Class->setWindowTitle(QCoreApplication::translate("Exercitiu_produse2Class", "Exercitiu_produse2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Exercitiu_produse2Class: public Ui_Exercitiu_produse2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXERCITIU_PRODUSE2_H
