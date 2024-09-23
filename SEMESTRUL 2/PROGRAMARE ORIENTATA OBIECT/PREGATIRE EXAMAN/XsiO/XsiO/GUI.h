#pragma once
#include<iostream>
#include"service.h"
#include<QWidget>
#include<QPushButton>
#include<QLineEdit>
#include<QHBoxLayout>
#include"model.h"
#include<QTableView>
#include<QFormLayout>
#include<QPushButton>
#include<QMessageBox>
#include"Tabela.h"
#include"Observer.h"
class GUI :public QWidget, public Observer{
private:
	Service& service;
	QTableView* tbl=new QTableView;
	QTableView* tbl_tabela=new QTableView;
	TableModel* model;
	Tabela* tabela;
	QLineEdit* edit_dimensiune = new QLineEdit;
	QLineEdit* edit_id = new QLineEdit;
	QLineEdit* edit_jucator = new QLineEdit;
	QLineEdit* edit_joc = new QLineEdit;
	QLineEdit* edit_stare = new QLineEdit;
	QPushButton* btn_adauga = new QPushButton{ "Adauga" };
	QPushButton* btn_modifica = new QPushButton{ "Modifica" };
	void init_gui();
	void conectare();
	void load_data();

public:
	GUI(Service& service) :service{ service } {
		model = new TableModel{ service };
		tbl->setModel(model);
		tabela = new Tabela{service, "",0 };
		tbl_tabela->setModel(tabela);
		init_gui();
		conectare();
		load_data();
		service.addObserver(this);
	}
	void update()override {
		load_data();
	}
	~GUI() {
		service.removeObserver(this);
	}
};