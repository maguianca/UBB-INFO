#pragma once
#include<QAbstractTableModel>
#include<QWidget>
#include<vector>
#include"service.h"
class TableModel :public QAbstractTableModel{
private:
	Service& service;
	vector < Joc >date;
public:
	TableModel(Service& service) :service{ service } {
		date = service.sorteaza();
	};
	int rowCount(const QModelIndex& parent = QModelIndex()) const {
		return service.get_all().size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const {
		return 5;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const {
		if (role == Qt::DisplayRole) {
			Joc j = service.sorteaza()[index.row()];
			if (index.column() == 0)
			{
				return QString::number(j.get_id());
			}
			if (index.column() == 1)
			{
				return QString::number(j.get_dim());
			}
			if (index.column() == 2)
			{
				qDebug() <<index.row()<< j.get_joc();
				return QString::fromStdString(j.get_joc());
			}
			if (index.column() == 3)
			{
				return QString::fromStdString(j.get_jucator());
			}
			if (index.column() == 4)
			{
				return QString::fromStdString(j.get_stare());
			}
		}
		return QVariant{};
	}
	void set(Service& servicee) {
		date = service.sorteaza();
		auto top = createIndex(0, 0);
		auto buttom = createIndex(rowCount(), columnCount());
		emit dataChanged(top, buttom);
		emit layoutChanged();
	}
}; 
