#pragma once
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTableView>
#include "TableModel.h"
#include "Board.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

class GUI: public QWidget{
private:
    Board board;
    QHBoxLayout *main;
    QVBoxLayout *right_side;
    QLabel *movess;
    QLabel *status;
    QLabel *reguli;
    QLabel *mesaj;
    QPushButton *attack;
    QPushButton *new_game;
    QLineEdit *config;
    QTableView *table_view; //la table view ii asociez un model
    //widget face o copie la date
    BattleshipTableModel *table_model;
    void init_gui();
    void reload_table();
    void connect();

public:
    GUI(Board &board):board{board}{
        init_gui();
        connect();
    };


};
