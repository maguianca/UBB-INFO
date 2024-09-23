#include "gui.h"

void GUI::load_data(vector<Melodie> m)
{
	tabel->clearContents();
	tabel->setRowCount(m.size());
	for (int i = 0; i < m.size(); i++)
	{
		tabel->setItem(i, 0, new QTableWidgetItem(QString::number(m[i].get_id())));
		tabel->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(m[i].get_titlu())));
		tabel->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(m[i].get_artist())));
		tabel->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(m[i].get_gen())));
	}
}

void GUI::init_gui()
{
	painter = new Painter{ service };
	painter->setLayout(l_painter);
	QVBoxLayout* main = new QVBoxLayout;
	setLayout(main);
	tabel = new QTableWidget{ 10,4 };
	tabel->setHorizontalHeaderLabels({ "id","titlu","artist","gen" });
	main->addWidget(tabel);
	main->addWidget(tbl);
	QWidget* form = new QWidget;
	QFormLayout* lform = new QFormLayout;
	form->setLayout(lform);
	lform->addRow("titlu:", edit_titlu);
	lform->addRow("artist:", edit_artist);
	lform->addRow("gen:", edit_gen);
	lform->addRow(btn_adauga);
	lform->addRow(btn_sterge);
	main->addWidget(form);
}

void GUI::connectare()
{
	QObject::connect(btn_adauga, &QPushButton::clicked, this, [&]() {
		string titlu = edit_titlu->text().toStdString();
		string artist = edit_artist->text().toStdString();
		string gen = edit_gen->text().toStdString();
		service.adauga(titlu, artist, gen);
		load_data(service.sorteaza());
		load_tabela();
		});
	QObject::connect(btn_sterge, &QPushButton::clicked, this, [&]() {
		if (!tbl->selectionModel()->selectedIndexes().isEmpty())
		{
			auto row = tbl->selectionModel()->selectedIndexes()[0].row();
			int id = tbl->model()->data(tbl->model()->index(row, 0), Qt::DisplayRole).toInt();
			service.sterge(id);
			load_data(service.sorteaza());
			load_tabela();
		}
		});
}

void GUI::load_tabela()
{
	tabela->set(service);
	this->repaint();
}
void GUI::paintEvent(QPaintEvent* ev) {

	QPainter p{ this };
	p.setPen(Qt::red);
	int pop = 0, rock = 0, folk = 0, disco = 0;
	for (auto& m : service.get_all())
	{
		if (m.get_gen() == "pop") {
			pop++;
			p.drawEllipse(QPoint(10, 10), pop * 8, pop * 8);
		}
		if (m.get_gen() == "folk") {
			folk++;
			p.drawEllipse(QPoint(p.device()->width() - 10, 10), folk * 8, folk * 8);
		}
		if (m.get_gen() == "disco") {
			disco++;
			p.drawEllipse(QPoint(10, p.device()->height() - 10), disco * 8, disco * 8);
		}
		if (m.get_gen() == "rock") {
			rock++;
			p.drawEllipse(QPoint(p.device()->width() - 10, p.device()->height() - 10), rock * 8, rock * 8);
		}
	}
}
void Painter::paintEvent(QPaintEvent* ex)
{
}
