#pragma once
#include"service.h"
#include<QWidget>
#include<qtablewidget.h>
#include<QHBoxLayout>
#include"model.h"
#include<QVBoxLayout>
#include<QPushButton>
#include<qlineedit.h>
#include<QSlider>
#include<qlabel.h>
#include<qmessagebox.h>
#include<qitemselectionmodel.h>
#include<qpainter.h>
#include<qformlayout.h>
#include"tabela.h"
#include<Qlistview.h>
#include<string.h>
#include<sstream>
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
	Service& service;
	QListView* lista = new QListView;
	Lista* m_list;
	QTableWidget* table;
	QTableView* tbl=new QTableView;
	TableModel* model;
	QPushButton* btn_sterge = new QPushButton{ "Sterge" };
	QPushButton* btn_modifica = new QPushButton{ "Update" };
	QLineEdit* edit_titlu = new QLineEdit;
	QSlider* slider = new QSlider{ Qt::Horizontal };
	QLabel* lbl = new QLabel;
	QVBoxLayout* layout_p = new QVBoxLayout;
	void load_table(vector<Melodie>m);
	void conectare();
	void init_gui();
	void reload();
	Painter* painter;
	void paintEvent(QPaintEvent* ev)override;
public:
	GUI(Service& service) :service{ service } {
		m_list = new Lista{ service };
		lista->setModel(m_list);
		model = new TableModel{ service };
		tbl->setModel(model);
		init_gui();
		conectare();
		load_table(service.sorteaza_rank());
		reload();
		repaint();
	}

};