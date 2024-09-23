#pragma once
#include"service.h"
#include<QWidget>
#include<QTableWidget>
#include<QLabel>
#include<QLineEdit>
#include<QHBoxLayout>
#include<QPushButton>
#include<QFormLayout>
#include<QMessageBox>
#include"ferestre.h"
#include"observer.h"
class GUI :public QWidget, public Observer {
private:
	Service& service;
	QTableWidget* table;
	QPushButton* btn_add = new QPushButton{ "Adauga" };
	QPushButton* btn_reset = new QPushButton{ "Reset" };
	QLineEdit* edit_id = new QLineEdit;
	QLineEdit* edit_descriere = new QLineEdit;
	QLineEdit* edit_programator= new QLineEdit;
	QLineEdit* edit_stare = new QLineEdit;
	QLineEdit* edit_filtrare = new QLineEdit;
	//vector<Fereastra*>ferestre;
	//adauga in tabela pozitiile din vectorul parametru
	void load_table(vector<Task>all);
	//initializeaza gui
	void init_gui();
	//conecteaza compunentele cu semnale
	void connect();
public:
	GUI(Service& service) :service{ service } {
		init_gui();
		connect();
		load_table(service.sorteaza());
		service.addObserver(this);
	}
	void update()override {
		load_table(service.sorteaza());
	}
	~GUI(){ 
		service.removeObserver(this); 
	}
	//constructor 
};