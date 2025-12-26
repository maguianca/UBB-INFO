#include"gui.h"
#include<iostream>
using namespace std;

void GUI::init_gui()
{
	QHBoxLayout* main = new QHBoxLayout;
	this->setLayout(main);
	main->addWidget(lista);
	QVBoxLayout* dr = new QVBoxLayout;
	main->addLayout(dr);
	QFormLayout* form = new QFormLayout;
	dr->addLayout(form);
	form->addRow(lbl_loc, edit_loc);
	form->addRow(lbl_data, edit_data);
	form->addRow(lbl_intensitate, edit_intensitate);
	form->addRow(lbl_adancime, edit_adancime);
	form->addWidget(btn_adauga);
	QLabel* filtrare = new QLabel{ "Filtrare" };
	dr->addWidget(filtrare);
	dr->addWidget(locatie);
	dr->addWidget(slider);
	dr->addWidget(v_slider);
	slider->setRange(0, 10);

}

void GUI::conectare()
{
	QObject::connect(btn_adauga, &QPushButton::clicked, this, [&]() {
		string locatie = edit_loc->text().toStdString();
		string data = edit_data->text().toStdString();
		int intensitatea = edit_intensitate->text().toInt();
		int adancime = edit_adancime->text().toInt();
		edit_loc->clear();
		edit_data->clear();
		edit_intensitate->clear();
		edit_adancime->clear();
		try {
			service.adaugare(locatie, data, intensitatea, adancime);
			load_locatii();
			load_data(service.get_all());
			//load_locatii();
			QMessageBox::information(this, "info", QString::fromStdString("Adaugat cu succes"));
		}
		catch (ValException& ex)
		{
			QMessageBox::warning(this, "info", QString::fromStdString(ex.get_mesaj()));
		}
		});
	QObject::connect(slider, &QSlider::sliderReleased, [&]() {
		int val = slider->value();
		string loc = locatie->itemText(locatie->currentIndex()).toStdString();
		v_slider->setText(QString::fromStdString(to_string(val)));
		load_data(service.filtrare(loc, val));
		});
	QObject::connect(locatie, &QComboBox::currentIndexChanged, [&]() {
		int val = slider->value();
		string loc = locatie->itemText(locatie->currentIndex()).toStdString();
		v_slider->setText(QString::fromStdString(to_string(val)));
		load_data(service.filtrare(loc, val));
	});
}

void GUI::load_data(vector<Cutremur> cutremure)
{
	lista->clear();
	lista->addItem(QString::fromStdString(" Locatie  Data  Intensitate   Adancime"));
	for (auto& o : cutremure)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(o.get_locatie() + " " + o.get_data() + " " + to_string(o.get_intensitate()) +" "+ to_string(o.get_adancime())));
		if (o.get_intensitate() < 3)
			item->setData(Qt::BackgroundRole, QBrush(Qt::gray));
		else if (o.get_intensitate() < 4)
			item->setData(Qt::BackgroundRole, QBrush(Qt::green));
		else if (o.get_intensitate() < 6)
			item->setData(Qt::BackgroundRole, QBrush(Qt::yellow));
		else if (o.get_intensitate() < 7)
			item->setData(Qt::BackgroundRole, QBrush(Qt::red));
		lista->addItem(item);
	}
}
void GUI::load_locatii()
{
	locatie->clear();
	locatie->addItem("None");
	for(auto&l:service.get_locatii())
	{
		locatie->addItem(QString::fromStdString(l));
	}
}
