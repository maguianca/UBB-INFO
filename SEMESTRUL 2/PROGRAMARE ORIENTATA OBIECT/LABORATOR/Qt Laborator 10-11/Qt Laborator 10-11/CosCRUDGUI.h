#pragma once
#include<QHBoxLayout>
#include<QWidget>
#include<QPushButton>
#include<QListWidget>
#include<QTableWidget>
#include<QLabel>
#include<QFormLayout>
#include<QLineEdit>
#include<vector>
#include<QMessageBox>
#include"CosOferte.h"
#include"observer.h"
class CosLista :public QWidget, public Observer {
private:
	CosOferte& cos;
	QWidget* fereastra;
	QListWidget* lista_cos;
	QPushButton* btn;
	QPushButton* btn_cos;
	QPushButton* btn_adauga_cos;
	QPushButton* btn_random_cos;
	QPushButton* btn_export_cos;
	QPushButton* btn_goleste_cos;
	QPushButton* btn_exit_cos;
	QLineEdit* edit_export_cos;
	QLineEdit* edit_random_cos;
	QLabel* lbl_random = new QLabel{ "Cate oferte doriti sa aveti in wishlist:" };
	QLabel* lbl_export = new QLabel{ "Numele fisierului export (.csv)/(.html):" };

	QLineEdit* destinatie_cos;
	QLineEdit* denumire_cos;
	QLineEdit* tip_cos;
	QLineEdit* pret_cos;
	void load_lista_cos(const vector<Turism>&oferte) {
		lista_cos->clear();
		for (auto& p : oferte) {
			auto item = new QListWidgetItem(QString::fromStdString(p.get_denumire()+"  "+p.get_destinatie()+"  "+p.get_tip()+"  "+to_string(p.get_pret())));
			lista_cos->addItem(item);

		}
	}
	void initGUICos() {
		lista_cos = new QListWidget;
		fereastra = new QWidget;
		QFormLayout* lyCos = new QFormLayout;
		fereastra->setLayout(lyCos);
		denumire_cos = new QLineEdit;
		destinatie_cos = new QLineEdit;
		tip_cos = new QLineEdit;
		pret_cos = new QLineEdit;
		lyCos->addRow("Denumire:", denumire_cos);
		lyCos->addRow("Destinatie:", destinatie_cos);
		lyCos->addRow("Tip:", tip_cos);
		lyCos->addRow("Pret:", pret_cos);
		btn_adauga_cos = new QPushButton("Adauga oferta existenta");
		btn_random_cos = new QPushButton("Adauga oferte random");
		btn_goleste_cos = new QPushButton("Goleste Cos");
		btn_export_cos = new QPushButton("Exporta Cos");
		btn_exit_cos = new QPushButton("Exit Wishlist");
		edit_random_cos = new QLineEdit;
		edit_export_cos = new QLineEdit;
		lyCos->addWidget(btn_adauga_cos);
		lyCos->addRow(lbl_random, edit_random_cos);
		lyCos->addWidget(btn_random_cos);
		lyCos->addWidget(btn_goleste_cos);
		lyCos->addRow(lbl_export, edit_export_cos);
		lyCos->addWidget(btn_export_cos);
		lyCos->addWidget(btn_exit_cos);
		lyCos->addWidget(lista_cos);
		fereastra->show();
	}
	void connect_cos() {
		cos.addObserver(this);
		QObject::connect(btn_exit_cos, &QPushButton::clicked, this, [&]() {
			QMessageBox::information(this, "Info", "Inchidere Wishlist");
			fereastra->close();
			});
		QObject::connect(btn_adauga_cos, &QPushButton::clicked, [&]() {
			try {
				string denumire = denumire_cos->text().toStdString();
				string destinatie = destinatie_cos->text().toStdString();
				string tip = tip_cos->text().toStdString();
				double pret = pret_cos->text().toDouble();
				Turism t{ denumire, destinatie, tip, pret };
				cos.adaugaOfertaCos(t);
				denumire_cos->clear();
				destinatie_cos->clear();
				tip_cos->clear();
				pret_cos->clear();
				load_lista_cos(cos.getAllCos());
			}
			catch (RepoException& ex) {
				QMessageBox::warning(this, "Info", QString::fromStdString(ex.get_mesaj()));
			}
			});
		QObject::connect(btn_random_cos, &QPushButton::clicked, [&]() {
			try {
				int nr = edit_random_cos->text().toInt();
				edit_random_cos->clear();
				cos.umple(nr);
				load_lista_cos(cos.getAllCos());
			}
			catch (RepoException& ex) {
				QMessageBox::warning(this, "Info", QString::fromStdString(ex.get_mesaj()));
			}
			});
		QObject::connect(btn_goleste_cos, &QPushButton::clicked, [&]() {
			try {
				cos.stergeCos();
				load_lista_cos(cos.getAllCos());
			}
			catch (RepoException& ex) {
				QMessageBox::warning(this, "Info", QString::fromStdString(ex.get_mesaj()));
			}
			});
		QObject::connect(btn_export_cos, &QPushButton::clicked, [&]() {
			try {
				string fisier = edit_export_cos->text().toStdString();
				edit_export_cos->clear();
				cos.exportaCos(fisier);
				lista_cos->clear();
				cos.stergeCos();
				load_lista_cos(cos.getAllCos());
			}
			catch (RepoException& ex) {
				QMessageBox::warning(this, "Info", QString::fromStdString(ex.get_mesaj()));
			}
			});
	}
public:
	CosLista(CosOferte& cos) :cos{ cos } {
		initGUICos();
		connect_cos();
		load_lista_cos(cos.getAllCos());
	}
	void update()override {
		load_lista_cos(cos.getAllCos());

	}
	~CosLista() {
		cos.removeObserver(this);
	}
};