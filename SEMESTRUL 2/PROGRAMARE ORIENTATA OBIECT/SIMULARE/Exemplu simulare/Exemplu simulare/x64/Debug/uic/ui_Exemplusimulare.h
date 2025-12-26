/********************************************************************************
** Form generated from reading UI file 'Exemplusimulare.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXEMPLUSIMULARE_H
#define UI_EXEMPLUSIMULARE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExemplusimulareClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ExemplusimulareClass)
    {
        if (ExemplusimulareClass->objectName().isEmpty())
            ExemplusimulareClass->setObjectName("ExemplusimulareClass");
        ExemplusimulareClass->resize(600, 400);
        menuBar = new QMenuBar(ExemplusimulareClass);
        menuBar->setObjectName("menuBar");
        ExemplusimulareClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ExemplusimulareClass);
        mainToolBar->setObjectName("mainToolBar");
        ExemplusimulareClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ExemplusimulareClass);
        centralWidget->setObjectName("centralWidget");
        ExemplusimulareClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ExemplusimulareClass);
        statusBar->setObjectName("statusBar");
        ExemplusimulareClass->setStatusBar(statusBar);

        retranslateUi(ExemplusimulareClass);

        QMetaObject::connectSlotsByName(ExemplusimulareClass);
    } // setupUi

    void retranslateUi(QMainWindow *ExemplusimulareClass)
    {
        ExemplusimulareClass->setWindowTitle(QCoreApplication::translate("ExemplusimulareClass", "Exemplusimulare", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExemplusimulareClass: public Ui_ExemplusimulareClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXEMPLUSIMULARE_H
