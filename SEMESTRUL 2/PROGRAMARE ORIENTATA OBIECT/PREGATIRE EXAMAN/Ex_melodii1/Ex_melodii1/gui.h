#pragma once
#include<QWidget>
#include<QTableView>
#include"service.h"
#include<qhboxlayout>
#include<qpushbutton>
#include<qlineedit.h>
#include"model.h"
#include<qlabel>
#include<qmessagebox.h>
#include<qformlayout.h>
#include<QPainter>
class Painter :public QWidget {
private:
	Service& service;
public:
	explicit Painter(Service& service) :service{ service } {
		this->repaint();
	}
	void paintEvent(QPaintEvent* ev)override;
};
class GUI :public QWidget {
private:
	Painter* painter;
	QVBoxLayout* lpaint = new QVBoxLayout;
	Service& service;
	QTableView* table = new QTableView;
	TableModel* model;
	QPushButton* btn_modifica = new QPushButton{ "modifica" };
	QPushButton* btn_sterge = new QPushButton{ "sterge" };
	QPushButton* btn_undo = new QPushButton{ "undo" };
	QLineEdit* edit_titlu = new QLineEdit;
	QSlider* slider = new QSlider{ Qt::Horizontal };
	QLabel* lbl = new QLabel;
	void init_gui();
	//initializeaza gui
	void load_data();
	//incarca datele semnaleaza tableview
	void conect();
	//conecteaza componentele intre ele prin sloturi
	void paintEvent(QPaintEvent* ev)override;
public:
	GUI(Service& service) :service{ service } {
		model = new TableModel{ service };
		table->setModel(model);
		init_gui();
		load_data();
		conect();
		this->repaint();
	}
};