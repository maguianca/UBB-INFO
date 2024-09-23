#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Tudor_Xsi0.h"

class Tudor_Xsi0 : public QMainWindow
{
    Q_OBJECT

public:
    Tudor_Xsi0(QWidget *parent = nullptr);
    ~Tudor_Xsi0();

private:
    Ui::Tudor_Xsi0Class ui;
};
