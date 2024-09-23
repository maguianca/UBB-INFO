#pragma once
#include<QWidget>
#include"service.h"
#include<QAbstractTableModel>
class TableModel :public QAbstractTableModel {
private:
	Service& service;
public:TableModel(Service& service) :service{ service } {}
	  int rowCount(const QModelIndex& parent = QModelIndex()) const {
		  return service.get_all().size();
	  }
	  int columnCount(const QModelIndex& parent = QModelIndex()) const {
		  return 6;
	  }
	  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const {
		  if (role==Qt::DisplayRole){
			  Melodie m = service.get_all()[index.row()];
			  if (index.column() == 0) {
				  return QString::number(m.get_id());
			  }
			  if (index.column() == 1) {
				  return QString::fromStdString(m.get_titlu());
			  }
			  if (index.column() == 2) {
				  return QString::fromStdString(m.get_artist());
			  }
			  if (index.column() == 3) {
				  return QString::fromStdString(m.get_gen());
			  }
			  if (index.column() == 4) {
				  return QString::number(service.artist(m.get_artist()));
			  }
			  if (index.column() == 5) {
				  return QString::number(service.gen(m.get_gen()));
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

};