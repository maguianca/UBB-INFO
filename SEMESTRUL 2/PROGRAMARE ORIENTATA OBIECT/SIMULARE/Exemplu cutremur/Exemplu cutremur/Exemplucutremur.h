#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Exemplucutremur.h"

class Exemplucutremur : public QMainWindow
{
    Q_OBJECT

public:
    Exemplucutremur(QWidget *parent = nullptr);
    ~Exemplucutremur();

private:
    Ui::ExemplucutremurClass ui;
};
