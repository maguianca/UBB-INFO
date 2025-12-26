#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Elevi.h"

class Elevi : public QMainWindow
{
    Q_OBJECT

public:
    Elevi(QWidget *parent = nullptr);
    ~Elevi();

private:
    Ui::EleviClass ui;
};
