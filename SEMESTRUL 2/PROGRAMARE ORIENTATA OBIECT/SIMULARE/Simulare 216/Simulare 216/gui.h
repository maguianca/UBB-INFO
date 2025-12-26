#pragma once
#include<iostream>
#include"service.h"
#include<QApplication>
#include<QWidget>
#include<QTableWidget>
#include<QListWidget>
#include<QPushButton>
#include<QLabel>
#include<QLineEdit>
#include<QMessageBox>
class Gui: public QWidget{
private:
	Service& service;
	QListWidget* lista = new QListWidget;
	QTableWidget* table = new QTableWidget;
	QLabel* lable = new QLabel{ "detalii" };
	QLineEdit* edit = new QLineEdit;
	QPushButton* btn_informatica = new QPushButton{ "informatica" };
	QPushButton* btn_desen = new QPushButton{ "desen+pictura" };
	QPushButton* btn_fotografie = new QPushButton{ "fotografie" };
	QPushButton* btn_muzica = new QPushButton{ "muzica" };
	QPushButton* btn_jurnalism = new QPushButton{ "jurnalism" };;
	void connect();
	void init_gui();
	void load_data(vector<Elev>elevi);
public:
	Gui(Service& service) :service{ service } {
		connect();
		init_gui();
		load_data(service.get_all());
	}
};