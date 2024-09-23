#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Produse2.h"

class Produse2 : public QMainWindow
{
    Q_OBJECT

public:
    Produse2(QWidget *parent = nullptr);
    ~Produse2();

private:
    Ui::Produse2Class ui;
};
