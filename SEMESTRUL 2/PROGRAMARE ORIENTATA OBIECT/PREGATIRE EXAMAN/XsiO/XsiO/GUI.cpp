#include "GUI.h"

void GUI::init_gui()
{
	QHBoxLayout* main=new QHBoxLayout;
	setLayout(main);
	main->addWidget(tbl);
	main->addWidget(tbl_tabela);
	QWidget* form = new QWidget;
	QFormLayout* lform = new QFormLayout;
	form->setLayout(lform);
	lform->addRow("id:", edit_id);
	lform->addRow("dimeniune:", edit_dimensiune);
	lform->addRow("joc:", edit_joc);
	lform->addRow("jucator:", edit_jucator);
	lform->addRow("stare:", edit_stare);
	lform->addWidget(btn_adauga);
	lform->addWidget(btn_modifica);
	main->addWidget(form);
}

void GUI::conectare()
{
	QObject::connect(btn_adauga, &QPushButton::clicked, this, [&]() {
		int id = edit_id->text().toInt();
		int dim = edit_dimensiune->text().toInt();
		string joc = edit_joc->text().toStdString();
		string jucator = edit_jucator->text().toStdString();
		try {
			service.adauga(id, dim, joc, jucator, "Neterminat");
			load_data();
			QMessageBox::information(this, "info", QString::fromStdString("s-a adaugat"));
		}
		catch (ValException ex) {
			QMessageBox::warning(this, "info", QString::fromStdString(ex.get_mesaj()));
		}
		});
	QObject::connect(btn_modifica, &QPushButton::clicked, this, [&]() {
		if (!tbl->selectionModel()->selectedIndexes().isEmpty()) {
			auto row = tbl->selectionModel()->selectedIndexes().at(0).row();
			int id = tbl->model()->data(tbl->model()->index(row, 0), Qt::DisplayRole).toInt();
			int dim = edit_dimensiune->text().toInt();
			string joc = edit_joc->text().toStdString();
			string jucator = edit_jucator->text().toStdString();
			string stare = edit_stare->text().toStdString();
			try {
				service.modifica(id, dim, joc, jucator, stare);
				load_data();
				QMessageBox::information(this, "info", QString::fromStdString("s-a modificat"));
			}
			catch (ValException ex) {
				QMessageBox::warning(this, "info", QString::fromStdString(ex.get_mesaj()));
			}
		}
		});
	QObject::connect(tbl->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (!tbl->selectionModel()->selectedIndexes().isEmpty()) {
			auto row = tbl->selectionModel()->selectedIndexes().at(0).row();
			int dim = tbl->model()->data(tbl->model()->index(row, 1), Qt::DisplayRole).toInt();
			int id= tbl->model()->data(tbl->model()->index(row, 0), Qt::DisplayRole).toInt();
			string joc= tbl->model()->data(tbl->model()->index(row, 2), Qt::DisplayRole).toString().toStdString();
			string jucator= tbl->model()->data(tbl->model()->index(row, 3), Qt::DisplayRole).toString().toStdString();
			tabela->set(joc, dim,jucator,id);
		}
		});
}

void GUI::load_data()
{
	model->set(service);
}
