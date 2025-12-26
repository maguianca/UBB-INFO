#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Exemplusimulare.h"

class Exemplusimulare : public QMainWindow
{
    Q_OBJECT

public:
    Exemplusimulare(QWidget *parent = nullptr);
    ~Exemplusimulare();

private:
    Ui::ExemplusimulareClass ui;
};
