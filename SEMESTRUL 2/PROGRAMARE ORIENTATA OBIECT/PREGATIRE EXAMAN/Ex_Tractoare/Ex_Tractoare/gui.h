#pragma once
#include"service.h"
#include<qwidget>
#include<qpushbutton>
#include<qtableview.h>
#include<qlineedit>
#include<qformlayout>
#include<qhboxlayout>
#include"model.h"
#include<qmessagebox>
#include<qcombobox.h>
#include<Qpainter>
#include<qevent.h>
class Painter:public QWidget {
private:
	Service& service;
public:
	explicit Painter(Service& service) :service{ service } {
	this->repaint();
}
	void paintEvent(QPaintEvent* ev)const;

};
class GUI :public QWidget {
private:
	Painter* painter;
	QHBoxLayout* lpaint = new QHBoxLayout;
	Service& service;
	QTableView* table = new QTableView;
	TableModel* model;
	QPushButton* btn_adauga = new QPushButton{ "Adauga" };
	QLineEdit* edit_id = new QLineEdit;
	QLineEdit* edit_denumire = new QLineEdit;
	QLineEdit* edit_tip = new QLineEdit;
	QLineEdit* edit_numar = new QLineEdit;
	QComboBox* combo = new QComboBox;
	int nr;
	QPoint centru;
	void init_gui();
	//initializeaza gui
	void conect();
	//conecteaza gui
	void load_data();
	//semnaleaza schimbare de date la model table
	void paintEvent(QPaintEvent* ev)override;
	void mousePressEvent(QMouseEvent* event)override;

public:
	GUI(Service& service) :service{ service } {
		model = new TableModel{ service };
		table->setModel(model);
		init_gui();
		load_data();
		conect();
		repaint();
	}
};