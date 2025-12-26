#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ExempluSimulareAbonament.h"

class ExempluSimulareAbonament : public QMainWindow
{
    Q_OBJECT

public:
    ExempluSimulareAbonament(QWidget *parent = nullptr);
    ~ExempluSimulareAbonament();

private:
    Ui::ExempluSimulareAbonamentClass ui;
};
