#include "Gui.h"

void GUI::init() {
    setLayout(mainL);
    mainL->addWidget(procesoareList);
    mainL->addWidget(placiList);
    mainL->addWidget(formDreapta);
    mainL->addWidget(pret);

    formDreapta->setLayout(formDreaptaL);
    formDreaptaL->addWidget(new QLabel{ "nume placa: " });
    formDreaptaL->addWidget(namePlaca);
    formDreaptaL->addWidget(new QLabel{ "soclu placa: " });
    formDreaptaL->addWidget(socluPlaca);
    formDreaptaL->addWidget(new QLabel{ "pret placa:" });
    formDreaptaL->addWidget(pretPlaca);
    formDreaptaL->addWidget(addBtn);
}

void GUI::conec() {
    QObject::connect(addBtn, &QPushButton::clicked, [this]() {
        if (pretPlaca->text().isEmpty() || namePlaca->text().isEmpty() || socluPlaca->text().isEmpty())
            return;
        try {
            std::string pretStr = pretPlaca->text().toStdString();
            std::string nume = namePlaca->text().toStdString();
            std::string soclu = socluPlaca->text().toStdString();
            int pret = std::stoi(pretStr);
            service.addPlaca(nume, soclu, pret);
            reloadPlaciList(service.getPlaciDeBaza());
        }
        catch (std::invalid_argument&) {
            QMessageBox::warning(this, "warning", "trebuie intodus un numar");
        }
        });

    QObject::connect(procesoareList, &QListWidget::itemSelectionChanged, [this]() {
        if (procesoareList->selectedItems().isEmpty())
            return;
        reloadPlaciList(service.filterBySoclu(procesoareList->selectedItems()[0]->data(Qt::UserRole).toString().toStdString()));
        });

    QObject::connect(placiList, &QListWidget::itemSelectionChanged, [this]() {
        if (procesoareList->selectedItems().isEmpty())
            return;
        if (placiList->selectedItems().isEmpty())
            return;
        std::string nameProcesor = procesoareList->selectedItems()[0]->data(Qt::UserRole).toString().toStdString();
        std::string namePlaca = placiList->selectedItems()[0]->text().toStdString();
        pret->setText(QString::fromStdString("pret: " + std::to_string(service.pret(nameProcesor, namePlaca))));
        });
}

void GUI::reloadPlaciList(const std::vector<Candidat>& lst) {
    placiList->clear();
    for (const auto& placa : lst) {
        placiList->addItem(QString::fromStdString(placa.getNume()));
    }
}
