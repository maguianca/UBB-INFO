#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Aplicatie_produse.h"

class Aplicatie_produse : public QMainWindow
{
    Q_OBJECT

public:
    Aplicatie_produse(QWidget *parent = nullptr);
    ~Aplicatie_produse();

private:
    Ui::Aplicatie_produseClass ui;
};
