#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EX2_XsiO.h"

class EX2_XsiO : public QMainWindow
{
    Q_OBJECT

public:
    EX2_XsiO(QWidget *parent = nullptr);
    ~EX2_XsiO();

private:
    Ui::EX2_XsiOClass ui;
};
