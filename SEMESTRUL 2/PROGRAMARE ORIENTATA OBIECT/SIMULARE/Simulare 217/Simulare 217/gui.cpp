#include "gui.h"

void Gui::connect()
{
	QObject::connect(btn_restart, &QPushButton::clicked, [&]() {
		load_data(service.get_all());
		edit->clear();
		});
	QObject::connect(btn_sort, &QPushButton::clicked, [&]() {
		load_data(service.sortare());
		});
	QObject::connect(lista, &QListWidget::itemClicked, [&]() {
		string dt = lista->currentItem()->text().toStdString();
		edit->setText(QString::fromStdString(dt+"  "+lista->currentItem()->data(Qt::UserRole).toString().toStdString()));
		});
	QObject::connect(btn_informatica, &QPushButton::clicked, [&]() {
		vector<Elev>v;
		for (auto& l : service.get_all()) {
			string curent;
			stringstream linestream(l.get_atelier());
			while (getline(linestream, curent, '|')) {
				if (curent == "informatica")
					v.push_back(l);
			}
		}
		tabel(v);
		});
	QObject::connect(btn_desen, &QPushButton::clicked, [&]() {
		vector<Elev>v;
		for (auto& l : service.get_all()) {
			string curent;
			stringstream linestream(l.get_atelier());
			while (getline(linestream, curent, '|')) {
				if (curent == "desen+pictura")
					v.push_back(l);
			}
		}
		tabel(v);
		});
	QObject::connect(btn_muzica, &QPushButton::clicked, [&]() {
		vector<Elev>v;
		for (auto& l : service.get_all()) {
			string curent;
			stringstream linestream(l.get_atelier());
			while (getline(linestream, curent, '|')) {
				if (curent == "muzica")
					v.push_back(l);
			}
		}
		tabel(v);
		});
	QObject::connect(btn_muzica, &QPushButton::clicked, [&]() {
		vector<Elev>v;
		for (auto& l : service.get_all()) {
			string curent;
			stringstream linestream(l.get_atelier());
			while (getline(linestream, curent, '|')) {
				if (curent == "muzica")
					v.push_back(l);
			}
		}
		tabel(v);
		});
	QObject::connect(btn_fotografie, &QPushButton::clicked, [&]() {
		vector<Elev>v;
		for (auto& l : service.get_all()) {
			string curent;
			stringstream linestream(l.get_atelier());
			while (getline(linestream, curent, '|')) {
				if (curent == "fotografie")
					v.push_back(l);
			}
		}
		tabel(v);
		});
}

void Gui::init_gui()
{
	QHBoxLayout* main = new QHBoxLayout;
	setLayout(main);
	QWidget* right = new QWidget;
	QWidget* left = new QWidget;
	QVBoxLayout* lright = new QVBoxLayout;
	QVBoxLayout* lleft = new QVBoxLayout;
	right->setLayout(lright);
	left->setLayout(lleft);
	main->addWidget(left);
	main->addWidget(right);
	lleft->addWidget(lista);
	int colomns = 3;
	int lines = service.get_all().size();
	table = new QTableWidget{ lines,colomns };
	table->setHorizontalHeaderLabels({ "nrMatricol","Nume","Scoala" });
	lleft->addWidget(table);
	QFormLayout* lform = new QFormLayout;
	QWidget* form = new QWidget;
	form->setLayout(lform);
	lform->addRow(label, edit);
	lright->addWidget(form);
	lright->addWidget(btn_informatica);
	lright->addWidget(btn_desen);
	lright->addWidget(btn_muzica);
	lright->addWidget(btn_fotografie);
	lright->addWidget(btn_jurnalism);
	lright->addWidget(btn_restart);
	lright->addWidget(btn_sort);
}

void Gui::load_data(vector<Elev> elevi)
{
	lista->clear();
	lista->addItem((QString::fromStdString("nrMatricol  Nume  Scoala")));
	for (auto& l : elevi) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(to_string(l.get_matricol()) +"   " +l.get_nume() + "   "+l.get_scoala()));
		lista->addItem(item);
		item->setData(Qt::UserRole, QString::fromStdString(l.get_atelier()));
	}
}

void Gui::tabel(vector<Elev> elevi)
{
	table->clearContents();
	table->setRowCount(elevi.size());
	for (int i = 0; i < elevi.size(); i++)
	{
		table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(to_string(elevi[i].get_matricol()))));
		table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(elevi[i].get_nume())));
		table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(elevi[i].get_scoala())));
	}
}

