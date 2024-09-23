#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtLaborator1011.h"

class QtLaborator1011 : public QMainWindow
{
    Q_OBJECT

public:
    QtLaborator1011(QWidget *parent = nullptr);
    ~QtLaborator1011();

private:
    Ui::QtLaborator1011Class ui;
};
