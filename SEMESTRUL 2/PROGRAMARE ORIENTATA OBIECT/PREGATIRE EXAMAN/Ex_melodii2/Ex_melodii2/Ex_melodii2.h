#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Ex_melodii2.h"

class Ex_melodii2 : public QMainWindow
{
    Q_OBJECT

public:
    Ex_melodii2(QWidget *parent = nullptr);
    ~Ex_melodii2();

private:
    Ui::Ex_melodii2Class ui;
};
