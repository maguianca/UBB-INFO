#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Simulare_jucator.h"

class Simulare_jucator : public QMainWindow
{
    Q_OBJECT

public:
    Simulare_jucator(QWidget *parent = nullptr);
    ~Simulare_jucator();

private:
    Ui::Simulare_jucatorClass ui;
};
