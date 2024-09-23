#pragma once
#include"service.h"
#include<QWidget>
#include<QTableView>
#include<QLabel>
#include<QPushButton>
#include<qlineedit.h>
#include<QHBoxLayout>
#include"model.h"
#include<qformlayout.h>
#include<QMessageBox.h>
#include<QSlider>
#include"ferestre.h"
class GUI :public QWidget {
private:
	Service& service;
	QTableView* table=new QTableView;
	ModelTable* model;
	QLineEdit* edit_nume = new QLineEdit;
	QLineEdit* edit_id = new QLineEdit;
	QLineEdit* edit_tip = new QLineEdit;
	QLineEdit* edit_pret = new QLineEdit;
	QPushButton* btn_adauga = new QPushButton{ "&Adauga" };
	QSlider* slider = new QSlider{ Qt::Horizontal };
	QLabel* label = new QLabel;
	vector<Fereastra*>ferestre;
	void load_data();
	void conectare();
	void init_gui();
public:
	GUI(Service& service) :service{ service } {
	model = new ModelTable{ service };
	table->setModel(model);
	model->setValue(0);
	init_gui();
	conectare();
	load_data();
}
};