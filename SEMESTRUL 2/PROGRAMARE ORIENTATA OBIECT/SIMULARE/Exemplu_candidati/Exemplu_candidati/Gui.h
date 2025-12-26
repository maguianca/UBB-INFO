#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <vector>
#include <string>
#include "Service.h"

class GUI : public QWidget {
    Q_OBJECT
private:
    Service& service;
    void init();
    void conec();
    void reloadPlaciList(const std::vector<Candidat>& lst);

    QListWidget* procesoareList = new QListWidget;
    QListWidget* placiList = new QListWidget;
    QHBoxLayout* mainL = new QHBoxLayout;

    QWidget* formDreapta = new QWidget;
    QVBoxLayout* formDreaptaL = new QVBoxLayout;

    QLineEdit* namePlaca = new QLineEdit;
    QLineEdit* socluPlaca = new QLineEdit;
    QLineEdit* pretPlaca = new QLineEdit;

    QPushButton* addBtn = new QPushButton{ "adaugã" };

    QLabel* pret = new QLabel("");

public:
    GUI(Service& service) : service{ service } {
        init();
        conec();
        reloadPlaciList(service.getPlaciDeBaza());
    }
};
