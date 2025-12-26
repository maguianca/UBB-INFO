#include"ui.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void GUI::init_gui()
{
	QHBoxLayout* main = new QHBoxLayout;
	this->setLayout(main);
	QWidget* left = new QWidget;
	QWidget* right = new QWidget;
	lista = new QListWidget;
	QVBoxLayout* ly_right = new QVBoxLayout;
	QVBoxLayout* ly_left = new QVBoxLayout;
	left->setLayout(ly_left);
	right->setLayout(ly_right);
	ly_left->addWidget(lista);
	btn_restart = new QPushButton("Restart");
	ly_left->addWidget(btn_restart);
	QWidget* b = new QWidget;
	QHBoxLayout* but = new QHBoxLayout;
	b->setLayout(but);
	btn_sterge = new QPushButton{ "Sterge" };
	btn_filtreaza_pret = new QPushButton{ "Filtreaza pret" };
	btn_filtreaza_suprafata = new QPushButton{ "Filtreaza suprafata" };
	QWidget* f = new QWidget;
	QFormLayout* form = new QFormLayout;
	f->setLayout(form);
	form->addRow(lbl_suprafata, edit_suprafata);
	form->addRow(lbl_strada, edit_strada);
	form->addRow(lbl_pret, edit_pret);
	form->addItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed));
	form->addRow("suprafata inferioara:", suprafata_a);
	form->addRow("suprafata superioara:", suprafata_b);
	form->addRow("pret inferior:", pret_a);
	form->addRow("pret superioara:", pret_b);
	ly_right->addWidget(f);
	but->addWidget(btn_sterge);
	but->addWidget(btn_filtreaza_pret);
	but->addWidget(btn_filtreaza_suprafata);
	ly_right->addWidget(b);
	main->addWidget(left);
	main->addWidget(right);

}

void GUI::conectare()
{
	QObject::connect(btn_restart, &QPushButton::clicked, [&]() {
		load_data(service.get_all());
		edit_suprafata->clear();
		edit_strada->clear();
		edit_pret->clear();
		suprafata_a->clear();
		suprafata_b->clear();
		pret_b->clear();
		pret_a->clear();
		});
	QObject::connect(btn_sterge, &QPushButton::clicked, [&]() {
		try {
			string strada = edit_strada->text().toStdString();
			int pret = edit_pret->text().toInt();
			int suprafata = edit_suprafata->text().toInt();
			edit_strada->clear();
			edit_pret->clear();
			edit_suprafata->clear();
			service.sterge(suprafata, strada, pret);
			load_data(service.get_all());
			QMessageBox::information(this, "info", QString::fromStdString("Obiect sters cu succes!"));
		}
		catch (std::exception) {
		QMessageBox::warning(this, "eroare", QString::fromStdString("nu exista elementul"));
		}
		});
	QObject::connect(lista, &QListWidget::itemClicked, [&]() {
		QListWidgetItem* item = lista->currentItem();
		edit_suprafata->setText(QString::number(service.cauta_suprafata(item->text().toStdString())));
		edit_pret->setText(QString::number(service.cauta_pret(item->text().toStdString())));
		edit_strada->setText(QString::fromStdString(service.cauta_strada(item->text().toStdString())));
		});
	QObject::connect(btn_filtreaza_pret, &QPushButton::clicked, [&]() {
		try {
			//int a = stoi(pret_a->text().toStdString());
			//int b = stoi(pret_b->text().toStdString());
			int a = pret_a->text().toInt();
			int b = pret_b->text().toInt();
			load_data(service.filtreaza_pret(a,b));
		}
		catch (exception e)
		{
			QMessageBox::warning(this, "eroare", "In edit line trb sa fie int-uri");
		}
		});
	QObject::connect(btn_filtreaza_suprafata, &QPushButton::clicked, [&]() {
		try {
			int a = stoi(suprafata_a->text().toStdString());
			int b = stoi(suprafata_b->text().toStdString());
			load_data(service.filtreaza_suprafete(a, b));
		}
		catch (exception e)
		{
			QMessageBox::warning(this, "eroare", "In edit line trb sa fie int-uri");
		}
		});
}

void GUI::load_data(vector<Apartament>apartamente)
{
	lista->clear();
	lista->addItem("Suprafata    Strada     Pret");
	for (int i = 0; i < apartamente.size(); i++)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(to_string(apartamente[i].get_suprafata()) + "   " + apartamente[i].get_strada() + "   " +to_string( apartamente[i].get_pret())));
		lista->addItem(item);
	}
}
