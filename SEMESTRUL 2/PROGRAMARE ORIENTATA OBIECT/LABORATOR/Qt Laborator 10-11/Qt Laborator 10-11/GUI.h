#pragma once
#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/QSpacerItem>
#include <QStringList>
#include "service.h"
#include"CosCRUDGUI.h"
#include"CosReadOnlyGui.h"
#include"TableModel.h"
using std::vector;
using std::string;
class GUI : public QWidget {
private:
	Service& service;
	QListWidget* lista_oferte;
	QListWidget* lista_cos;
	QTableView* tbl = new QTableView;

	//QWidget* fereastra;
	QWidget* wishlistWindow;
	QListWidget* lista;

	QLabel* lbl_denumire = new QLabel{ "Denumire:" };
	QLabel* lbl_destinatie = new QLabel{ "Destinatie:" };
	QLabel* lbl_tip = new QLabel{ "Tip:" };
	QLabel* lbl_pret = new QLabel{ "Pret:" };
	QLabel* lbl_tip_nou = new QLabel{ "Tip nou:" };
	QLabel* lbl_pret_nou = new QLabel{ "Pret nou:" };
	QLabel* lbl_filtrare_pret = new QLabel{ "Pretul dupa care se filtreaza:" };
	QLabel* lbl_filtrare_destinatie = new QLabel{ "Destinatia dupa care se filtreaza:" };
	//QLabel* lbl_random = new QLabel{ "Cate oferte doriti sa aveti in wishlist:" };
	//QLabel* lbl_export = new QLabel{ "Numele fisierului export (.csv)/(.html):" };

	QLineEdit* edit_destinatie;
	QLineEdit* edit_denumire;
	QLineEdit* edit_tip;
	QLineEdit* edit_pret;
	QLineEdit* edit_pret_nou;
	QLineEdit* edit_tip_nou;
	QLineEdit* edit_filtrare_pret;
	QLineEdit* edit_filtrare_destinatie;
	/*QLineEdit* edit_export_cos;
	QLineEdit* edit_random_cos;
	
	QLineEdit* destinatie_cos;
	QLineEdit* denumire_cos;
	QLineEdit* tip_cos;
	QLineEdit* pret_cos;*/

	QPushButton* btn_adauga;
	QPushButton* btn_modifica;
	QPushButton* btn_sterge;
	QPushButton* btn_exit;
	QPushButton* btn_sortare;
	QPushButton* btn_filtrare_pret;
	QPushButton* btn_filtrare_destinatie;
	QPushButton* btn_reload_data;
	QPushButton* btn_undo;
	QPushButton* btn_cos;
	/*QPushButton* btn_adauga_cos;
	QPushButton* btn_random_cos;
	QPushButton* btn_export_cos;
	QPushButton* btn_goleste_cos;
	QPushButton* btn_exit_cos;*/
	QPushButton* btn_desenare;
	
	vector<QPushButton*>butoane;
	QHBoxLayout* ly_butoane = new QHBoxLayout;

	QTableWidget* tableOferte;

	QRadioButton* radio_sortare_destinatie=new QRadioButton(QString::fromStdString("Destinatie"));
	QRadioButton* radio_sortare_denumire= new QRadioButton(QString::fromStdString("Denumire"));
	QRadioButton* radio_sortare_tip_pret=new QRadioButton(QString::fromStdString("Tip+Pret"));

	QGroupBox* group_box=new QGroupBox(tr("Tip sortare"));
	void initializare_gui();
	void conectare();
	void load_data(vector<Turism>oferte);
	void load_data_cos(vector<Turism>oferte);
public:
	GUI(Service& service) : service{ service } {
		initializare_gui();
		conectare();
		load_data(service.get_all());

	}
	void gui_adauga();
	void gui_modifica();
	void gui_stergere();
};