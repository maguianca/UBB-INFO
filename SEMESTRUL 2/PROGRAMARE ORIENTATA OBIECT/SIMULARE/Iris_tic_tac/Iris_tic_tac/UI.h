#pragma once
//
// Created by Iris on 6/21/2024.
//

#ifndef TICTAC_UI_H
#define TICTAC_UI_H
#include "Service.h"
#include <qwidget.h>
#include <qboxlayout.h>
#include <qpushbutton.h>
#include <qtableview.h>
#include <qformlayout.h>
#include <qlineedit.h>
#include "JocTableModel.h"
//#include <bits/stdc++.h>

class TablaWindow : public QWidget {
private:
    string tabla;
    string jucator;
    int id;
    Service& srv;
    void generateGUI();
private slots:
    void tableButtons();
public:
    TablaWindow(string& s, string jucator, int id, Service& se) : srv{ se } {
        tabla = s;
        this->jucator = jucator;
        this->id = id;
        generateGUI();
    }
    std::pair<int, int> emptyAndCompletedCells();
};



class UI : public QWidget {
private:
    Service& srv;
    QTableView* listaJocuri = new QTableView;
    QFormLayout* infoForm = new QFormLayout;
    QLineEdit* dimField = new QLineEdit;
    QLineEdit* tablaField = new QLineEdit;
    QLineEdit* jucatorField = new QLineEdit;
    QLineEdit* stareField = new QLineEdit;

    QFormLayout* modifyForm = new QFormLayout;
    QLineEdit* dimModifField = new QLineEdit;
    QLineEdit* tablaModifField = new QLineEdit;
    QLineEdit* jucatorModifField = new QLineEdit;
    QLineEdit* stareModifField = new QLineEdit;
    QPushButton* addBtn = new QPushButton{ "Add joc" };
    QPushButton* modifyBtb = new QPushButton{ "Modify joc" };
    QPushButton* deleteBtn = new QPushButton{ "Delete joc" };
    TablaWindow* tw;
    JocTableModel* jocModel;

    void initGUI();
    void loadData();
    void connectGUI();
    void connectAddBtn();
    void connectModifyBtn();
    void connectSelectCell();
    void connectDelete();

public:
    UI(Service& s) :srv{ s } {
        initGUI();
        loadData();
        connectGUI();
    }
};


#endif //TICTAC_UI_H
