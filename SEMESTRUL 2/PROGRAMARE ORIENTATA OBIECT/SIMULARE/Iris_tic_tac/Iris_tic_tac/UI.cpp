//
// Created by Iris on 6/21/2024.
//

#include "UI.h"

#include <qmessagebox.h>
void UI::initGUI() {
    auto hLy = new QHBoxLayout;
    this->setLayout(hLy);
    auto v1Ly = new QVBoxLayout;
    auto v2Ly = new QVBoxLayout;
    hLy->addLayout(v1Ly);
    hLy->addLayout(v2Ly);
    v1Ly->addWidget(listaJocuri);
    v2Ly->addLayout(infoForm);
    infoForm->addRow("Dimensiune: ", dimField);
    infoForm->addRow("Tabla de joc: ", tablaField);
    infoForm->addRow("Jucator: ", jucatorField);
    infoForm->addRow("Stare veche: ", stareField);
    v2Ly->addWidget(addBtn);
    //    tw = new TablaWindow(" ", "", 1,srv);
    tw = nullptr;
    v2Ly->addLayout(modifyForm);
    modifyForm->addRow("Dimensiune noua: ", dimModifField);
    modifyForm->addRow("Tabla noua: ", tablaModifField);
    modifyForm->addRow("Jucator nou: ", jucatorModifField);
    modifyForm->addRow("Stare de modificat: ", stareModifField);
    v2Ly->addWidget(modifyBtb);
    v2Ly->addWidget(deleteBtn);


}

void UI::loadData() {
    vector<Joc> listaSortata = srv.sortStare();
    jocModel = new JocTableModel(listaSortata);
    listaJocuri->setModel(jocModel);

}

void UI::connectAddBtn() {
    QObject::connect(addBtn, &QPushButton::clicked, [&]() {
        auto dim = dimField->text().toInt();
        auto tabla = tablaField->text().toStdString();
        auto jucator = jucatorField->text().toStdString();
        srv.addJoc(dim, tabla, jucator);
        loadData();
        });
}

void UI::connectGUI() {
    connectAddBtn();
    connectModifyBtn();
    connectSelectCell();
    connectDelete();
}

void UI::connectModifyBtn() {
    QObject::connect(modifyBtb, &QPushButton::clicked, [&]() {
        auto dim = dimField->text().toInt();
        auto tabla = tablaField->text().toStdString();
        auto jucator = jucatorField->text().toStdString();
        auto stare = stareField->text().toStdString();

        auto dimNoua = dimModifField->text().toInt();
        auto tablaNoua = tablaModifField->text().toStdString();
        auto jucatorNou = jucatorModifField->text().toStdString();
        auto stareNoua = stareModifField->text().toStdString();
        try {
            srv.modifica(dim, tabla, jucator, stare, dimNoua, tablaNoua, jucatorNou, stareNoua);
            loadData();
        }
        catch (std::invalid_argument& ia)
        {
            QMessageBox msgBox;
            msgBox.setText(ia.what());
            msgBox.exec();
        }
        });
}

void UI::connectSelectCell() {
    QObject::connect(listaJocuri, &QTableView::clicked, [this](const QModelIndex& index) {
        auto indexx = jocModel->index(index.row(), 2);
        auto indexxx = jocModel->index(index.row(), 0);
        auto indexxxx = jocModel->index(index.row(), 3);

        string s = indexx.data(Qt::DisplayRole).toString().toStdString();
        int id = indexxx.data(Qt::DisplayRole).toInt();
        string jucator = indexxxx.data(Qt::DisplayRole).toString().toStdString();
        if (tw != nullptr)
            tw->deleteLater();
        tw = new TablaWindow(s, jucator, id, this->srv);
        tw->show();
        });

}

void UI::connectDelete() {
    QObject::connect(deleteBtn, &QPushButton::clicked, [&]() {
        auto index = listaJocuri->selectionModel()->selectedIndexes()[0];
        auto indexx = jocModel->index(index.row(), 0);
        int id = indexx.data(Qt::DisplayRole).toInt();
        srv.deleteService(id);
        loadData();
        });
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
