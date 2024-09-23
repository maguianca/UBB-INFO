#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Ex_melodii1.h"

class Ex_melodii1 : public QMainWindow
{
    Q_OBJECT

public:
    Ex_melodii1(QWidget *parent = nullptr);
    ~Ex_melodii1();

private:
    Ui::Ex_melodii1Class ui;
};
