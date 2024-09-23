/********************************************************************************
** Form generated from reading UI file 'Examen_Magui_Anca.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXAMEN_MAGUI_ANCA_H
#define UI_EXAMEN_MAGUI_ANCA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Examen_Magui_AncaClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Examen_Magui_AncaClass)
    {
        if (Examen_Magui_AncaClass->objectName().isEmpty())
            Examen_Magui_AncaClass->setObjectName("Examen_Magui_AncaClass");
        Examen_Magui_AncaClass->resize(600, 400);
        menuBar = new QMenuBar(Examen_Magui_AncaClass);
        menuBar->setObjectName("menuBar");
        Examen_Magui_AncaClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Examen_Magui_AncaClass);
        mainToolBar->setObjectName("mainToolBar");
        Examen_Magui_AncaClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Examen_Magui_AncaClass);
        centralWidget->setObjectName("centralWidget");
        Examen_Magui_AncaClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Examen_Magui_AncaClass);
        statusBar->setObjectName("statusBar");
        Examen_Magui_AncaClass->setStatusBar(statusBar);

        retranslateUi(Examen_Magui_AncaClass);

        QMetaObject::connectSlotsByName(Examen_Magui_AncaClass);
    } // setupUi

    void retranslateUi(QMainWindow *Examen_Magui_AncaClass)
    {
        Examen_Magui_AncaClass->setWindowTitle(QCoreApplication::translate("Examen_Magui_AncaClass", "Examen_Magui_Anca", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Examen_Magui_AncaClass: public Ui_Examen_Magui_AncaClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXAMEN_MAGUI_ANCA_H
