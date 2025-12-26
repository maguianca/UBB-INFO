#include"ui.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void GUI::init_gui()
{
	QHBoxLayout* lyMain = new QHBoxLayout;
	this->setLayout(lyMain);
	QWidget* left = new QWidget;
	QWidget* right = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);
	lista_procesoare = new QListWidget;
	lyLeft->addWidget(lista_procesoare);
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);
	lista_placi = new QListWidget;
	lyRight->addWidget(lista_placi);
	btn_adauga = new QPushButton("adauga");
	QWidget* f = new QWidget;
	QFormLayout* form = new QFormLayout;
	f->setLayout(form);
	form->addRow(lbl_nume, edit_nume);
	form->addRow(lbl_soclu, edit_soclu);
	form->addRow(lbl_pret, edit_pret);
	form->addWidget(btn_adauga);
	QHBoxLayout* r = new QHBoxLayout;
	btn_pret = new QPushButton("calculeaza");
	btn_filtreaza = new QPushButton("filtreaza");
	btn_restart = new QPushButton("restart");
	QWidget* butoane = new QWidget;
	butoane->setLayout(r);
	lyRight->addWidget(f);
	lyRight->addWidget(butoane);
	r->addWidget(btn_pret);
	r->addWidget(btn_filtreaza);
	r->addWidget(btn_restart);
	right->setLayout(r);
	lyMain->addWidget(left);
	lyMain->addWidget(right);
}

void GUI::conectare()
{
	QObject::connect(btn_adauga, &QPushButton::clicked,this, [&]() {
		string nume = edit_nume->text().toStdString();
		string soclu = edit_soclu->text().toStdString();
		int pret = edit_pret->text().toInt();
		edit_nume->clear();
		edit_soclu->clear();
		edit_pret->clear();
		this->service.adauga(nume, soclu, pret);
		this->load_data_1(this->service.get_all_placi());
		QMessageBox::information(this, "info", QString::fromStdString("Placa adaugata cu succes!"));
		});
	QObject::connect(btn_restart, &QPushButton::clicked, this, [&]() {
		load_data_2(service.get_all_procesoare());
		load_data_1(service.get_all_placi());
		edit_nume->clear();
		edit_soclu->clear();
		edit_pret->clear();
		});
	QObject::connect(btn_filtreaza, &QPushButton::clicked, [&]() {
		load_data_1(service.filtrare(edit_soclu->text().toStdString()));
		});
	QObject::connect(lista_procesoare, &QListWidget::itemClicked, [&]() {
		QListWidgetItem* item = lista_procesoare->currentItem();
		edit_soclu->setText(QString::fromStdString(service.cauta(item->text().toStdString())));
		edit_pret->setText(QString::number(service.numar(item->text().toStdString())));
		pret_procesor = service.numar(item->text().toStdString());
		});
	QObject::connect(lista_placi, &QListWidget::itemClicked, [&]() {
		QListWidgetItem* item = lista_placi->currentItem();
		edit_pret->setText(QString::number(service.numar_2(item->text().toStdString())));
		pret_placa = service.numar_2(item->text().toStdString());
		if (pret_placa != 0 && pret_procesor != 0)
		{
			pret_total = pret_placa + pret_procesor;
			pret_placa = 0;
			pret_procesor = 0;
		}
		});
	QObject::connect(btn_pret, &QPushButton::clicked, [&](){
		if (lista_placi->selectedItems().isEmpty() || lista_procesoare->selectedItems().isEmpty())
		QMessageBox::information(this, "Info", QString::fromStdString("Nu ati selectat destule produse"));
		else {
			int pret = lista_placi->selectedItems()[0]->data(Qt::UserRole).toInt();
			pret += lista_procesoare->selectedItems()[0]->data(Qt::UserRole).toInt();
			QMessageBox::information(this, "Info", QString::fromStdString("Pretul pentru produsele selectate este " + to_string(pret)));
		}
		});
		/*
	QObject::connect(btn_pret, &QPushButton::clicked, [&]() {
		if (pret_total != 0) {
			QMessageBox::information(this, "Info", QString::fromStdString("Pretul pentru produsele selectate este " +to_string(pret_total)));
			pret_total = 0;
			lista_procesoare->clearSelection();
			lista_placi->clearSelection();
		}
		else
			QMessageBox::information(this, "Info", QString::fromStdString("Nu ati selectat destule produse"));
		});*/
}

void GUI::load_data_1(vector<PlacaDeBaza> p1)
{
	lista_placi->clear();
	lista_placi->addItem("nume");
	for (int i = 0; i < p1.size(); i++)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(p1[i].get_nume()));
		lista_placi->addItem(item);
		item->setData(Qt::UserRole, QString::number(p1[i].get_pret()));
	}
}

void GUI::load_data_2(vector<Procesor1> p2)
{
	lista_procesoare->clear();
	lista_procesoare->addItem("nume    numarThreaduri");
	for (int i = 0; i < p2.size(); i++)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(p2[i].get_nume()+"      "+to_string(p2[i].get_numar())));
		lista_procesoare->addItem(item);
		item->setData(Qt::UserRole, QString::number(p2[i].get_pret()));
	}
}
