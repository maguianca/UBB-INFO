#pragma once
#include"service.h"
#include<QWidget>
#include<qabstractitemmodel.h>
class ModelTable :public QAbstractTableModel {
private:
	Service& service;
	int value;
public:
	ModelTable(Service& service) :service{ service } {};
	//constructor service
	int rowCount(const QModelIndex& parent = QModelIndex()) const override{
		return service.get_all().size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override{
		return 5;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override
	{
		if (role == Qt::DisplayRole)
		{
			Produs p = service.sorteaza()[index.row()];
			if (index.column() == 0)
				return QString::number(p.get_id());
			if (index.column() == 1)
				return QString::fromStdString(p.get_nume());
			if (index.column() == 2)
				return QString::fromStdString(p.get_tip());
			if (index.column() == 3)
				return QString::number(p.get_pret());
			if (index.column() == 4)
				return QString::number(service.voc(p.get_nume()));
				
		}
		if (role == Qt::BackgroundRole)
		{
			Produs p = service.get_all()[index.row()];
			if (p.get_pret() <= value)
				return QBrush(Qt::red);

		}
		return QVariant{};
	}
	void set(Service& service) {
		auto f = createIndex(0, 0);
		auto b = createIndex(rowCount(), columnCount());
		emit dataChanged(f, b);
		emit layoutChanged();
	}
	void setValue(int val) {
		value = val;
		set(service);
	}

};