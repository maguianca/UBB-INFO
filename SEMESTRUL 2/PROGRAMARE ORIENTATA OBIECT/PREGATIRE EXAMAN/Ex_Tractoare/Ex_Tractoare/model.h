#pragma once
#include<qabstractitemmodel.h>
#include<qwidget>
#include"service.h"
class TableModel :public QAbstractTableModel {
private:
	Service& service;
	string denumire;
public:
	TableModel(Service& service) :service{ service } {
		denumire = "";
	}
	//constrctor primeste referinta la service
	int rowCount(const QModelIndex& parent = QModelIndex()) const {
		return service.sorteaza().size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const {
		return 5;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const {
		if (role == Qt::DisplayRole) {
			Tractor t = service.sorteaza()[index.row()];
			if (index.column() == 0) {
				return QString::number(t.get_id());
			}
			if (index.column() == 1) {
				return QString::fromStdString(t.get_denumire());
			}
			if (index.column() == 2) {
				return QString::fromStdString(t.get_tip());
			}
			if (index.column() == 3) {
				return QString::number(t.get_numar());
			}
			if (index.column() == 4) {
				return QString::number(service.numar(t.get_tip()));
			}

		}
		if (role == Qt::BackgroundRole) {
			Tractor t = service.sorteaza()[index.row()];
			if (t.get_tip() == denumire) {
				return QBrush{Qt::red};
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
	void setN(string nume) {
		denumire = nume;
	}
};