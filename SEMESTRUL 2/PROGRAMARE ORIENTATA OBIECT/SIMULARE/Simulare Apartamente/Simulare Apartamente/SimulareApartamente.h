#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SimulareApartamente.h"

class SimulareApartamente : public QMainWindow
{
    Q_OBJECT

public:
    SimulareApartamente(QWidget *parent = nullptr);
    ~SimulareApartamente();

private:
    Ui::SimulareApartamenteClass ui;
};
