#pragma once
#include<QWidget>
#include"service.h"
#include<Qlabel>
#include<QHBoxlayout>
class Fereastra:public Observer,public QWidget {
private:
	Service& service;
	string nume;
	int n;
	QLabel* lbl = new QLabel;
	void init_gui()
	{
		QHBoxLayout* main = new QHBoxLayout;
		this->setLayout(main);
		setWindowTitle(QString::fromStdString(nume));
		lbl->setText(QString::number(n));
		main->addWidget(lbl);

	}
public:
	Fereastra(Service& service, string nume, int n) :service{ service }, nume{ nume }, n{ n } {
		service.addObserver(this);
		init_gui();
	};
	void update()override {
		map<string, int> rez = service.tipuri();
		int count = 0;
		auto it = rez.find(nume);
		if (it != rez.end()) {
			count = it->second;
		}
		else
			count = 0;
		n = count;
		lbl->setText(QString::number(count));
	}
	~Fereastra() {
		service.removeObserver(this);
	}
};