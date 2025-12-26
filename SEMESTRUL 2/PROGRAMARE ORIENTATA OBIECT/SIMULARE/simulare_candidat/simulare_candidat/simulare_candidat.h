#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_simulare_candidat.h"

class simulare_candidat : public QMainWindow
{
    Q_OBJECT

public:
    simulare_candidat(QWidget *parent = nullptr);
    ~simulare_candidat();

private:
    Ui::simulare_candidatClass ui;
};
