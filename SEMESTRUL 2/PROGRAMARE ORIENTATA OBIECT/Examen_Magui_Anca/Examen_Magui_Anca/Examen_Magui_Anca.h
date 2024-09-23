#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Examen_Magui_Anca.h"

class Examen_Magui_Anca : public QMainWindow
{
    Q_OBJECT

public:
    Examen_Magui_Anca(QWidget *parent = nullptr);
    ~Examen_Magui_Anca();

private:
    Ui::Examen_Magui_AncaClass ui;
};
