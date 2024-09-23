/********************************************************************************
** Form generated from reading UI file 'Tudor_Xsi0.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TUDOR_XSI0_H
#define UI_TUDOR_XSI0_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tudor_Xsi0Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Tudor_Xsi0Class)
    {
        if (Tudor_Xsi0Class->objectName().isEmpty())
            Tudor_Xsi0Class->setObjectName("Tudor_Xsi0Class");
        Tudor_Xsi0Class->resize(600, 400);
        menuBar = new QMenuBar(Tudor_Xsi0Class);
        menuBar->setObjectName("menuBar");
        Tudor_Xsi0Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Tudor_Xsi0Class);
        mainToolBar->setObjectName("mainToolBar");
        Tudor_Xsi0Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(Tudor_Xsi0Class);
        centralWidget->setObjectName("centralWidget");
        Tudor_Xsi0Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Tudor_Xsi0Class);
        statusBar->setObjectName("statusBar");
        Tudor_Xsi0Class->setStatusBar(statusBar);

        retranslateUi(Tudor_Xsi0Class);

        QMetaObject::connectSlotsByName(Tudor_Xsi0Class);
    } // setupUi

    void retranslateUi(QMainWindow *Tudor_Xsi0Class)
    {
        Tudor_Xsi0Class->setWindowTitle(QCoreApplication::translate("Tudor_Xsi0Class", "Tudor_Xsi0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Tudor_Xsi0Class: public Ui_Tudor_Xsi0Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TUDOR_XSI0_H
