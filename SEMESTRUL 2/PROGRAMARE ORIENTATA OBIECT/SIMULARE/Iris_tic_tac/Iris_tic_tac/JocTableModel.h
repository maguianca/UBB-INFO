#pragma once
//
// Created by Iris on 6/21/2024.
//

#ifndef TICTAC_JOCTABLEMODEL_H
#define TICTAC_JOCTABLEMODEL_H
#include <QAbstractTableModel>
#include "Joc.h"
#include <vector>
using std::vector;
class JocTableModel : public QAbstractTableModel {
private:
    vector<Joc> jocuri;
public:
    JocTableModel(vector<Joc> all) : QAbstractTableModel(), jocuri{ all } {}
    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return jocuri.size();
    }
    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 5;
    }
    QVariant data(const QModelIndex& index, int role) const override {
        if (role == Qt::DisplayRole)
        {
            const Joc& j = jocuri[index.row()];

            switch (index.column()) {
            case 0:
                return j.getId();
            case 1:
                return j.getDim();
            case 2:
                return QString::fromStdString(j.getTabla());
            case 3:
                return QString::fromStdString(j.getJucator());
            case 4:
                return QString::fromStdString(j.getStare());
            default:
                break;
            }
        }
        return QVariant();
    }

};


#endif //TICTAC_JOCTABLEMODEL_H
