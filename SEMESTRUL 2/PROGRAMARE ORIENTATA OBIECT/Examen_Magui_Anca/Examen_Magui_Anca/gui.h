#pragma once
#include"service.h"
#include<QWidget>
#include<QTableview>
#include<QTableWidget>
#include<qpushbutton>
#include<qhboxlayout>
#include<qlineedit>
#include<qformlayout>
#include"model.h"
#include<QMessageBox>
#include<qradiobutton.h>
#include<QEvent>
#include<Qpainter>
//clasa de desen
class Painter :public QWidget {
private:
	Service& service;
public:
	explicit Painter(Service& service) :service{ service } {
		this->repaint();
	}
	//functie care deseneaza 
	void paintEvent(QPaintEvent* ev)override;
};
class GUI :public QWidget {
private:
	Service& service;
	Painter* p;
	QHBoxLayout* lay = new QHBoxLayout;
	QTableWidget* tabel;
	QTableView* table=new QTableView;
	TableModel* model;
	QPushButton* btn_sterge = new QPushButton{ "Delete" };
	QPushButton* btn_modifica = new QPushButton{ "Update" };
	QLineEdit* edit_denumire = new QLineEdit;
	QLineEdit* edit_tip = new QLineEdit;
	QRadioButton* c1 = new QRadioButton{ "cilindru 1" };
	QRadioButton* c2 = new QRadioButton{ "cilindru 2" };
	QRadioButton* c3 = new QRadioButton{ "cilindru 4" };
	QRadioButton* c4 = new QRadioButton{ "cilindru 8" };
	void load_data(vector<Utilaj>ut);
	//incarca tabelul cu date si apeleaza model table
	void init_gui();
	//initializeaza gui
	void conectare();
	//conecteaza componentele intre ele
	void paintEvent(QPaintEvent* ev)override;
	//metoda de desenare
public:
	GUI(Service& service) :service{ service } {
		model = new TableModel{ service };
		table->setModel(model);
		init_gui();
		conectare();
		load_data(service.sortare());
		this->repaint();
	}
	//constructor gui aepeleaza cele 3 metode private si initializeaza modelul
};