#pragma once
#include<vector>
#include<string>
#include<QtWidgets/QApplication>
#include<QtWidgets/QLabel>
#include<QtWidgets/QPushButton>
#include<QtWidgets/QLineEdit>
#include<QtWidgets/QHBoxLayout>
#include<QtWidgets/QListWidget>
#include<QtWidgets/QFormLayout>
#include<QtWidgets/QMessageBox>
#include "service.h"
using std::vector;
using std::string;
class GUI :public QWidget {
private:
	Service& service;
	QListWidget* lista_procesoare;
	QListWidget* lista_placi;
	QWidget* fereastra;
	QLabel* lbl_nume = new QLabel{ "nume:" };
	QLabel* lbl_soclu = new QLabel{ "soclu:" };
	QLabel* lbl_pret = new QLabel{ "pret:" };
	QLineEdit* edit_pret=new QLineEdit;
	QLineEdit* edit_nume = new QLineEdit;
	QLineEdit* edit_soclu = new QLineEdit;
	QPushButton* btn_adauga;
	QPushButton* btn_filtreaza;
	QPushButton* btn_pret;
	QPushButton* btn_restart;
	void init_gui();
	void conectare();
	void load_data_1(vector<PlacaDeBaza>p1);
	void load_data_2(vector<Procesor1>p2);
	int pret_procesor=0;
	int pret_placa=0;
	int pret_total = 0;
public:
	GUI(Service& service) :service(service) {
		init_gui();
		conectare();
		load_data_1(service.get_all_placi());
		load_data_2(service.get_all_procesoare());
	}

};