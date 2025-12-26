#pragma once
#include <QAbstractTableModel>
#include "Board.h"
#include <qbrush.h>

class BattleshipTableModel: public QAbstractTableModel{
    Board &board;
public:

    int rowCount(const QModelIndex&parent = QModelIndex())const override{
        return board.get_size();
    };

    int columnCount(const QModelIndex&parent = QModelIndex()) const override{
        return board.get_size();
    };

    QVariant data(const QModelIndex& index, int role=Qt::DisplayRole) const override{
        int row=index.row();
        int col=index.column();
        //verificare valid nue nevoie ca se selecteaza din tabel
        int value=board.get_coordinates(row,col);
        //qDebug()<<row<<" "<<col<<" "<<role<<"\n";
        if(role==Qt::DisplayRole) //
        {
            if(value==0||value==1)
                return "*";
            else if(value==2)
                return "o";
            else if(value==3)
                return "x";
         return QString::number(value);
        }
        else if(role==Qt::BackgroundRole){
            if(value==0||value==1)
                return QBrush{Qt::lightGray};
            else if(value==2)
                return QBrush(Qt::blue);
            else if(value==3)
                return QBrush(Qt::red);

        }
        return {}; // fara asta am segmentation fault

    };

    BattleshipTableModel(Board &board):board{board}{};
    void update(){
        emit layoutChanged();
    }

};
