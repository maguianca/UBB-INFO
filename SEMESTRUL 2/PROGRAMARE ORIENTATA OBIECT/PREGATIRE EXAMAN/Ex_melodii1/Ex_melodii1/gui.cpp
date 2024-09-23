#include "gui.h"

void GUI::init_gui()
{
	painter = new Painter{ service };
	painter->setLayout(lpaint);
	QHBoxLayout* main = new QHBoxLayout;
	QWidget* left = new QWidget ;
	QWidget* right = new QWidget ;
	QVBoxLayout* lleft = new QVBoxLayout;
	QVBoxLayout* lright = new QVBoxLayout;
	left->setLayout(lleft);
	right->setLayout(lright);
	setLayout(main);
	lleft->addWidget(table);
	QWidget* form = new QWidget;
	QFormLayout* lform = new QFormLayout;
	form->setLayout(lform);
	lform->addRow("titlu", edit_titlu);
	slider->setRange(0, 10);
	lform->addWidget(slider);
	lform->addWidget(lbl);
	lform->addWidget(btn_modifica);
	lform->addWidget(btn_sterge);
	lform->addWidget(btn_undo);
	lright->addWidget(form);
	lright->addWidget(painter);
	main->addWidget(left);
	main->addWidget(right);


}

void GUI::load_data()
{
	model->set(service);
	this->repaint();
}
void showWarning()
{
	QMessageBox msgBox;
	msgBox.setWindowTitle("Info");
	msgBox.setText("Nu se poate sterge e ultima melodie.");
	QPushButton* saveButton = msgBox.addButton(QMessageBox::Save);
	QPushButton* discardButton = msgBox.addButton(QMessageBox::Discard);
	msgBox.setDefaultButton(saveButton);

	int ret = msgBox.exec();

	if (ret == QMessageBox::Save) {
		// Save action
		// TODO: Implement the save logic here
		qDebug() << "Save button clicked";
	}
	else if (ret == QMessageBox::Discard) {
		// Discard action
		// TODO: Implement the discard logic here
		qDebug() << "Discard button clicked";
	}
}
void GUI::conect()
{
	QObject::connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, this, [&]() {
		if (!table->selectionModel()->selectedIndexes().isEmpty()) {
			auto row = table->selectionModel()->selectedIndexes()[0].row();
			int id = table->model()->data(table->model()->index(row, 0), Qt::DisplayRole).toInt();
			auto titlu = table->model()->data(table->model()->index(row, 1), Qt::DisplayRole).toString();
			edit_titlu->setText(titlu);
		}});
	QObject::connect(slider,&QSlider::valueChanged,this,[&]{
		int value = slider->value();
		lbl->setText(QString::number(value));
		});
	QObject::connect(btn_modifica, &QPushButton::clicked, this, [&]() {
		if (!table->selectionModel()->selectedIndexes().isEmpty()) {
			auto row = table->selectionModel()->selectedIndexes()[0].row();
			int id = table->model()->data(table->model()->index(row, 0), Qt::DisplayRole).toInt();
			string titlu = edit_titlu->text().toStdString();
			string artist = table->model()->data(table->model()->index(row, 2), Qt::DisplayRole).toString().toStdString();
			int rank = slider->value();
			try {
				service.modifica(id, titlu, artist, rank);
				load_data();
				qDebug() << "modificat cu succes";
			}
			catch (ValException)
			{
				qDebug() << "nu se poate modifica";
			}
		}
		});
	QObject::connect(btn_sterge, &QPushButton::clicked, this, [&]() {
		if (!table->selectionModel()->selectedIndexes().isEmpty()) {
			auto row = table->selectionModel()->selectedIndexes()[0].row();
			int id = table->model()->data(table->model()->index(row, 0), Qt::DisplayRole).toInt();
			string artist = table->model()->data(table->model()->index(row, 2), Qt::DisplayRole).toString().toStdString();
			int valoare = service.artist(artist);
			if (valoare > 1) {
				try {
					service.sterge(id);
					load_data();
					qDebug() << "modificat cu succes";
				}
				catch (ValException)
				{
					qDebug() << "nu se poate modifica";
				}
			}
			else {
				//showWarning();
				QMessageBox::warning(this, "info", QString::fromStdString("nu se poate sterge e ultima melodie"));
			}
		}
		});
	QObject::connect(btn_undo, &QPushButton::clicked, this, [&]() {
		try {
			service.undo();
			load_data();
		}
		catch (exception&ex) {
			QMessageBox::warning(this, "info", QString::fromStdString("nu se poate face undo"), QMessageBox::Save | QMessageBox::Discard);
		}
		});
}

void GUI::paintEvent(QPaintEvent* ev)
{
}

void Painter::paintEvent(QPaintEvent* ev)
{
	QPainter p{ this };
	p.setPen(Qt::red);
	for (int i = 0; i <=10; i++) {
		int x = service.rank(i);
		p.drawRect(10 + i * 10, p.device()->height(), 10, -(x + 1) * 10);
		
	}
}
