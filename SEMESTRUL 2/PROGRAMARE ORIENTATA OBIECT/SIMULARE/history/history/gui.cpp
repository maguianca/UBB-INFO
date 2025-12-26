#include "gui.h"
#include<QHBoxLayout>
#include<QMessageBox>
void GUI::init_gui()
{
	QHBoxLayout* main = new QHBoxLayout;
	setLayout(main);
	main->addWidget(lista);
	main->addWidget(btn_sterge);
	main->addWidget(btn_filtrare);
	main->addWidget(edit_1);
	main->addWidget(edit_2);
}

void GUI::load_data(vector<Razboi> r)
{
	lista->clear();
	for (auto& l : r) {
		QListWidgetItem* it = new QListWidgetItem(QString::fromStdString("(" + l.get_nume() + "(" + l.get_start() + "," + l.get_end() + ")"));
		lista->addItem(it);
		it->setData(Qt::UserRole, QString::number(l.get_id()));
		QFont f;
		if (l.get_id() > 0 && l.get_id() < 10)
			f.setPointSize(12);
		else 
			if(l.get_id()>10&& l.get_id()<15)
				f.setPointSize(16);
			else 
				f.setPointSize(20);
		it->setData(Qt::FontRole, f);
	}
}

void GUI::connect()
{
	QObject::connect(btn_sterge, &QPushButton::clicked, this, [&]() {
		if (!lista->selectedItems().isEmpty())
		{
			QMessageBox msg;
			msg.setText("este sigur ca vrei sa stergi?");
			QPushButton* btnDa = msg.addButton(QString::fromStdString("DA"), QMessageBox::ActionRole);
			QPushButton* btnCancel = msg.addButton(QMessageBox::Cancel);
			/*msg.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
			int ret = msg.exec();
			switch (ret) {
			case QMessageBox::Save:
			{
				int id = lista->selectedItems()[0]->data(Qt::UserRole).toInt();
				service.sterge(id);
				load_data(service.get_all());
				break;
			}
			case QMessageBox::Cancel:
				break;
			default:
				break;
			}*/
			int ret = msg.exec(); 

			if (msg.clickedButton() == btnDa)
			{
				int id = lista->selectedItems()[0]->data(Qt::UserRole).toInt();
				service.sterge(id);
				load_data(service.get_all());
			}
		}
		});
	QObject::connect(btn_filtrare, &QPushButton::clicked, this, [&]() {
		
		string data1 = edit_1->text().toStdString();
		string data2 = edit_2->text().toStdString();
		qDebug() << data1 << " " << data2 << " ";
		});
}
