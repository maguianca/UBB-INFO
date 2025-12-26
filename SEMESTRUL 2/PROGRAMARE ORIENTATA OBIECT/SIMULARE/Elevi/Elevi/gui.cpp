#include "gui.h"

void GUI::init_gui()
{
	QHBoxLayout* main = new QHBoxLayout;
	setLayout(main);
	QWidget* left = new QWidget;
	QWidget* right = new QWidget;
	QVBoxLayout* lright = new QVBoxLayout;
	QVBoxLayout* lleft = new QVBoxLayout;
	left->setLayout(lleft);
	right->setLayout(lright);
	main->addWidget(left);
	main->addWidget(right);
	lleft->addWidget(lista);
	lleft->addWidget(btn_restart);
	QLabel* lbl_detalii = new QLabel{ "Detalii" };
	lright->addWidget(lbl_detalii);
	lright->addWidget(detalii);
	lright->addWidget(btn_sortare_clasa);
	lright->addWidget(btn_sortare_medie);
	lright->addWidget(btn_sortare_nume);
	lright->addWidget(btn_sterge);

}

void GUI::conectare()
{
	QObject::connect(btn_restart, &QPushButton::clicked, [&]() {
		load_data(service.get_all());
		detalii->clear();
		});
	QObject::connect(btn_sortare_clasa, &QPushButton::clicked, [&]() {
		load_data(service.sortare_clasa());
		detalii->clear();
		});
	QObject::connect(btn_sortare_medie, &QPushButton::clicked, [&]() {
		load_data(service.sortare_medie());
		detalii->clear();
		});
	QObject::connect(btn_sortare_nume, &QPushButton::clicked, [&]() {
		load_data(service.sortare_nume());
		detalii->clear();
		});
	QObject::connect(lista, &QListWidget::itemClicked, [&]() {
		detalii->setText(lista->selectedItems()[0]->data(Qt::UserRole).toString());
		});
	QObject::connect(btn_sterge, &QPushButton::clicked, [&]() {
		if (lista->selectedItems().isEmpty())
			QMessageBox::warning(NULL, "info", "Nu se poate sterge nu est nimic selectat");
		else {
			string data = lista->selectedItems()[0]->data(Qt::UserRole).toString().toStdString();
			elev& x = service.cauta(data);
			service.stergere(x.get_matricol());
			load_data(service.get_all());
		}
		});
}

void GUI::load_data(vector<elev> elevi)
{
	lista->clear();
	lista->addItem(QString::fromStdString("Nr matricol   Nume   Prenume  "));
	for (auto& l : elevi) {
		/*auto widget = new QWidget;
		auto lay = new QHBoxLayout;
		auto buton = new QPushButton{ "delete" };
		widget->setLayout(lay);
		lay->setAlignment(Qt::AlignRight);
		lay->addWidget(buton);
		QObject::connect(buton, &QPushButton::clicked, [=]() {
			service.stergere(l.get_matricol());
			load_data(service.get_all());
			});
			*/
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(to_string(l.get_matricol()) + "  " + l.get_nume() + "  " + l.get_prenume()));
		if (l.get_medie() < 5)
			item->setData(Qt::BackgroundRole, QBrush(Qt::red));
		else if (l.get_medie() <= 8.5)
			item->setData(Qt::BackgroundRole, QBrush(Qt::yellow));
		else
			item->setData(Qt::BackgroundRole, QBrush(Qt::green));
		item->setData(Qt::UserRole, QString::fromStdString(to_string(l.get_matricol()) + "  " + l.get_nume() + "  " + l.get_prenume()));
		/*item->setSizeHint(buton->sizeHint() * 2);
		string info = to_string(l.get_matricol()) + "  " + l.get_nume() + "  " + l.get_prenume() + "  " + to_string(l.get_clasa()) + "  " + to_string(l.get_medie());
		item->setData(Qt::UserRole, QString::fromStdString(info));
		//buton->setMaximumSize(item->sizeHint() / 2);*/
		lista->addItem(item);
		//lista->setItemWidget(item, widget);
	}
}
