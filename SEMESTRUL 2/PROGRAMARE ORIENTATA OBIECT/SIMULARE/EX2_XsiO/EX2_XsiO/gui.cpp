#include "GUI.h"

void GUI::init_gui()
{
	QHBoxLayout* main = new QHBoxLayout;
	setLayout(main);
	main->addWidget(tbl);
	//main->addWidget(tbl_tabela);
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
			int id = tbl->model()->data(tbl->model()->index(row, 0), Qt::DisplayRole).toInt();
			string joc = tbl->model()->data(tbl->model()->index(row, 2), Qt::DisplayRole).toString().toStdString();
			string jucator = tbl->model()->data(tbl->model()->index(row, 3), Qt::DisplayRole).toString().toStdString();
			qDebug() << joc << dim << id;
			if (tw != nullptr)
				tw->deleteLater();
			tw = new TablaWindow(joc, jucator, id, this->service);
			tw->show();
		}
		});


	/*
	QObject::connect(tbl->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (!tbl->selectionModel()->selectedIndexes().isEmpty()) {
			auto row = tbl->selectionModel()->selectedIndexes().at(0).row();
			int dim = tbl->model()->data(tbl->model()->index(row, 1), Qt::DisplayRole).toInt();
			int id = tbl->model()->data(tbl->model()->index(row, 0), Qt::DisplayRole).toInt();
			string joc = tbl->model()->data(tbl->model()->index(row, 2), Qt::DisplayRole).toString().toStdString();
			string jucator = tbl->model()->data(tbl->model()->index(row, 3), Qt::DisplayRole).toString().toStdString();
			//tbl->set(joc, dim, jucator, id);
		}
		});*/
}

void GUI::load_data()
{
	model->set(service);
}
void TablaWindow::generateGUI() {
	int dim = sqrt(tabla.length());
	auto vLy = new QVBoxLayout;
	this->setLayout(vLy);
	int currentIndex = 0;
	for (int i = 0; i < dim; i++)
	{
		auto hLy = new QHBoxLayout;
		vLy->addLayout(hLy);
		for (int j = 0; j < dim; j++)
		{
			QPushButton* qpb = new QPushButton{ QString::fromStdString(std::string(1, tabla[currentIndex])) };
			qpb->setProperty("Nr", QVariant(currentIndex));
			hLy->addWidget(qpb);
			connect(qpb, &QPushButton::clicked, this, &TablaWindow::tableButtons);
			currentIndex++;
		}
	}

}

void TablaWindow::tableButtons() {
	int indexToModify = sender()->property("Nr").toInt();
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	if (button->text() == "-") {
		tabla[indexToModify] = jucator[0];
		button->setText(QString::fromStdString(jucator));
		if (jucator == "X")
			jucator = "O";
		else
			jucator = "X";

		srv.notify(id, tabla, jucator, (emptyAndCompletedCells().first == 0 ? "Terminat" : "In derulare"));
	}
}
void GUI::connectSelectCell() {
	QObject::connect(tbl->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (!tbl->selectionModel()->selectedIndexes().isEmpty()) {
			auto row = tbl->selectionModel()->selectedIndexes().at(0).row();
			int dim = tbl->model()->data(tbl->model()->index(row, 1), Qt::DisplayRole).toInt();
			int id = tbl->model()->data(tbl->model()->index(row, 0), Qt::DisplayRole).toInt();
			string joc = tbl->model()->data(tbl->model()->index(row, 2), Qt::DisplayRole).toString().toStdString();
			string jucator = tbl->model()->data(tbl->model()->index(row, 3), Qt::DisplayRole).toString().toStdString();
			qDebug() << joc << dim<< id;
			if (tw != nullptr)
				tw->deleteLater();
			tw = new TablaWindow(joc, jucator, id, this->service);
			tw->show();
		}
		});
	/*
	QObject::connect(tbl, &QTableView::clicked, [this](const QModelIndex& index) {
		auto indexx = model->index(index.row(), 2);
		auto indexxx = model->index(index.row(), 0);
		auto indexxxx = model->index(index.row(), 3);
		qDebug() << indexx << indexxx << indexxxx;
		string s = indexx.data(Qt::DisplayRole).toString().toStdString();
		int id = indexxx.data(Qt::DisplayRole).toInt();
		string jucator = indexxxx.data(Qt::DisplayRole).toString().toStdString();
		if (tw != nullptr)
			tw->deleteLater();
		tw = new TablaWindow(s, jucator, id, this->service);
		tw->show();
		});*/

}
std::pair<int, int> TablaWindow::emptyAndCompletedCells() {
	std::pair<int, int> rez;
	for (auto ch : tabla) {
		if (ch == '-')
			rez.first++;
		else
			rez.second++;
	}
	return rez;
}
