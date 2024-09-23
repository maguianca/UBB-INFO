#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Exemplulab1314.h"

class Exemplulab1314 : public QMainWindow
{
    Q_OBJECT

public:
    Exemplulab1314(QWidget *parent = nullptr);
    ~Exemplulab1314();

private:
    Ui::Exemplulab1314Class ui;
};
