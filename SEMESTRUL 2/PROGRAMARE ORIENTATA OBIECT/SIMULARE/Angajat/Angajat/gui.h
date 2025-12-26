#pragma once
#include<QApplication>
#include<QWidget>
#include<QLineEdit>
#include<QPushButton>
#include<QListWidget>
#include<QListWidgetItem>
#include<QLabel>
#include<QComboBox>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QFormLayout>
#include"service.h"
class GUI :public QWidget {
	Service& service;
	QListWidget* lista=new QListWidget;
	QPushButton* btn_modifica = new QPushButton{ "&modifica" };
	QPushButton* btn_refresh = new QPushButton{ "&refresh" };
	QLineEdit* edit_nume = new QLineEdit;
	QLineEdit* edit_job = new QLineEdit;
	QComboBox* status = new QComboBox;
	QLineEdit* edit_filtreaza = new QLineEdit;
	QLabel* lbl_filtreaza = new QLabel{ "filtreaza:" };
	void conect();
	void init_gui();
	void load_data(vector<Persoana>persoane);
public:
	GUI(Service& service) :service{ service } {
		conect();
		init_gui();
		load_data(service.get_all());
	}
};