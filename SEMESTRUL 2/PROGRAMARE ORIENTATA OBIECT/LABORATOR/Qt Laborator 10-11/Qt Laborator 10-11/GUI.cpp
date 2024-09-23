#include "GUI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

void GUI::initializare_gui()
{
	QHBoxLayout* lyMain = new QHBoxLayout;
	this->setLayout(lyMain);

	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);
	
	QWidget* form = new QWidget;
	QFormLayout* lyForm = new QFormLayout;
	form->setLayout(lyForm);
	edit_denumire = new QLineEdit;
	edit_destinatie = new QLineEdit;
	edit_tip = new QLineEdit;
	edit_pret = new QLineEdit;
	edit_tip_nou = new QLineEdit;
	edit_pret_nou = new QLineEdit;

	lyForm->addRow(lbl_denumire, edit_denumire);
	lyForm->addRow(lbl_destinatie, edit_destinatie);
	lyForm->addRow(lbl_tip, edit_tip);
	lyForm->addRow(lbl_pret, edit_pret);
	lyForm->addItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed));
	lyForm->addRow(lbl_pret_nou, edit_pret_nou);
	lyForm->addRow(lbl_tip_nou, edit_tip_nou);

	QWidget* form1 = new QWidget;
	QHBoxLayout* lyForm1 = new QHBoxLayout;
	form1->setLayout(lyForm1);
	btn_adauga = new QPushButton("Adauga oferta");
	lyForm1->addWidget(btn_adauga);
	btn_modifica = new QPushButton("Modifica oferta");
	lyForm1->addWidget(btn_modifica);
	btn_sterge = new QPushButton("Stergere oferta");
	lyForm1->addWidget(btn_sterge);

	lyLeft->addWidget(form);
	lyLeft->addWidget(form1);

	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);
	QWidget* but = new QWidget;
	//QHBoxLayout* ly_butoane = new QHBoxLayout;
	but->setLayout(ly_butoane);

	lyRight->addWidget(but);
	//tabel
	int Lines = 10;
	int Columns = 4;
	this->tableOferte = new QTableWidget{ Lines,Columns };
	QStringList table_header;
	table_header << "Denumire" << "Destinatie" << "Tip" << "Pret";
	this->tableOferte->setHorizontalHeaderLabels(table_header);
	this->tableOferte->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	lyRight->addWidget(tableOferte);
	lista = new QListWidget;
	lyRight->addWidget(lista);
	//filtrare
	QWidget* formFilter = new QWidget;
	QFormLayout* lyform = new QFormLayout;
	formFilter->setLayout(lyform);

	edit_filtrare_pret = new QLineEdit;
	lyform->addRow(lbl_filtrare_pret, edit_filtrare_pret);
	btn_filtrare_pret = new QPushButton("Filtreaza oferte dupa pret");
	lyform->addWidget(btn_filtrare_pret);
	edit_filtrare_destinatie = new QLineEdit;
	lyform->addRow(lbl_filtrare_destinatie, edit_filtrare_destinatie);
	btn_filtrare_destinatie = new QPushButton("Filtreaza oferte dupa destinatie");
	lyform->addWidget(btn_filtrare_destinatie);
	
	lyLeft->addWidget(formFilter);
	//sortare
	QVBoxLayout* lyRadioBox = new QVBoxLayout;
	group_box->setLayout(lyRadioBox);
	lyRadioBox->addWidget(radio_sortare_denumire);
	lyRadioBox->addWidget(radio_sortare_destinatie);
	lyRadioBox->addWidget(radio_sortare_tip_pret);

	btn_sortare = new QPushButton("Sortare oferte");
	lyRadioBox->addWidget(btn_sortare);
	lyLeft->addWidget(group_box);

	btn_reload_data = new QPushButton("Reload data");
	lyLeft->addWidget(btn_reload_data);
	btn_undo = new QPushButton("Undo");
	lyLeft->addWidget(btn_undo);
	btn_exit = new QPushButton("Exit");
	lyLeft->addWidget(btn_exit);

	btn_cos = new QPushButton("CosCRUDGui");
	lyRight->addWidget(btn_cos);
	btn_desenare = new QPushButton("CosReadOnlyGui");
	lyRight->addWidget(btn_desenare);
	
	lyMain->addWidget(left);
	lyMain->addWidget(right);
}
void GUI::conectare()
{
	QObject::connect(btn_adauga, &QPushButton::clicked, this, &GUI::gui_adauga);
	QObject::connect(btn_modifica, &QPushButton::clicked, this, &GUI::gui_modifica);
	QObject::connect(btn_sterge, &QPushButton::clicked, this, &GUI::gui_stergere);
	QObject::connect(btn_exit, &QPushButton::clicked, this, [&]() {
		QMessageBox::information(this, "Info", "Terminare program!");
		close();
		});
	QObject::connect(btn_filtrare_destinatie, &QPushButton::clicked,this,[&]() {
		string text1 = this->edit_filtrare_destinatie->text().toStdString();
		edit_filtrare_destinatie->clear();
		load_data(service.filtrare_destinatie(text1));
		});
	QObject::connect(btn_filtrare_pret, &QPushButton::clicked, this, [&]() {
		double text2 = this->edit_filtrare_pret->text().toDouble();
		edit_filtrare_pret->clear();
		load_data(service.filtrare_pret(text2));
		});
	QObject::connect(btn_undo, &QPushButton::clicked, this, [&]() {
		try {
			service.undo();
			load_data(service.get_all());
			QMessageBox::information(this, "Info", QString::fromStdString("Undo realizat cu succes"));
		}
		catch (RepoException& ex) {
			QMessageBox::warning(this, "Info", QString::fromStdString(ex.get_mesaj()));
		}
		});
	QObject::connect(btn_reload_data, &QPushButton::clicked, this, [&]() {
		this->load_data(service.get_all());
		});
	QObject::connect(btn_sortare, &QPushButton::clicked, [&]() {
		if (radio_sortare_denumire->isChecked()) {
			load_data(service.sortare_denumire());
			radio_sortare_denumire->setChecked(false);
		}
		else if (radio_sortare_destinatie->isChecked()) {
			load_data(service.sortare_denumire());
			radio_sortare_destinatie->setChecked(false);
		}
		else if (radio_sortare_tip_pret->isChecked()) {
			load_data(service.sortare_tip_pret());
			radio_sortare_tip_pret->setChecked(false);
		}
		});
	QObject::connect(btn_cos, &QPushButton::clicked, [&]() {
		auto fereastraCos = new CosLista{ service.getCos() };
		});
	QObject::connect(btn_desenare, &QPushButton::clicked, [&]() {
		auto window = new HistogramGUI{ service.getCos() };
		window->show();
		});
	/*
	QObject::connect(btn_cos, &QPushButton::clicked, [&]() {
		lista_cos = new QListWidget;
		fereastra = new QWidget;
		QFormLayout* lyCos = new QFormLayout;
		fereastra->setLayout(lyCos);
		denumire_cos = new QLineEdit;
		destinatie_cos = new QLineEdit;
		tip_cos = new QLineEdit;
		pret_cos = new QLineEdit;
		lyCos->addRow("Denumire:", denumire_cos);
		lyCos->addRow("Destinatie:", destinatie_cos);
		lyCos->addRow("Tip:", tip_cos);
		lyCos->addRow("Pret:", pret_cos);
		btn_adauga_cos = new QPushButton("Adauga oferta existenta");
		btn_random_cos = new QPushButton("Adauga oferte random");
		btn_goleste_cos = new QPushButton("Goleste Cos");
		btn_export_cos = new QPushButton("Exporta Cos");
		btn_exit_cos = new QPushButton("Exit Wishlist");
		edit_random_cos = new QLineEdit;
		edit_export_cos = new QLineEdit;
		lyCos->addWidget(btn_adauga_cos);
		lyCos->addRow(lbl_random,edit_random_cos);
		lyCos->addWidget(btn_random_cos);
		lyCos->addWidget(btn_goleste_cos);
		lyCos->addRow(lbl_export,edit_export_cos);
		lyCos->addWidget(btn_export_cos);
		lyCos->addWidget(btn_exit_cos);
		lyCos->addWidget(lista_cos);
		fereastra->show();
		QObject::connect(btn_exit_cos, &QPushButton::clicked, this, [&]() {
		QMessageBox::information(this, "Info", "Inchidere Wishlist");
		fereastra->close();
		});
		QObject::connect(btn_adauga_cos, &QPushButton::clicked, [&]() {
			try {
				string denumire = denumire_cos->text().toStdString();
				string destinatie = destinatie_cos->text().toStdString();
				string tip = tip_cos->text().toStdString();
				double pret = pret_cos->text().toDouble();
				service.cosAdauga(denumire, destinatie, tip, pret);
				denumire_cos->clear();
				destinatie_cos->clear();
				tip_cos->clear();
				pret_cos->clear();
				load_data_cos(service.getAllCos());
			}
			catch (RepoException& ex) {
				QMessageBox::warning(this, "Info", QString::fromStdString(ex.get_mesaj()));
			}
			});
		QObject::connect(btn_random_cos, &QPushButton::clicked, [&]() {
			try {
				int nr = edit_random_cos->text().toInt();
				edit_random_cos->clear();
				service.cosAdaugaRandom(nr);
				load_data_cos(service.getAllCos());
			}
			catch (RepoException& ex) {
				QMessageBox::warning(this, "Info", QString::fromStdString(ex.get_mesaj()));
			}
			});
		QObject::connect(btn_goleste_cos, &QPushButton::clicked, [&]() {
			try {
				service.cosSterge();
				load_data_cos(service.getAllCos());
			}
			catch (RepoException& ex) {
				QMessageBox::warning(this, "Info", QString::fromStdString(ex.get_mesaj()));
			}
			});
		QObject::connect(btn_export_cos, &QPushButton::clicked, [&]() {
			try {
				string fisier = edit_export_cos->text().toStdString();
				edit_export_cos->clear();
				service.cosExport(fisier);
				lista_cos->clear();
				service.cosSterge();
				load_data_cos(service.getAllCos());
			}
			catch (RepoException& ex) {
				QMessageBox::warning(this, "Info", QString::fromStdString(ex.get_mesaj()));
			}
			});
		
		});
		*/
	

}
void GUI::load_data_cos(vector<Turism>oferte)
{
	lista_cos->clear();
	for (const auto& elem : oferte) {
		auto item = new QListWidgetItem(QString::fromStdString(
			elem.get_denumire() + " " + elem.get_destinatie() + " " + elem.get_tip() + " " + std::to_string(elem.get_pret())
		));
		lista_cos->addItem(item);
	}
}
void GUI::load_data(vector<Turism>oferte)
{
	this->tableOferte->clearContents();
	this->tableOferte->setRowCount(oferte.size());

	int lineNumber = 0;
	for (auto& oferta : oferte) {
		this->tableOferte->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(oferta.get_denumire())));
		this->tableOferte->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(oferta.get_destinatie())));
		this->tableOferte->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(oferta.get_tip())));
		this->tableOferte->setItem(lineNumber, 3, new QTableWidgetItem(QString::number(oferta.get_pret())));
		lineNumber++;
	}
	for (auto button : butoane) {
		ly_butoane->removeWidget(button); 
		delete button;                
	}
	butoane.clear();
	lista->clear();
	lista->addItem("Denumire  Destinatie  Tip   Pret");
	for (int i = 0; i < oferte.size(); i++)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(oferte[i].get_denumire() + "  " + oferte[i].get_destinatie() + " " + oferte[i].get_tip() + "  " + to_string(oferte[i].get_pret())));
		lista->addItem(item);
	}
	std::unordered_map<string, int>tipuri = service.raport();
	for (const auto& pair : tipuri) {
		string tip = pair.first;
		QPushButton* button = new QPushButton(QString::fromStdString(tip));
		ly_butoane->addWidget(button);
		butoane.push_back(button);
		QObject::connect(button, &QPushButton::clicked, [tip, this]() {
			std::unordered_map<string, int>tipuri = service.raport();
			int count = tipuri[tip];
			QMessageBox::information(this, "Info", QString::fromStdString("Numarul ofertelor " + tip + " sunt: %1 ").arg(count));
			});

	}
	
}
void GUI::gui_adauga() {
	try {
		string denumire = edit_denumire->text().toStdString();
		string destinatie = edit_destinatie->text().toStdString();
		string tip = edit_tip->text().toStdString();
		int pret = edit_pret->text().toInt();

		edit_denumire->clear();
		edit_destinatie->clear();
		edit_tip->clear();
		edit_pret->clear();
		edit_pret_nou->clear();
		edit_tip_nou->clear();

		this->service.adauga(denumire, destinatie, tip, pret);
		this->load_data(this->service.get_all());

		QMessageBox::information(this, "Info", QString::fromStdString("Oferta adaugata cu succes!"));

	}
	catch (RepoException& ex1) {
		QMessageBox::warning(this, "Eroare", QString::fromStdString(ex1.get_mesaj()));
	}
	catch (ValException& ex2) {
		QMessageBox::warning(this, "Eroare", QString::fromStdString(ex2.get_mesaj()));
	}

}
void GUI::gui_stergere() {
	try {
		string denumire = edit_denumire->text().toStdString();
		string destinatie = edit_destinatie->text().toStdString();
		string tip = edit_tip->text().toStdString();
		int pret = edit_pret->text().toInt();

		edit_denumire->clear();
		edit_destinatie->clear();
		edit_tip->clear();
		edit_pret->clear();
		edit_pret_nou->clear();
		edit_tip_nou->clear();

		this->service.stergere(denumire, destinatie, tip, pret);
		this->load_data(this->service.get_all());

		QMessageBox::information(this, "Info", QString::fromStdString("Oferta stearsa cu succes!"));


	}
	catch (RepoException& ex1) {
		QMessageBox::warning(this, "Eroare", QString::fromStdString(ex1.get_mesaj()));
	}
	catch (ValException& ex2) {
		QMessageBox::warning(this, "Eroare", QString::fromStdString(ex2.get_mesaj()));
	}

}
void GUI::gui_modifica() {
	try {
		string denumire = edit_denumire->text().toStdString();
		string destinatie = edit_destinatie->text().toStdString();
		string tip= edit_tip->text().toStdString();
		int pret= edit_pret->text().toInt();
		string tip_nou = edit_tip_nou->text().toStdString();
		int pret_nou = edit_pret_nou->text().toInt();

		edit_denumire->clear();
		edit_destinatie->clear();
		edit_tip->clear();
		edit_pret->clear();
		edit_pret_nou->clear();
		edit_tip_nou->clear();

		this->service.modifica(denumire, destinatie, tip, pret,tip_nou,pret_nou);
		this->load_data(this->service.get_all());

		QMessageBox::information(this, "Info", QString::fromStdString("Oferta modificata cu succes!"));

	}
	catch (RepoException& ex1) {
		QMessageBox::warning(this, "Eroare", QString::fromStdString(ex1.get_mesaj()));
	}
	catch (ValException& ex2) {
		QMessageBox::warning(this, "Eroare", QString::fromStdString(ex2.get_mesaj()));
	}

}