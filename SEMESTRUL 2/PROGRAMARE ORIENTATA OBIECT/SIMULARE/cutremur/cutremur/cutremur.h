#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_cutremur.h"

class cutremur : public QMainWindow
{
    Q_OBJECT

public:
    cutremur(QWidget *parent = nullptr);
    ~cutremur();

private:
    Ui::cutremurClass ui;
};
