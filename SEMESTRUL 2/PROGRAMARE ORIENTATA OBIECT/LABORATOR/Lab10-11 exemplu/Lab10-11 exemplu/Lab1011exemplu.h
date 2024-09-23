#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lab1011exemplu.h"

class Lab1011exemplu : public QMainWindow
{
    Q_OBJECT

public:
    Lab1011exemplu(QWidget *parent = nullptr);
    ~Lab1011exemplu();

private:
    Ui::Lab1011exempluClass ui;
};
