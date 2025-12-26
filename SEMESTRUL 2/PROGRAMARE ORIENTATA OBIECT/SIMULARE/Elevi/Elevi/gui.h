#pragma once
#include<QApplication>
#include"service.h"
#include<QWidget>
#include<qpushbutton.h>
#include<QListWidget>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QLabel>
#include<QLineEdit>
#include<QMessageBox>
class GUI :public QWidget {
private:
	Service& service;
	QListWidget* lista=new QListWidget;
	QPushButton* btn_sortare_clasa = new QPushButton{ "Sortare dupa clasa" };
	QPushButton* btn_sortare_nume = new QPushButton{ "Sortare dupa nume" };
	QPushButton* btn_sortare_medie = new QPushButton{ "Sortare dupa medie" };
	QPushButton* btn_restart = new QPushButton{ "Restart" };
	QPushButton* btn_sterge = new QPushButton{ "Sterge" };
	QLineEdit* detalii = new QLineEdit;
	void init_gui();
	void conectare();
	void load_data(vector<elev>elevi);
public:
	GUI(Service& service) :service{ service } {
		init_gui();
		load_data(service.get_all());
		conectare();
	}

};