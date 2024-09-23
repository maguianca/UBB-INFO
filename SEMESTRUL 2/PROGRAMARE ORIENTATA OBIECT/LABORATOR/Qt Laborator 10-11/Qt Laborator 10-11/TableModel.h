#pragma once
#pragma once
#pragma once
#include <QAbstractTableModel>
#include "domeniu.h"
#include <vector>
#include <qdebug.h>
using namespace std;

class TableModel : public QAbstractTableModel {
	std::vector<Turism> oferte;
public:
	TableModel(const std::vector<Turism>& oferte) : oferte{ oferte } {
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return oferte.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		//qDebug() << "row:" << index.row() << " col:" << index.column() << " role" << role;
		if (role == Qt::FontRole) {
			QFont f;
			f.setItalic(index.row());
			f.setBold(index.row());
			return f;
		}
		if (role == Qt::ForegroundRole)
		{
			Turism t = oferte[index.row()];
			if (t.get_pret() > 0)
				return QBrush(Qt::darkGreen);
		}
		if (role == Qt::DisplayRole) {
			Turism p = oferte[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(p.get_denumire());
			}
			else if (index.column() == 1) {
				return QString::fromStdString(p.get_destinatie());
			}
			else if (index.column() == 2) {
				return QString::fromStdString(p.get_tip());
			}
			else if (index.column() == 3) {
				return QString::number(p.get_pret());
			}
		}

		return QVariant{};
	}

	void setOferte(const vector<Turism>& oferte) {
		this->oferte = oferte;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount()-1, columnCount()-1);
		emit dataChanged(topLeft, bottomR);
	}
	Qt::ItemFlags flags(const QModelIndex& /*index*/) const {
		return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
	}
};