/********************************************************************************
** Form generated from reading UI file 'QtLaborator1011.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTLABORATOR1011_H
#define UI_QTLABORATOR1011_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtLaborator1011Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtLaborator1011Class)
    {
        if (QtLaborator1011Class->objectName().isEmpty())
            QtLaborator1011Class->setObjectName("QtLaborator1011Class");
        QtLaborator1011Class->resize(600, 400);
        menuBar = new QMenuBar(QtLaborator1011Class);
        menuBar->setObjectName("menuBar");
        QtLaborator1011Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtLaborator1011Class);
        mainToolBar->setObjectName("mainToolBar");
        QtLaborator1011Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(QtLaborator1011Class);
        centralWidget->setObjectName("centralWidget");
        QtLaborator1011Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtLaborator1011Class);
        statusBar->setObjectName("statusBar");
        QtLaborator1011Class->setStatusBar(statusBar);

        retranslateUi(QtLaborator1011Class);

        QMetaObject::connectSlotsByName(QtLaborator1011Class);
    } // setupUi

    void retranslateUi(QMainWindow *QtLaborator1011Class)
    {
        QtLaborator1011Class->setWindowTitle(QCoreApplication::translate("QtLaborator1011Class", "QtLaborator1011", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtLaborator1011Class: public Ui_QtLaborator1011Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTLABORATOR1011_H
