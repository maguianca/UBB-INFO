#pragma once
#include<qWidget>
#include<Qlineedit>
#include<qpushbutton>
#include<qtableview.h>
#include<qtablewidget>
#include"service.h"
#include<Qhboxlayout>
#include<qvboxlayout>
#include"model.h"
#include<qpainter.h>
#include<qformlayout.h>
class Painter :public QWidget {
private:
	Service& service;
public:
	explicit Painter(Service& service) :service{ service } {
		this->repaint();
	}
	void paintEvent(QPaintEvent* ex)override;
};
class GUI:public QWidget {
private:
	Service& service;
	QTableView* tbl = new QTableView;
	TableModel* tabela;
	QTableWidget* tabel;
	QLineEdit* edit_titlu = new QLineEdit;
	QLineEdit* edit_artist = new QLineEdit;
	QLineEdit* edit_gen = new QLineEdit;
	QPushButton* btn_adauga = new QPushButton{ "Adauga" };
	QPushButton* btn_sterge = new QPushButton{ "Sterge" };
	Painter* painter;
	QHBoxLayout* l_painter = new QHBoxLayout;
	void load_data(vector<Melodie>m);
	//uploadeaza tabelul cu melodii
	void init_gui();
	//initializeaza gui 
	void connectare();
	//copnectreaza compunentele sib sloturile intre ele 
	void load_tabela();
	//semnaleaza schombare la tabela
	void paintEvent(QPaintEvent* ex)override;
public:
	GUI(Service& service) :service{ service } {
		tabela = new TableModel{ service };
		tbl->setModel(tabela);
		init_gui();
		connectare();
		load_data(service.sorteaza());
		load_tabela();
		this->repaint();
	}
};