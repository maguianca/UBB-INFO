#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_history.h"

class history : public QMainWindow
{
    Q_OBJECT

public:
    history(QWidget *parent = nullptr);
    ~history();

private:
    Ui::historyClass ui;
};
