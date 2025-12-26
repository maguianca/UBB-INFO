#pragma once
#include"service.h"
#include<QWidget>
#include<QListWidget>
#include<QPushButton>
#include<QDateEdit>
class GUI :public QWidget {
private:
	Service& service;
	QListWidget* lista = new QListWidget;
	QPushButton* btn_sterge = new QPushButton{ "sterge" };
	QPushButton* btn_filtrare = new QPushButton{ "filtrare" };
	QDateEdit* edit_1 = new QDateEdit;
	QDateEdit* edit_2 = new QDateEdit;
	void init_gui();
	void load_data(vector<Razboi>r);
	void connect();
public:
	GUI(Service& service) :service{ service } {
		init_gui();
		connect();
		load_data(service.get_all());
	}
};