#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Exemplu_candidati.h"

class Exemplu_candidati : public QMainWindow
{
    Q_OBJECT

public:
    Exemplu_candidati(QWidget *parent = nullptr);
    ~Exemplu_candidati();

private:
    Ui::Exemplu_candidatiClass ui;
};
