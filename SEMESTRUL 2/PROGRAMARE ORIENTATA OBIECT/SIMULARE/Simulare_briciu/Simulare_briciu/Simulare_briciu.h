#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Simulare_briciu.h"

class Simulare_briciu : public QMainWindow
{
    Q_OBJECT

public:
    Simulare_briciu(QWidget *parent = nullptr);
    ~Simulare_briciu();

private:
    Ui::Simulare_briciuClass ui;
};
