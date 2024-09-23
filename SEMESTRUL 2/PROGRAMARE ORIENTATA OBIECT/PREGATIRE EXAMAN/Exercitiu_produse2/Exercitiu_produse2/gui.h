#pragma once
#include"service.h"
#include"model.h"
#include"fereastra.h";
#include<QWidget>
#include<QPushbutton>
#include<qlineedit.h>
#include<qtableview>
#include<qlabel>
#include<qhboxlayout>
#include<qformlayout.h>
#include<qmessagebox.h>
#include<Qslider>
#include<Qlabel>
class GUI :public QWidget{
private:
	Service& service;
	TableModel* model;
	QTableView* tabel = new QTableView;
	QPushButton* btn_adauga = new QPushButton{ "Adauga" };
	QLineEdit* edit_id = new QLineEdit;
	QLineEdit* edit_nume = new QLineEdit;
	QLineEdit* edit_tip = new QLineEdit;
	QLineEdit* edit_pret = new QLineEdit;
	QSlider* slider = new QSlider{ Qt::Horizontal };
	QLabel* lbl = new QLabel;
	vector<Fereastra*>f;
	void init_gui();
	void load_data();
	void connect();

public:
	GUI(Service& service) :service{ service } {
	model = new TableModel{ service };
	tabel->setModel(model);
	init_gui();
	load_data();
	connect();
}
};