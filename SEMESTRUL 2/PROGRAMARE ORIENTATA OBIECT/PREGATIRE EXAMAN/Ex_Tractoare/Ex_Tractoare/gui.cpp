#include "gui.h"
#include<Qpainter>
void GUI::init_gui()
{
	QVBoxLayout* main = new QVBoxLayout;
	setLayout(main);
	main->addWidget(table);
	QWidget* form = new QWidget;
	QFormLayout* lform = new QFormLayout;
	form->setLayout(lform);
	lform->addRow("id:", edit_id);
	lform->addRow("denumire:", edit_denumire);
	lform->addRow("tip:", edit_tip);
	lform->addRow("numarRoti:", edit_numar);
	lform->addWidget(btn_adauga);
	main->addWidget(combo);
	main->addWidget(form);
	painter = new Painter{ service };
	painter->setLayout(lpaint);
}

void GUI::conect()
{
	QObject::connect(btn_adauga, &QPushButton::clicked, this, [&]() {
		int id = edit_id->text().toInt();
		string denumire = edit_denumire->text().toStdString();
		string tip = edit_tip->text().toStdString();
		int numar = edit_numar->text().toInt();
		try {
			service.adauga(id, denumire, tip, numar);
			load_data();
			QMessageBox::information(this, "info", QString::fromStdString("tractor adaugat cu succes!"));
		}
		catch (ValException& ex)
		{
			QMessageBox::warning(this, "info", QString::fromStdString(ex.get_mesaj()));
		}
		});
	QObject::connect(combo, &QComboBox::currentIndexChanged, this, [&]() {
		string nume = combo->currentText().toStdString();
		model->setN(nume);
		load_data();
		});
	QObject::connect(table->selectionModel(), &QItemSelectionModel::currentChanged, this, [&] {
		if (!table->selectionModel()->selectedIndexes().isEmpty())
		{
			repaint();
		}
		});
}

void GUI::load_data()
{
	model->set(service);
	combo->blockSignals(true); 
	combo->clear(); 
	combo->addItem("None");
	combo->setCurrentIndex(0);
	repaint();
	std::map<std::string, int> rez = service.tipuri();
	for (const auto& l : rez) {
		combo->addItem(QString::fromStdString(l.first));
	}
	combo->blockSignals(false); 
}

void GUI::paintEvent(QPaintEvent* ev) 
{
	if (!table->selectionModel()->selectedIndexes().isEmpty()) {
		QPainter p(this);
		p.setPen(Qt::darkMagenta);
		auto row = table->selectionModel()->selectedIndexes()[0].row();
		int roti = table->model()->data(table->model()->index(row, 3), Qt::DisplayRole).toInt();
		for (int i = 0; i < roti; i++)
		{
			p.drawEllipse(QPoint(50, p.device()->height() - 10), (i * 5 + 10) * 2, (i * 5 + 10) * 2);
			nr = roti;
			centru = QPoint(50, p.device()->height() - 10);
		}
	}

}

void GUI::mousePressEvent(QMouseEvent* event) 
{
	QPoint click = event->pos();
	int raza = (nr * 5 + 10) * 2;
	if (QPoint(centru - click).manhattanLength() <= raza) {
		if (nr > 2) {
			if (!table->selectionModel()->selectedIndexes().isEmpty()) {
				auto row = table->selectionModel()->selectedIndexes()[0].row();
				int roti = table->model()->data(table->model()->index(row, 3), Qt::DisplayRole).toInt();
				int id= table->model()->data(table->model()->index(row, 0), Qt::DisplayRole).toInt();
				string denumire= table->model()->data(table->model()->index(row, 1), Qt::DisplayRole).toString().toStdString();
				string tip= table->model()->data(table->model()->index(row, 2), Qt::DisplayRole).toString().toStdString();
				service.modifica(id, denumire, tip, roti-2);
				nr = nr - 2;
				load_data();

			}
		}
	}

}

void Painter::paintEvent(QPaintEvent* ex) const
{
}
