#include "GUIModele.h"

void ModelGUI::initializare_gui()
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
	//int Lines = 10;
	//int Columns = 4;
	//this->tableOferte = new QTableWidget{ Lines,Columns };
	//QStringList table_header;
	//table_header << "Denumire" << "Destinatie" << "Tip" << "Pret";
	//this->tableOferte->setHorizontalHeaderLabels(table_header);
	//this->tableOferte->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	lyRight->addWidget(tbl);
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

void ModelGUI::conectare()
{
	QObject::connect(btn_adauga, &QPushButton::clicked, this, &ModelGUI::gui_adauga);
	QObject::connect(btn_modifica, &QPushButton::clicked, this, &ModelGUI::gui_modifica);
	QObject::connect(btn_sterge, &QPushButton::clicked, this, &ModelGUI::gui_stergere);
	QObject::connect(btn_exit, &QPushButton::clicked, this, [&]() {
		QMessageBox::information(this, "Info", "Terminare program!");
		close();
		});
	QObject::connect(btn_filtrare_destinatie, &QPushButton::clicked, this, [&]() {
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
		this->load_data(this->service.get_all());
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
	QObject::connect(tbl->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (tbl->selectionModel()->selectedIndexes().isEmpty()) {
			edit_denumire->setText("");
			edit_destinatie->setText("");
			edit_tip->setText("");
			edit_pret->setText("");
			return;
		}
		qDebug() << "hahah";
		int selRow = tbl->selectionModel()->selectedIndexes().at(0).row();
		auto cel0Index = tbl->model()->index(selRow, 0);
		auto cel0Value = tbl->model()->data(cel0Index, Qt::DisplayRole).toString();
		edit_denumire->setText(cel0Value);
		auto cel1Index = tbl->model()->index(selRow, 1);
		auto cel1Value = tbl->model()->data(cel1Index, Qt::DisplayRole).toString();
		edit_destinatie->setText(cel1Value);
		auto cel2Index = tbl->model()->index(selRow, 2);
		auto cel2Value = tbl->model()->data(cel2Index, Qt::DisplayRole).toString();
		edit_tip->setText(cel2Value);
		auto cel3Index = tbl->model()->index(selRow, 3);
		auto cel3Value = tbl->model()->data(cel3Index, Qt::DisplayRole).toString();
		edit_pret->setText(cel3Value);
		});

}

void ModelGUI::load_data(vector<Turism> oferte)
{
	this->modelTabel->setOferte(oferte);
}

void ModelGUI::load_data_cos(vector<Turism> oferte)
{
	lista_cos->clear();
	for (const auto& elem : oferte) {
		auto item = new QListWidgetItem(QString::fromStdString(
			elem.get_denumire() + " " + elem.get_destinatie() + " " + elem.get_tip() + " " + std::to_string(elem.get_pret())
		));
		lista_cos->addItem(item);
	}
}

void ModelGUI::gui_adauga()
{
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

void ModelGUI::gui_modifica()
{
	try {
		string denumire = edit_denumire->text().toStdString();
		string destinatie = edit_destinatie->text().toStdString();
		string tip = edit_tip->text().toStdString();
		int pret = edit_pret->text().toInt();
		string tip_nou = edit_tip_nou->text().toStdString();
		int pret_nou = edit_pret_nou->text().toInt();

		edit_denumire->clear();
		edit_destinatie->clear();
		edit_tip->clear();
		edit_pret->clear();
		edit_pret_nou->clear();
		edit_tip_nou->clear();

		this->service.modifica(denumire, destinatie, tip, pret, tip_nou, pret_nou);
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

void ModelGUI::gui_stergere()
{
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
