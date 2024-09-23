#pragma once
#include"service.h"
#include<QWidget>
#include<QAbstractListModel>
class Lista :public QAbstractListModel {
private:
	Service& service;
public:
	Lista(Service& service) :service{ service } {}
	int rowCount(const QModelIndex& parent = QModelIndex()) const {
		return service.get_all().size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const {
		return 5;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			Melodie m = service.get_all()[index.row()];
			return QString::number(m.get_id()) +QString::fromStdString(" ")+ QString::fromStdString(m.get_titlu()) +QString::fromStdString(" ")+ QString::fromStdString(m.get_artist()) +QString::fromStdString(" ")+ QString::number(m.get_rank());
		}
		return QVariant{};
	}
	void set(Service& service)
	{
		auto top = createIndex(0, 0);
		auto button = createIndex(rowCount(), 0);
		emit layoutChanged();
		emit dataChanged(top, button);
	}
};