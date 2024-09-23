#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Melodii1.h"

class Melodii1 : public QMainWindow
{
    Q_OBJECT

public:
    Melodii1(QWidget *parent = nullptr);
    ~Melodii1();

private:
    Ui::Melodii1Class ui;
};
