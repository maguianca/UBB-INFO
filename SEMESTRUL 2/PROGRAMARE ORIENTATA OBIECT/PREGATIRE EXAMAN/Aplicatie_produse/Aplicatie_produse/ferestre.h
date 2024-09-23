#pragma once
#include"observer.h"
#include"service.h"
#include<QWidget>
#include<QLabel>
#include<QHBoxLayout>
using namespace std;
class Fereastra :public QWidget, public Observer {
private:
	Service& service;
	string nume;
	int count;
	QLabel* lbl = new QLabel;
	void init_gui() {
		QHBoxLayout* lay = new QHBoxLayout;
		setLayout(lay);
		lay->addWidget(lbl);
		setWindowTitle(QString::fromStdString(nume));
		//setWindowIconText(QString::fromStdString(nume));
	}
public:
	Fereastra(Service& service, const string& nume, int count) :service{ service },nume { nume }, count{ count } {
		init_gui();
		service.addObserver(this);
		update();
	};
	//construtor Fereastra-service;
	void update()override {
		map<string, int> rez = service.ret_tip();
		int count = 0;
		auto it = rez.find(nume);
		if (it != rez.end()) {
			count = it->second;
		}
		else
			count = 0;
		lbl->setText(QString::number(count));
	}
	~Fereastra() {
		service.removeObserver(this);
	}
};