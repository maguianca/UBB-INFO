#include "gui.h"

void GUI::load_data(vector<Utilaj> ut)
{
	model->set(service);
	tabel->clearContents();
	tabel->setRowCount(ut.size());
	//qDebug() << ut[0].get_id();
	for (int i = 0; i < ut.size(); i++) {
		tabel->setItem(i, 0, new QTableWidgetItem(QString::number(ut[i].get_id())));
		tabel->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(ut[i].get_denumire())));
		tabel->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(ut[i].get_tip())));
		tabel->setItem(i, 3, new QTableWidgetItem(QString::number(ut[i].get_cilindri())));
	}
	repaint();
}

void GUI::init_gui()
{
	p = new Painter{ service };
	p->setLayout(lay);
	QHBoxLayout* main = new QHBoxLayout;
	setLayout(main);
	QWidget* left = new QWidget;
	QWidget* right = new QWidget;
	QVBoxLayout* lleft = new QVBoxLayout;
	QVBoxLayout* lright = new QVBoxLayout;
	left->setLayout(lleft);
	right->setLayout(lright);
	tabel = new QTableWidget{ 10,4 };
	tabel->setHorizontalHeaderLabels({ "id","denumire","tip","cilindri" });
	lleft->addWidget(tabel);
	lleft->addWidget(table);
	QWidget* form = new QWidget;
	QFormLayout* lform = new QFormLayout;
	form->setLayout(lform);
	lform->addRow("denumire: ",edit_denumire);
	lform->addRow("tip: ",edit_tip);
	lform->addWidget(c1);
	lform->addWidget(c2);
	lform->addWidget(c3);
	lform->addWidget(c4);
	c1->setChecked(false);
	c2->setChecked(false);
	c3->setChecked(false);
	c4->setChecked(false);
	lform->addRow(btn_modifica);
	lright->addWidget(btn_sterge);
	lright->addWidget(form);
	main->addWidget(left);
	main->addWidget(right);
}

void GUI::conectare()
{
	QObject::connect(btn_sterge, &QPushButton::clicked, this, [&]() {
		if (!table->selectionModel()->selectedIndexes().isEmpty()) {
			auto row = table->selectionModel()->selectedIndexes()[0].row();
			int id = table->model()->data(table->model()->index(row, 0), Qt::DisplayRole).toInt();
			int cilindri = table->model()->data(table->model()->index(row, 3), Qt::DisplayRole).toInt();
			int nr = service.nr_cilindri(cilindri);
			if (nr > 1) {
				service.sterge(id);
				repaint();
				load_data(service.sortare());
				QMessageBox::warning(this, "info", QString::fromStdString("elementul s-a sters"));
			}
			else
			{
				QMessageBox::warning(this, "info", QString::fromStdString("nu se poate sterge este doar un obiect cu " + to_string(nr) + " cilindru"));
			}
		}
		});
	QObject::connect(btn_modifica, &QPushButton::clicked, this, [&]() {
		if (!table->selectionModel()->selectedIndexes().isEmpty()) {
			auto row = table->selectionModel()->selectedIndexes()[0].row();
			int id = table->model()->data(table->model()->index(row, 0), Qt::DisplayRole).toInt();
			if (c1->isChecked() || c2->isChecked() || c3->isChecked() || c4->isChecked()) {
				int cilindri;
				if (c1->isChecked())
					cilindri = 1;
				else if (c2->isChecked())
					cilindri = 2;
				else if (c3->isChecked())
					cilindri = 4;
				else if (c4->isChecked())
					cilindri = 8;
				string denumire = edit_denumire->text().toStdString();
				string tip = edit_tip->text().toStdString();
				service.modifica(id, denumire, tip, cilindri);
				load_data(service.sortare());
				repaint();

			}
		}
		else {
			QMessageBox::warning(this, "info", QString::fromStdString("nu ati selectat linie"));
		}
		});
	QObject::connect(table->selectionModel(), &QItemSelectionModel::currentChanged, this, [&]() {
		if (!table->selectionModel()->selectedIndexes().isEmpty()) {
			auto row = table->selectionModel()->selectedIndexes()[0].row()+1;
			int id = table->model()->data(table->model()->index(row, 0), Qt::DisplayRole).toInt();
			auto denumire = table->model()->data(table->model()->index(row, 1), Qt::DisplayRole).toString();
			auto tip = table->model()->data(table->model()->index(row, 2), Qt::DisplayRole).toString();
			edit_denumire->setText(denumire);
			edit_tip->setText(tip);

		}
		});
}

void GUI::paintEvent(QPaintEvent* ev)
{
	int c = 0;
	for (int i = 1; i <= 8; i++)
	{
		QPainter p(this);
		p.setPen(Qt::darkMagenta);
		int nr;
		if (i == 1) {
			nr = service.nr_cilindri(i);
			p.drawEllipse(QPoint(300 + c*3,p.device()->height() - 30), (nr+1)*8, (nr+1)*8);
			c += 20;
		}
		if (i == 2) {
			nr = service.nr_cilindri(i);
			p.drawEllipse(QPoint(300 + c*3, p.device()->height() - 30), (nr+1)*8, (nr+1)*8);
			c += 20;
		}
		if (i == 4) {
			nr = service.nr_cilindri(i);
			p.drawEllipse(QPoint(300 + c*3, p.device()->height() - 30), (nr + 1) * 8, (nr + 1) * 8);
			c += 20;
		}
		if (i == 8) {
			nr = service.nr_cilindri(i);
			p.drawEllipse(QPoint(300 + c*3, p.device()->height() - 30), (nr + 1) * 8, (nr + 1) * 8);
			c += 20;
		}
	}
}

void Painter::paintEvent(QPaintEvent* ev)
{
}
