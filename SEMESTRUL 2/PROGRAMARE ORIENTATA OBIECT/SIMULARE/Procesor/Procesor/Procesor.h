#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Procesor.h"

class Procesor : public QMainWindow
{
    Q_OBJECT

public:
    Procesor(QWidget *parent = nullptr);
    ~Procesor();

private:
    Ui::ProcesorClass ui;
};
