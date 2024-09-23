/********************************************************************************
** Form generated from reading UI file 'Melodii1.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MELODII1_H
#define UI_MELODII1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Melodii1Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Melodii1Class)
    {
        if (Melodii1Class->objectName().isEmpty())
            Melodii1Class->setObjectName("Melodii1Class");
        Melodii1Class->resize(600, 400);
        menuBar = new QMenuBar(Melodii1Class);
        menuBar->setObjectName("menuBar");
        Melodii1Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Melodii1Class);
        mainToolBar->setObjectName("mainToolBar");
        Melodii1Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(Melodii1Class);
        centralWidget->setObjectName("centralWidget");
        Melodii1Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Melodii1Class);
        statusBar->setObjectName("statusBar");
        Melodii1Class->setStatusBar(statusBar);

        retranslateUi(Melodii1Class);

        QMetaObject::connectSlotsByName(Melodii1Class);
    } // setupUi

    void retranslateUi(QMainWindow *Melodii1Class)
    {
        Melodii1Class->setWindowTitle(QCoreApplication::translate("Melodii1Class", "Melodii1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Melodii1Class: public Ui_Melodii1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MELODII1_H
