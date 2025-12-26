#pragma once
#include"service.h"
#include"domeniu.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QMessageBox>
class GUI :public QWidget {
private:
	Service& service;
	QListWidget* lista = new QListWidget;
	QWidget* fereastra;
	QLabel* lbl_loc = new QLabel{ "localitate:" };
	QLabel* lbl_data = new QLabel{ "data:" };
	QLabel* lbl_intensitate = new QLabel{ "intensitate:" };
	QLabel* lbl_adancime = new QLabel{ "adancime:" };
	QLineEdit* edit_loc = new QLineEdit;
	QLineEdit* edit_data = new QLineEdit;
	QLineEdit* edit_intensitate = new QLineEdit;
	QLineEdit* edit_adancime = new QLineEdit;
	QPushButton* btn_adauga = new QPushButton{ "Adauga" };
	QComboBox* locatie = new QComboBox;
	QSlider* slider = new QSlider(Qt::Horizontal);
	QLabel* v_slider = new QLabel;
	void init_gui();
	void conectare();
	void load_data(vector<Cutremur>cutremure);
	void load_locatii();
public:
	GUI(Service& service) :service{ service } {
		init_gui();
		load_data(service.get_all());
		conectare();
		load_locatii();
	}
};