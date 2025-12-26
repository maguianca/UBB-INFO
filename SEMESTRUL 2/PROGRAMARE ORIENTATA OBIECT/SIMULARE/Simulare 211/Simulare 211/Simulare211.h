#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Simulare211.h"

class Simulare211 : public QMainWindow
{
    Q_OBJECT

public:
    Simulare211(QWidget *parent = nullptr);
    ~Simulare211();

private:
    Ui::Simulare211Class ui;
};
