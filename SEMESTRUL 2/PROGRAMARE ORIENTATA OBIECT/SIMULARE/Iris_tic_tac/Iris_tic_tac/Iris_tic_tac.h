#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Iris_tic_tac.h"

class Iris_tic_tac : public QMainWindow
{
    Q_OBJECT

public:
    Iris_tic_tac(QWidget *parent = nullptr);
    ~Iris_tic_tac();

private:
    Ui::Iris_tic_tacClass ui;
};
