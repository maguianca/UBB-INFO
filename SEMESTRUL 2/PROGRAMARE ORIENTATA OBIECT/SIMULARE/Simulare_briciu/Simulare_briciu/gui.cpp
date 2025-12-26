#include "gui.h"
#include<random>
void GUI::conectare()
{
	QObject::connect(btn_adauga, &QPushButton::clicked, [&]() {
		string d = destinatie->itemText(destinatie->currentIndex()).toStdString();
		string p = perioada->itemText(perioada->currentIndex()).toStdString();
		double avans = edit_avans->text().toDouble();
		double pret = edit_pret->text().toDouble();
		service.adauga(d, p, avans, pret);
		load_data(service.get_all());
		});
	QObject::connect(btn_sterge, &QPushButton::clicked, [&]() {
		if (tabel->selectedItems().isEmpty())
		{
			QMessageBox::warning(NULL, "info", QString::fromStdString("Nu este niciun element selectat"));
			return;
		}
		int r = tabel->selectedItems()[0]->row();
		string dest = tabel->item(r, 0)->text().toStdString();
		string per = tabel->item(r, 1)->text().toStdString();
		edit_pret->setText(tabel->item(r, 2)->text());
		edit_avans->setText(tabel->item(r, 3)->text());
		if (dest == "Spania")
			destinatie->setCurrentIndex(0);
		if (dest == "Norvegia")
			destinatie->setCurrentIndex(1);
		if (dest == "Grecia")
			destinatie->setCurrentIndex(2);
		if (dest == "Franta")
			destinatie->setCurrentIndex(3);
		if (dest == "SUA")
			destinatie->setCurrentIndex(4);
		if (per == "20-28 iunie")
			perioada->setCurrentIndex(0);
		if (per == "13-20 iulie")
			perioada->setCurrentIndex(1);
		if (per == "12-19 august")
			perioada->setCurrentIndex(2);
		double avans = edit_avans->text().toDouble();
		double pret = edit_pret->text().toDouble();
		service.stergere(dest, per, pret, avans);
		load_data(service.get_all());
		});
	QObject::connect(slider, &QSlider::sliderReleased, [&]() {
		int val = slider->value();
		procent->setText(QString::fromStdString(to_string(val)));
		});
	QObject::connect(btn_discount, &QPushButton::clicked, [&]() {
		int val = slider->value();
		procent->setText(QString::fromStdString(to_string(val)));
		service.discount(val);
		load_data(service.get_all());
		});
	QObject::connect(btn_tombola, &QPushButton::clicked, [&]() {
		int val = spin->value();
		service.export_to_file(service.random(val));
		});
	QObject::connect(btn_salveaza, &QPushButton::clicked, [&]() {
			if (grecia->isChecked() || spania->isChecked() || norvegia->isChecked()) {
				string fisier = edit_fisier->text().toStdString();
				if (fisier.find(".txt")!= std::string::npos) {
					std::ofstream file(fisier);
					if (!file.is_open()) {
						QMessageBox::warning(nullptr, "info", "Nu se poate deschide fisierul");
						return;
					}
					for (auto& o : service.get_all()) {
						if ((grecia->isChecked() && o.get_destinatie() == "Grecia") ||
							(spania->isChecked() && o.get_destinatie() == "Spania") ||
							(norvegia->isChecked() && o.get_destinatie() == "Norvegia")) {
							file << o.get_destinatie() << "," << o.get_perioada() << "," << o.get_pret() << "," << o.get_avans() << std::endl;
						}
					}
					QMessageBox::information(NULL, "info", "s-a salvat in fisier");
					file.close();
				}
				else {
					QMessageBox::warning(NULL, "info", "Fisierul nu are extensia .txt");
				}
			}
			else {
				QMessageBox::warning(NULL, "info", "Nu este selectat niciun QCheckBox");
			}
		});
	QObject::connect(sort_crescator, &QRadioButton::toggled, [&](bool checked) {
		if (checked) {
			load_data(service.sortare_crescator());
			sort_crescator->setChecked(false);
		}
		});
	QObject::connect(sort_descrescator, &QRadioButton::toggled, [&](bool checked) {
		if (checked) {
			load_data(service.sortare_descrescator());
			sort_crescator->setChecked(false);
		}
		});
}

void GUI::init_gui()
{
	QHBoxLayout* main = new QHBoxLayout;
	QVBoxLayout* lright = new QVBoxLayout;
	QVBoxLayout* lleft = new QVBoxLayout;
	QWidget* right = new QWidget;
	QWidget* left = new QWidget;
	setLayout(main);
	main->addWidget(left);
	main->addWidget(right);
	left->setLayout(lleft);
	right->setLayout(lright);
	int lines = 10; int colomns = 4;
	tabel = new QTableWidget{ lines,colomns };
	QStringList header;
	header << "Destinatie" << "Perioada" << "Pret" << "Avans";
	tabel->setHorizontalHeaderLabels(header);
	lleft->addWidget(tabel);
	lleft->addWidget(sort_crescator);
	lleft->addWidget(sort_descrescator);
	lright->addWidget(destinatie);
	lright->addWidget(perioada);
	destinatie->addItem("Spania");
	destinatie->addItem("Norvegia");
	destinatie->addItem("Grecia");
	destinatie->addItem("Franta");
	destinatie->addItem("SUA");
	perioada->addItem("20-28 iunie");
	perioada->addItem("13-20 iulie");
	perioada->addItem("12-19 august");
	QFormLayout* lform = new QFormLayout;
	QWidget* form = new QWidget;
	form->setLayout(lform);
	lform->addRow("Pret:", edit_pret);
	lform->addRow("Avans:", edit_avans);
	lright->addWidget(form);
	lright->addWidget(btn_adauga);
	lright->addWidget(btn_sterge);
	lright->addWidget(slider);
	lright->addWidget(procent);
	lright->addWidget(btn_discount);
	lright->addWidget(spin);
	lright->addWidget(btn_tombola);
	spin->setRange(0, service.get_all().size() - 1);
	lright->addWidget(spania);
	lright->addWidget(grecia);
	lright->addWidget(norvegia);
	lright->addWidget(edit_fisier);
	lright->addWidget(btn_salveaza);
}

void GUI::load_data(vector<Rezervare> oferte)
{
	tabel->clearContents();
	tabel->setRowCount(oferte.size());
	int contor = 0;
	for (auto& o : oferte) {
		tabel->setItem(contor, 0, new QTableWidgetItem(QString::fromStdString(o.get_destinatie())));
		tabel->setItem(contor, 1, new QTableWidgetItem(QString::fromStdString(o.get_perioada())));
		tabel->setItem(contor, 2, new QTableWidgetItem(QString::fromStdString(to_string(o.get_pret()))));
		tabel->setItem(contor, 3, new QTableWidgetItem(QString::fromStdString(to_string(o.get_avans()))));
		if (o.get_avans() > o.get_pret() / 2)
			color(contor);
		contor++;
	}
}
void GUI::color(int row) {
	for (int i = 0; i < 4; i++)
	{
		//tabel->item(row, i)->setBackground(Qt::cyan);
		tabel->item(row, i)->setData(Qt::BackgroundRole, QBrush(Qt::cyan));
	}
}