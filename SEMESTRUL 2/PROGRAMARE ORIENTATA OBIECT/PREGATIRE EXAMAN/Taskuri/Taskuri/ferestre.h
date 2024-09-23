#pragma once
#include"observer.h"
#include"service.h"
#include<QWidget>
#include<QLabel>
#include<QHBoxLayout>
#include<QPushButton>
#include<QListWidget>
using namespace std;
class Fereastra :public QWidget, public Observer {
private:
	string text;
	Service& service;
	QPushButton* btn1;
	QPushButton* btn2;
	QPushButton* btn3;
	QListWidget* lista=new QListWidget;
	void init_gui() {
		QHBoxLayout* lay = new QHBoxLayout;
		setLayout(lay);
		lay->addWidget(lista);
		btn3 = new QPushButton{"close"};
		btn1 = new QPushButton{"inprogress"};
		btn2 = new QPushButton{"open"};
		lay->addWidget(btn3);
		lay->addWidget(btn1);
		lay->addWidget(btn2);
		setWindowTitle(QString::fromStdString(text));
	}
	void load_lista(vector<Task>all) {
		lista->clear();
		for (auto l : all) {
			auto item = new QListWidgetItem(QString::fromStdString(to_string(l.get_id()) + " " + l.get_descriere() + " " + l.get_programatori_string()));
			lista->addItem(item);
			item->setData(Qt::UserRole, QString::number(l.get_id()));
		}
	}
	void connect() {
		QObject::connect(btn1, &QPushButton::clicked, this, [&] {
			if (!lista->selectedItems().isEmpty()) {
				int item = lista->selectedItems()[0]->data(Qt::UserRole).toString().toInt();
				qDebug() << item;
				service.modifica(item, "inprogress");
				load_lista(service.stare(text));
				
			}
			});
		QObject::connect(btn2, &QPushButton::clicked, this, [&] {
			if (!lista->selectedItems().isEmpty()) {
				int item = lista->selectedItems()[0]->data(Qt::UserRole).toString().toInt();
				qDebug() << item;
				service.modifica(item, "open");
				load_lista(service.stare(text));
			}
			});
		QObject::connect(btn3, &QPushButton::clicked, this, [&] {
			if (!lista->selectedItems().isEmpty()) {
				int item = lista->selectedItems()[0]->data(Qt::UserRole).toString().toInt();
				qDebug() << item;
				service.modifica(item, "close");
				load_lista(service.stare(text));
			}
			});
	}
public:
	Fereastra(Service& service, const string& text) :service{ service },text { text } {
		init_gui();
		service.addObserver(this);
		connect();
		load_lista(service.stare(text));
		update();
	}
	void update()override {
		load_lista(service.stare(text));
	}
	~Fereastra() {
		service.removeObserver(this);
	}
};