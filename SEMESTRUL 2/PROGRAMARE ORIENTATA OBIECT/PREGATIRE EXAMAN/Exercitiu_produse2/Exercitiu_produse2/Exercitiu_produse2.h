#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Exercitiu_produse2.h"

class Exercitiu_produse2 : public QMainWindow
{
    Q_OBJECT

public:
    Exercitiu_produse2(QWidget *parent = nullptr);
    ~Exercitiu_produse2();

private:
    Ui::Exercitiu_produse2Class ui;
};
