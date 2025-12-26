#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Angajat.h"

class Angajat : public QMainWindow
{
    Q_OBJECT

public:
    Angajat(QWidget *parent = nullptr);
    ~Angajat();

private:
    Ui::AngajatClass ui;
};
