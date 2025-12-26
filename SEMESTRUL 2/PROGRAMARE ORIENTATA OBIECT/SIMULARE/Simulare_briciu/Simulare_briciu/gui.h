#pragma once
#include<QApplication>
#include<QWidget>
#include<QPushButton>
#include<QLineEdit>
#include<QComboBox>
#include<QTableWidget>
#include<QMessageBox>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QFormLayout>
#include<QSlider>
#include<QLabel>
#include<QSpinBox>
#include<QCheckBox>
#include<QColor>
#include<QBrush>
#include<QRadioButton>
#include"service.h"
class GUI :public QWidget {
	Service& service;
	QTableWidget* tabel;
	QComboBox* destinatie = new QComboBox;
	QComboBox* perioada = new QComboBox;
	QPushButton* btn_adauga = new QPushButton{"Adauga"};
	QPushButton* btn_sterge = new QPushButton{"Sterge"};
	QPushButton* btn_discount = new QPushButton{"Aplica Discount"};
	QPushButton* btn_tombola = new QPushButton{"Tombola"};
	QPushButton* btn_salveaza = new QPushButton{"Salveaza filtrat"};
	QLineEdit* edit_pret = new QLineEdit;
	QLineEdit* edit_avans = new QLineEdit;
	QSlider* slider = new QSlider{ Qt::Horizontal };
	QLabel* procent = new QLabel;
	QSpinBox* spin = new QSpinBox;
	QCheckBox* grecia = new QCheckBox("Grecia");
	QCheckBox* spania = new QCheckBox("Spania");
	QCheckBox*norvegia  = new QCheckBox("Norvegia");
	QLineEdit* edit_fisier = new QLineEdit;
	QRadioButton* sort_crescator = new QRadioButton("Sortare dupa crescatoare dupa pret");
	QRadioButton* sort_descrescator = new QRadioButton("Sortare descrecatoare dupa pret");
	void conectare();
	void init_gui();
	void load_data(vector<Rezervare>oferte);
	void color(int row);
public:
	GUI(Service& service) :service{ service } {
		conectare();
		init_gui();
		load_data(service.get_all());
	};

};