#pragma once
#include<QWidget>
#include<QAbstractTableModel>
#include"service.h"
class TableModel :public QAbstractTableModel {
private:
	Service& service;
	int value;
public:
	TableModel(Service& service) :service{ service } {
		value = 0;
	}
	int rowCount(const QModelIndex& parent = QModelIndex()) const {
		return service.sortare().size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const {
		return 5;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const {
		if (role == Qt::DisplayRole) {
			Produs p = service.sortare()[index.row()];
			if (index.column() == 0)
				return QString::number(p.get_id());
			if (index.column() == 1)
				return QString::fromStdString(p.get_nume());
			if (index.column() == 2)
				return QString::fromStdString(p.get_tip());
			if (index.column() == 3)
				return QString::number(p.get_pret());
			if (index.column() == 4)
				return QString::number(service.nr_voc(p.get_nume()));
		}
		if (role == Qt::BackgroundRole) {
			Produs p = service.sortare()[index.row()];
			if (p.get_pret() <= value)
				return QBrush{ Qt::red };
		}
		return QVariant{};
	}
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const {
		if (role == Qt::DisplayRole) {
			if (orientation == Qt::Horizontal) {
				if (section == 0)
					return QString::fromStdString("id");
				if (section == 1)
					return QString::fromStdString("nume");
				if (section == 2)
					return QString::fromStdString("tip");
				if (section == 3)
					return QString::fromStdString("pret");
				if (section == 4)
					return QString::fromStdString("nr_voc");
			}
		}
		return QVariant{};
	}
	void set(Service& service) {
		auto f = createIndex(0, 0);
		auto b = createIndex(rowCount(), columnCount());
		emit dataChanged(f, b);
		emit layoutChanged();
	}
	void setVal(int val) {
		value = val;
	}
};