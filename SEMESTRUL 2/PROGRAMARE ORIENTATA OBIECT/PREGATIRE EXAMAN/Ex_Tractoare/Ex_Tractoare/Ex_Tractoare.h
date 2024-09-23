#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Ex_Tractoare.h"

class Ex_Tractoare : public QMainWindow
{
    Q_OBJECT

public:
    Ex_Tractoare(QWidget *parent = nullptr);
    ~Ex_Tractoare();

private:
    Ui::Ex_TractoareClass ui;
};
