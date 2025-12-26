#include "gui.h"

void Gui::init_gui()
{
	QHBoxLayout* main = new QHBoxLayout;
	this->setLayout(main);
	QWidget* form = new QWidget;
	QVBoxLayout* lform = new QVBoxLayout;
	main->addWidget(form);
	form->setLayout(lform);
	lform->addWidget(lista);
	int coloane = 5, linii = service.get_all().size();
	tabel = new QTableWidget{ coloane,linii };
	tabel->setHorizontalHeaderLabels({ "denumire","marime","pret" });
	lform->addWidget(tabel);
	lform->addWidget(btn_inchiriere);
	lform->addWidget(btn_sortare_pret);
	lform->addWidget(btn_sortare_marime);
	lform->addWidget(btn_nesortat);
	lform->addWidget(btn_stergere);
	lform->addWidget(btn_filtrare);
}

void Gui::conectare()
{
	
	QObject::connect(btn_inchiriere, &QPushButton::clicked, [&]() {
		if (lista->selectedItems().isEmpty())
			QMessageBox::warning(NULL, "info", QString::fromStdString("nu aveti nicio rochie selectata"));
		else {
			QListWidgetItem* item = lista->selectedItems()[0];
			int id = item->data(Qt::UserRole).toString().toInt();
			Rochie& r = service.cautare_rochie(id);
			if (r.get_disponibilitate() == "True") {
				service.seteaza(r, "False");
				qDebug() << QString::fromStdString(r.get_disponibilitate());
				load_data(service.get_all());
			}
			else {
				QMessageBox::warning(NULL, "info", QString::fromStdString("rochia este deja inchiriata"));
			}
				
		}
		});
	QObject::connect(btn_stergere, &QPushButton::clicked, [&]() {
		if (tabel->selectedItems().isEmpty())
			QMessageBox::warning(NULL, "info", QString::fromStdString("nu aveti nicio rochie selectata"));
		else {
			int row = tabel->selectedItems()[0]->row();
			int id = tabel->item(row, 0)->text().toInt();
			qDebug() << tabel->item(row, 0)->data(Qt::UserRole).toString();
			service.stergere(id);
			load_data_tabel(service.get_all());

		}
		});
	QObject::connect(btn_inchiriere, &QPushButton::clicked, [&]() {
		if (tabel->selectedItems().isEmpty())
			QMessageBox::warning(NULL, "info", QString::fromStdString("nu aveti nicio rochie selectata"));
		else {
			int row = tabel->selectedItems()[0]->row();
			int id = tabel->item(row, 0)->text().toInt();
			Rochie& r = service.cautare_rochie(id);
			string disponibilitate = tabel->item(row, 4)->text().toStdString();
			if (disponibilitate == "True") {
				service.seteaza(r, "False");
				qDebug() << QString::fromStdString(r.get_disponibilitate());
				load_data_tabel(service.get_all());
			}
			else {
				QMessageBox::warning(NULL, "info", QString::fromStdString("rochia este deja inchiriata"));
			}

		}
		});
	QObject::connect(btn_nesortat, &QPushButton::clicked, [&]() {
		load_data(service.get_all());
		});
	QObject::connect(btn_sortare_pret, &QPushButton::clicked, [&]() {
		load_data(service.sorteaza_pret());
		});
	QObject::connect(btn_sortare_marime, &QPushButton::clicked, [&]() {
		load_data(service.sorteaza_marime());
		});
	QObject::connect(btn_filtrare, &QPushButton::clicked, [&]() {
		load_data(service.filtreaza());
		});
}

void Gui::load_data(vector<Rochie> rochii)
{
	lista->clear();
	lista->addItem("Denumire   Marime   Pret");
	for (auto& l : rochii) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(l.get_denumire() + "  " + l.get_marime() + "  " + to_string(l.get_pret())));
		item->setData(Qt::UserRole, QString::number(l.get_cod()));
		if (l.get_disponibilitate() == "True")
			item->setBackground(Qt::green);
		else if (l.get_disponibilitate() == "False")
			item->setBackground(Qt::red);
		lista->addItem(item);
	}
}

void Gui::load_data_tabel(vector<Rochie> rochii)
{
	tabel->clearContents();
	tabel->setRowCount(rochii.size());
	for (int i = 0; i < rochii.size(); i++) {
		tabel->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(to_string(rochii[i].get_cod()))));
		tabel->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(rochii[i].get_denumire())));
		tabel->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(rochii[i].get_marime())));
		tabel->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(to_string(rochii[i].get_pret()))));
		tabel->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(rochii[i].get_disponibilitate())));
		tabel->item(i, 0)->setData(Qt::UserRole, QString::fromStdString(to_string(100)));
		if (rochii[i].get_disponibilitate() == "True")
			for (int j = 0; j < 5; j++)
				tabel->item(i, j)->setBackground(Qt::green);
		else
			for (int j = 0; j < 5; j++)
				tabel->item(i, j)->setBackground(Qt::red);
	}

}
