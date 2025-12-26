#include "gui.h"

void GUI::conect()
{
	QObject::connect(btn_modifica, &QPushButton::clicked, this, [&]() {
		if (edit_job->text().isEmpty())return;
		if (edit_nume->text().isEmpty())return;
		service.modificare(edit_nume->text().toStdString(), edit_job->text().toStdString(), status->itemText(status->currentIndex()).toStdString(), lista->selectedItems()[0]->data(Qt::UserRole).toString().toInt());
		load_data(service.get_all());
		});
	QObject::connect(btn_refresh, &QPushButton::clicked, this, [&]() {
		load_data(service.get_all());
		edit_filtreaza->clear();
		});
	QObject::connect(edit_filtreaza, &QLineEdit::textChanged, [&]() {
		string text = edit_filtreaza->text().toStdString();
		load_data(service.filtrare(text));
		});
	QObject::connect(lista, &QListWidget::itemSelectionChanged, this, [&]() {
		if (lista->selectedItems().isEmpty())return;
		Persoana p = service.cauta(lista->selectedItems()[0]->data(Qt::UserRole).toString().toInt());
		edit_nume->setText(QString::fromStdString(p.get_nume()));
		edit_job->setText(QString::fromStdString(p.get_job()));
		if (p.get_status() == "hired")
		{
			status->setCurrentIndex(0);
		}
		if (p.get_status() == "pending")
		{
			status->setCurrentIndex(1);
		}
		if (p.get_status() == "rejected")
		{
			status->setCurrentIndex(2);
		}
		});
}


void GUI::init_gui()
{
	QHBoxLayout* main = new QHBoxLayout;
	this->setLayout(main);
	QWidget* right = new QWidget;
	QWidget* left = new QWidget;
	QVBoxLayout* l_right = new QVBoxLayout;
	QVBoxLayout* l_left = new QVBoxLayout;
	right->setLayout(l_right);
	left->setLayout(l_left);
	main->addWidget(left);
	main->addWidget(right);
	l_left->addWidget(lista);
	QFormLayout* l_form = new QFormLayout;
	QWidget* form = new QWidget;
	form->setLayout(l_form);
	l_right->addWidget(form);
	l_form->addRow("Nume", edit_nume);
	l_form->addRow("Job", edit_job);
	l_form->addWidget(status);
	status->addItem("hired");
	status->addItem("pending");
	status->addItem("rejected");
	l_form->addWidget(btn_modifica);
	l_form->addWidget(btn_refresh);
	l_form->addRow(lbl_filtreaza, edit_filtreaza);;

}

void GUI::load_data(vector<Persoana>persoane)
{
	lista->clear();
	lista->addItem(QString::fromStdString("Nume   Job   Status"));
	for (auto& l : persoane)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(l.get_nume() + " " + l.get_job() + " " + l.get_status()));
		item->setData(Qt::UserRole, QString::fromStdString(to_string(l.get_id())));
		if (l.get_status() == "hired")
		{
			item->setData(Qt::BackgroundRole, QBrush(Qt::green));
		}
		if (l.get_status() == "pending")
		{
			item->setData(Qt::BackgroundRole, QBrush(Qt::yellow));
		}
		if (l.get_status() == "rejected")
		{
			item->setData(Qt::BackgroundRole, QBrush(Qt::red));
		}
		lista->addItem(item);
	}
}
