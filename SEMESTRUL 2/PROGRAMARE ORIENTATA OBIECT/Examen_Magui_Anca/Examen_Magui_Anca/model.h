#pragma once
#include<QWidget>
#include<QAbstractItemModel>
#include<QAbstractTableModel>
#include"service.h"
//QTableModel
class TableModel :public QAbstractTableModel{
private:
	Service& service;
public:
	TableModel(Service& service) :service{ service } {}
	//returneaza nr linii
	int rowCount(const QModelIndex& parent = QModelIndex()) const {
		return service.get_all().size();
	}
	//returneaza nr coloane
	int columnCount(const QModelIndex& parent = QModelIndex()) const {
		return 5;
	}
	//seteaza datele in coloane
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const {
		if (role == Qt::DisplayRole) {
			Utilaj u = service.get_all()[index.row()];
			if (index.column() == 0) {
				return QString::number(u.get_id());
			}
			if (index.column() == 1) {
				return QString::fromStdString(u.get_denumire());
			}
			if (index.column() == 2) {
				return QString::fromStdString(u.get_tip());
			}
			if (index.column() == 3) {
				return QString::number(u.get_cilindri());
			}
			if (index.column() == 4) {
				return QString::number(service.tip(u.get_tip()));
			}
		}
		return QVariant{};
	}
	//seteaza modelul si emite semnale
	void set(Service& service) {
		auto f = createIndex(0, 0);
		auto b = createIndex(rowCount(), columnCount());
		emit dataChanged(f, b);
		emit layoutChanged();
	}
};