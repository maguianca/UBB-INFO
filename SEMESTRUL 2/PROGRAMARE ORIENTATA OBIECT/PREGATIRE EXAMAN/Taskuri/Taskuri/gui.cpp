#include "gui.h"

void GUI::load_table(vector<Task>all)
{
	table->clearContents();
	table->setRowCount(all.size());
	for (int i = 0; i < all.size(); i++)
	{
		const Task& t = all[i];
		table->setItem(i, 0, new QTableWidgetItem(QString::number(t.get_id())));
		table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(t.get_descriere())));
		table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(t.get_programatori_string())));
		table->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(t.get_stare())));
	}
}

void GUI::init_gui()
{
	QHBoxLayout* main=new QHBoxLayout;
	setLayout(main);
	table = new QTableWidget{ 10,4 };
	table->setHorizontalHeaderLabels({ "id","descriere","programatori","stare" });
	QWidget* form = new QWidget;
	QFormLayout* lform = new QFormLayout;
	form->setLayout(lform);
	lform->addRow("id:", edit_id);
	lform->addRow("descriere:", edit_descriere);
	lform->addRow("programator:", edit_programator);
	lform->addRow("stare:", edit_stare);
	lform->addRow("Filtrare:", edit_filtrare);
	lform->addWidget(btn_add);
	lform->addWidget(btn_reset);
	main->addWidget(table);
	main->addWidget(form);
	Fereastra* f1 = new Fereastra(service,"close");
	Fereastra* f2 = new Fereastra(service,"open");
	Fereastra* f3 = new Fereastra(service,"inprogress");
	f1->show();
	f2->show();
	f3->show();
	//ferestre.push_back(f1);
	//ferestre.push_back(f3);
	//ferestre.push_back(f2);
}

void GUI::connect()
{
	QObject::connect(edit_filtrare, &QLineEdit::textChanged, this, [&]() {
		string filt = edit_filtrare->text().toStdString();
		load_table(service.filtrare(filt));

		});
	QObject::connect(btn_reset, &QPushButton::clicked, this, [&]() {
			load_table(service.sorteaza());
		});
	QObject::connect(btn_add, &QPushButton::clicked, this, [&]() {
		int id = edit_id->text().toInt();
		string denumire = edit_descriere->text().toStdString();
		string programatori = edit_programator->text().toStdString();
		string stare = edit_stare->text().toStdString();
		vector<string>p;
		string curent;
		stringstream linestream(programatori);
		while (getline(linestream, curent, ' ')) {
			p.push_back(curent);
			qDebug() << curent << " ";
		}
		try {
			service.adauga(id, denumire, p, stare);
			QMessageBox::information(this, "info", QString::fromStdString("adaugat cu succes"));
			load_table(service.sorteaza());
		}
		catch (ValException& ex)
		{
			QMessageBox::warning(this, "info", QString::fromStdString(ex.get_mesaj()));
		}
		});
}
