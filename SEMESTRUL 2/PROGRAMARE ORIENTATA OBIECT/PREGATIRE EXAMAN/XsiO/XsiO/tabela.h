#pragma once
#pragma once
#include<QAbstractTableModel>
#include<QWidget>
#include"service.h"
#include"observer.h"
class Tabela :public QAbstractTableModel{
private:
	Service& service;
	string text;
	int dim;
	string jucator;
	int id;
public:
	Tabela(Service& service, const string& text, const int& dim) :service{ service }, text{ text }, dim{ dim } {

	};
	int rowCount(const QModelIndex& parent = QModelIndex()) const {
		return dim;
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const {
		return dim;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const {
		if (role == Qt::DisplayRole) {
			int x = index.row() * dim + index.column();
			if (x >= 0 && x < text.size()) {
				return QString(text[x]);
			}
			else {
				return QString{};
			}
		}
		return QVariant{};
	}
	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override {
		if (role == Qt::EditRole) {
			int x = index.row() * dim + index.column();
			if (x >= 0 && x < text.size()&& text[x]=='-') {
				text[x] = jucator[0]; 
				service.mod(id,text,jucator);
				if (jucator == "O")jucator = "X";
				else jucator = "O";
				emit dataChanged(index, index, { Qt::DisplayRole });
				return true;
			}
		}
		return false;
	}
	Qt::ItemFlags flags(const QModelIndex& index) const override {
        return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
    }
	void set(const string& textul,const int& dimen,const string&juc,int iii) {
		auto top = createIndex(0, 0);
		auto buttom = createIndex(rowCount(), columnCount());
		emit dataChanged(top, buttom);
		emit layoutChanged();
		text = textul;
		dim = dimen;
		jucator = juc;
		id = iii;
	}
};
