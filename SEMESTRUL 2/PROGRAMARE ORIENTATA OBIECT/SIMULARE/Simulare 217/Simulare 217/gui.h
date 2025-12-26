#pragma once
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
#include<qHBoxLayout>
#include<qFormLayout>
#include<QVBoxLayout>
class Gui : public QWidget {
private:
	Service& service;
	QListWidget* lista = new QListWidget;
	QTableWidget* table = new QTableWidget;
	QLabel* label = new QLabel{ "detalii" };
	QLineEdit* edit = new QLineEdit;
	QPushButton* btn_informatica = new QPushButton{ "informatica" };
	QPushButton* btn_desen = new QPushButton{ "desen+pictura" };
	QPushButton* btn_fotografie = new QPushButton{ "fotografie" };
	QPushButton* btn_muzica = new QPushButton{ "muzica" };
	QPushButton* btn_jurnalism = new QPushButton{ "jurnalism" };;
	QPushButton* btn_restart = new QPushButton{ "restart" };
	QPushButton* btn_sort = new QPushButton{ "sorteaza dupa nume" };
	void connect();
	void init_gui();
	void load_data(vector<Elev>elevi);
	void tabel(vector<Elev>elevi);
public:
	Gui(Service& service) :service{ service } {
		connect();
		init_gui();
		load_data(service.get_all());
	}
};