#pragma once
#include<QWidget>
#include"service.h"
#include<QApplication>
#include<QTableWidget>
#include<QPushButton>
#include<QListWidget>
#include<QMessageBox>
#include<qHBoxLayout>
#include<qdebug.h>
class Gui :public QWidget {
private:
	Service& service;
	QListWidget* lista = new QListWidget;
	QTableWidget* tabel;
	QPushButton* btn_sortare_pret = new QPushButton{ "Sortare pret" };
	QPushButton* btn_sortare_marime = new QPushButton{ "Sortare marime" };
	QPushButton* btn_nesortat = new QPushButton{ "Nesoratat" };
	QPushButton* btn_inchiriere = new QPushButton{ "Inchiriere rochie" };
	QPushButton* btn_filtrare = new QPushButton{ "filtrare" };
	QPushButton* btn_stergere = new QPushButton{ "stergere" };
	void init_gui();//initializeaza Gui 
	void conectare();//conecteaza componentele din gui interfata grafica cu functionalitatile respective
	void load_data(vector<Rochie>rochii);//populeaza lista QlistWidget cu elementele din vectorul de rochii
	void load_data_tabel(vector<Rochie>rochii);//populeaza lista QlistWidget cu elementele din vectorul de rochii
public:
	Gui(Service& service) :service{ service } {
		init_gui();
		conectare();
		load_data(service.get_all());
		load_data_tabel(service.get_all());
	};
	//constructor Gui primeste atributul service si apeleaza cele 3 metode

};