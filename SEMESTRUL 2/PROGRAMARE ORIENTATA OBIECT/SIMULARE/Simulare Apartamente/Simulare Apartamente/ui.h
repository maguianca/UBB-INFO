#pragma once
#include<vector>
#include<string>
#include<QtWidgets/QApplication>
#include<QtWidgets/QLabel>
#include<QtWidgets/QPushButton>
#include<QtWidgets/QLineEdit>
#include<QtWidgets/QHBoxLayout>
#include<QtWidgets/QVBoxLayout>
#include<QtWidgets/QListWidget>
#include<QtWidgets/QFormLayout>
#include<QtWidgets/QMessageBox>
#include"service.h"
using std::vector;
using std::string;
class GUI:public QWidget{
private:
	Service& service;
	QListWidget* lista;
	QWidget* fereastra;
	QLabel* lbl_suprafata = new QLabel{ "Suprafata:" };
	QLabel* lbl_strada = new QLabel{ "Strada:" };
	QLabel* lbl_pret = new QLabel{ "Pret:" };
	QLineEdit* edit_suprafata=new QLineEdit;
	QLineEdit* edit_strada = new QLineEdit;
	QLineEdit* edit_pret = new QLineEdit;
	QLineEdit* suprafata_a = new QLineEdit;
	QLineEdit* suprafata_b = new QLineEdit;
	QLineEdit* pret_a = new QLineEdit;
	QLineEdit* pret_b = new QLineEdit;
	QPushButton* btn_sterge;
	QPushButton* btn_filtreaza_pret;
	QPushButton* btn_filtreaza_suprafata;
	QPushButton* btn_restart;
	void init_gui();
	void conectare();
	void load_data(vector<Apartament>apartemente);
public:
	GUI(Service& service) :service{ service } {
		init_gui();
		conectare();
		load_data(service.get_all());
	}
};