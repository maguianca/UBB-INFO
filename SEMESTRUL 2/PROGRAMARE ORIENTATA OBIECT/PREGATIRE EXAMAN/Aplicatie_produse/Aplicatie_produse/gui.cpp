#include"gui.h"

void GUI::load_data()
{
	model->set(service);
}

void GUI::conectare()
{
	QObject::connect(btn_adauga, &QPushButton::clicked, [&]() {
		try {
			int id = edit_id->text().toInt();
			string nume = edit_nume->text().toStdString();
			string tip = edit_tip->text().toStdString();
			double pret = edit_pret->text().toDouble();
			edit_id->clear();
			edit_nume->clear();
			edit_tip->clear();
			edit_pret->clear();
			service.adauga(id, nume, tip, pret);
			load_data();
			QMessageBox::information(this, "info", QString::fromStdString("adaugat cu succes"));
		}
		catch (ValException& val)
		{
			QMessageBox::warning(this, "info", QString::fromStdString("nu s-a putut adauga: " + val.get_mesaj()));
		}});
	QObject::connect(slider, &QSlider::sliderReleased, [&]() {
		label->setText(QString::number(slider->value()));
		model->setValue(slider->value());
		});
}

void GUI::init_gui()
{
	QHBoxLayout* main=new QHBoxLayout;
	setLayout(main);
	QHBoxLayout* lleft = new QHBoxLayout;
	QWidget* left = new QWidget;
	main->addWidget(left);
	left->setLayout(lleft);
	lleft->addWidget(table);
	QWidget* form = new QWidget;
	QFormLayout* lform = new QFormLayout;
	form->setLayout(lform);
	lform->addRow("id", edit_id);
	lform->addRow("nume", edit_nume);
	lform->addRow("tip", edit_tip);
	lform->addRow("pret", edit_pret);
	lform->addWidget(btn_adauga);
	lform->addWidget(slider);
	slider->setRange(1, 100);
	lform->addWidget(label);
	lleft->addWidget(form);
	map<string, int>tipuri = service.ret_tip();
	for (auto const& t : tipuri) {
		Fereastra* f = new Fereastra(service,t.first, t.second);
		ferestre.push_back(f);
		f->show();
	}
}
