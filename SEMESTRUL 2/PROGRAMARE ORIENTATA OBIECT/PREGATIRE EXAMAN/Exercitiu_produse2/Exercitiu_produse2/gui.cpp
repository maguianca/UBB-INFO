#include "gui.h"

void GUI::init_gui()
{
	QHBoxLayout* main = new QHBoxLayout;
	setLayout(main);
	main->addWidget(tabel);
	QWidget* form = new QWidget;
	QFormLayout* lform = new QFormLayout;
	form->setLayout(lform);
	lform ->addRow("id:", edit_id);
	lform ->addRow("nume:", edit_nume);
	lform ->addRow("tip:", edit_tip);
	lform ->addRow("pret:", edit_pret);
	lform ->addWidget(btn_adauga);
	slider->setRange(0, 100);
	slider->setValue(0);
	lform ->addWidget(slider);
	lform ->addWidget(lbl);
	main->addWidget(form);
	map<string, int>rez = service.tipuri();
	for (const auto l : rez) {
		Fereastra* fe= new Fereastra{ service,l.first,l.second };
		f.push_back(fe);
		fe->show();
	}
}

void GUI::load_data()
{
	model->set(service);
}

void GUI::connect()
{
	QObject::connect(btn_adauga, &QPushButton::clicked, this, [&]() {
		int id = edit_id->text().toInt();
		string nume = edit_nume->text().toStdString();
		string tip = edit_tip->text().toStdString();
		double pret = edit_pret->text().toDouble();
		try {
			service.adaugare(id, nume, tip, pret);
			load_data();
			QMessageBox::information(this, "info", QString::fromStdString("adaugat cu succes"));
		}
		catch (ValException& ex) {
			QMessageBox::warning(this, "info", QString::fromStdString(ex.get_mesaj()));
		}
		});
	QObject::connect(slider, &QSlider::valueChanged, this, [&]() {
		int value = slider->value();
		lbl->setText(QString::number(value));
		model->setVal(value);
		load_data();
		});
}
